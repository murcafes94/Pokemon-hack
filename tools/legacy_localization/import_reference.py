#!/usr/bin/env python3
"""Import compatible text literals by symbol, never engine logic or graphic resources."""
import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import re
import subprocess
from inventory import without_comments, STRING, LITERAL, LABEL, ASM, PARTY, NAME, source_paths

ROOT = Path(__file__).resolve().parents[2]
PROTECTED = {'data/text/birch_speech.inc', 'data/scripts/legacy_prologue.inc', 'data/scripts/legacy_field_research.inc'}
MACRO = r'(?:COMPOUND_STRING|_|ITEM_NAME|ITEM_PLURAL_NAME)'
CALL = re.compile(r'\b' + MACRO + r'\s*\(\s*(?P<literals>(?:' + STRING + r'\s*)+)\)')
DECL = re.compile(r'\b(?:static\s+)?const\s+(?:u8|char)\s+(?P<symbol>\w+)\s*(?:\[[^\]]*\])?\s*=\s*$')
INDEX = re.compile(r'\[(?P<symbol>[A-Z][A-Z0-9_]*(?:\s*-\s*FIRST_BERRY_INDEX)?)\]\s*=\s*\{')
FIELD = re.compile(r'\.(?P<field>[A-Za-z_]\w*)\s*=\s*$')
DIRECT = re.compile(r'\[(?P<symbol>[A-Z][A-Z0-9_]*)\]\s*=\s*$')
INDEX_POINTER = re.compile(r'\[(?P<index>[A-Z][A-Z0-9_]*)\]\s*=\s*(?P<symbol>[A-Za-z_]\w*)\s*,')
POINTER = re.compile(r'\.(?P<field>description)\s*=\s*(?P<symbol>[A-Za-z_]\w*)\s*,')
BRACES = re.compile(r'\{([^{}]+)\}')
LAYOUT = {'COLOR', 'HIGHLIGHT', 'SHADOW', 'COLOR_HIGHLIGHT_SHADOW', 'FONT', 'PAUSE', 'PAUSE_UNTIL_PRESS', 'CLEAR', 'CLEAR_TO', 'MIN_LETTER_SPACING', 'SIZE', 'SPACING'}
# Existing Spanish is preserved, including basic menu labels without accents.
SPANISH = re.compile(r'[¡¿ñÑáÁíÍóÓúÚ]|\b(?:CHICO|CHICA|NOMBRE|MOCHILA|GUARDAR|CANCELAR|SALIR|OBJETOS|POKÉDEX|SIEMPRE|POKÉMON|HABILIDAD|ATAQUE|DEFENSA)\b')


def entries(content, filename, shared=None):
    clean = without_comments(content)
    result = defaultdict(list)
    suffix = Path(filename).suffix
    if suffix in {'.c', '.h'}:
        indexes = list(INDEX.finditer(clean))
        for match in CALL.finditer(clean):
            prefix = clean[max(0, match.start() - 400):match.start()]
            decl = DECL.search(prefix)
            field = FIELD.search(prefix)
            direct = DIRECT.search(prefix)
            if decl:
                key = 'symbol:' + decl['symbol']
            elif direct:
                key = 'index:' + direct['symbol']
            elif field:
                preceding = [i for i in indexes if i.start() < match.start()]
                if not preceding:
                    continue
                key = 'field:' + preceding[-1]['symbol'] + ':' + field['field']
            else:
                preceding = [i for i in indexes if i.start() < match.start()]
                if not preceding:
                    continue
                index = preceding[-1]
                segment = LITERAL.sub('', clean[index.end():match.start()])
                if segment.count('}') > segment.count('{'):
                    continue
                key = 'list:' + index['symbol']
            if filename == 'src/berry.c':
                key = re.sub(r'ITEM_([A-Z0-9_]+)_BERRY\s*-\s*FIRST_BERRY_INDEX', r'BERRY_ID_\1', key)
            literals = list(LITERAL.finditer(clean, match.start('literals'), match.end('literals')))
            raw = ''.join(m.group()[1:-1] for m in literals)
            result[key].append(dict(raw=raw, spans=[(m.start(), m.end()) for m in literals]))
        for match in INDEX_POINTER.finditer(clean):
            values = result.get('symbol:' + match['symbol'], [])
            if len(values) == 1:
                result['index:' + match['index']].extend(values)
        # PBH shares some descriptions via named arrays. Resolve only an unambiguous definition.
        for match in POINTER.finditer(clean):
            preceding = [i for i in indexes if i.start() < match.start()]
            values = result.get('symbol:' + match['symbol'], [])
            if not values and shared and match['symbol'] in shared:
                values = [dict(raw=shared[match['symbol']], spans=[])]
            if preceding and len(values) == 1:
                key = 'field:' + preceding[-1]['symbol'] + ':' + match['field']
                if key not in result:
                    result[key].append(dict(raw=values[0]['raw'], spans=[]))
    elif suffix == '.inc':
        labels = list(LABEL.finditer(clean))
        for i, label in enumerate(labels):
            end = labels[i + 1].start() if i + 1 < len(labels) else len(clean)
            strings = list(ASM.finditer(clean, label.end(), end))
            if strings:
                result['label:' + label['symbol']].append(dict(
                    raw=''.join(m['literal'][1:-1] for m in strings),
                    spans=[(m.start('literal'), m.end('literal')) for m in strings]))
    elif suffix == '.party':
        trainers = list(PARTY.finditer(clean))
        for i, trainer in enumerate(trainers):
            end = trainers[i + 1].start() if i + 1 < len(trainers) else len(clean)
            name = NAME.search(clean, trainer.end(), end)
            if name:
                result['trainer:' + trainer['symbol']].append(dict(raw=name['text'].strip(),
                    spans=[(name.start('text'), name.end('text'))], plain=True))
    return result


def placeholders(text):
    return Counter(t for t in BRACES.findall(text) if t.split()[0] not in LAYOUT)


def safe(old, new, tokens, characters):
    if set(placeholders(old)) != set(placeholders(new)):
        return 'placeholders'
    if old.count('$') != new.count('$'):
        return 'terminators'
    if SPANISH.search(old):
        return 'existing_spanish'
    for token in BRACES.findall(new):
        if token.split()[0] not in tokens:
            return 'unknown_control'
    visible = BRACES.sub('', new)
    visible = re.sub(r'\\(?:x[0-9a-fA-F]{2}|[nplfrtv\\"\'])', '', visible)
    if any(c not in characters for c in visible):
        return 'unsupported_character'
    return None


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--reference', required=True, type=Path)
    parser.add_argument('--apply', action='store_true')
    parser.add_argument('--report', type=Path, required=True)
    args = parser.parse_args()
    revision = subprocess.check_output(['git', '-C', str(args.reference), 'rev-parse', 'HEAD'], text=True).strip()
    if revision != '74c8121ffd01a27b349975693e18537dade38b34':
        raise ValueError('Reference revision differs from the reviewed PBH snapshot')
    shared_values = defaultdict(set)
    for ref_path in source_paths(args.reference):
        ref_name = ref_path.relative_to(args.reference).as_posix()
        for key, values in entries(ref_path.read_text(), ref_name).items():
            if key.startswith(('symbol:', 'label:')):
                for value in values:
                    shared_values[key.split(':', 1)[1]].add(value['raw'])
    shared = {key: next(iter(values)) for key, values in shared_values.items() if len(values) == 1}
    charmap = (ROOT / 'charmap.txt').read_text()
    tokens = set(re.findall(r'^([A-Z][A-Z0-9_]*)\s*=', charmap, re.MULTILINE))
    characters = set(re.findall(r"^'(.)'\s*=", charmap, re.MULTILINE)) | set('\n\r\t$')
    counts = Counter()
    changes = []
    skipped = Counter()
    protected = {p: hashlib.sha256((ROOT / p).read_bytes()).hexdigest() for p in PROTECTED}
    for path in source_paths(ROOT):
        filename = path.relative_to(ROOT).as_posix()
        donor = args.reference / filename
        if filename in PROTECTED or not donor.is_file():
            continue
        content = path.read_text()
        own = entries(content, filename)
        reference = entries(donor.read_text(), filename, shared)
        edits = []
        scheduled = set()
        for key, values in own.items():
            candidates = reference.get(key, [])
            if len(values) != len(candidates):
                skipped['missing_or_ambiguous_symbol'] += len(values)
                continue
            for old, new in zip(values, candidates):
                if not old['spans'] or tuple(old['spans']) in scheduled or old['raw'] == new['raw']:
                    continue
                reason = safe(old['raw'], new['raw'], tokens, characters)
                if reason:
                    skipped[reason] += 1
                    continue
                scheduled.add(tuple(old['spans']))
                for i, (start, end) in enumerate(old['spans']):
                    replacement = new['raw'] if old.get('plain') else '"' + (new['raw'] if i == 0 else '') + '"'
                    edits.append((start, end, replacement))
                counts[filename] += 1
                changes.append(dict(file=filename, key=key,
                    before_sha256=hashlib.sha256(old['raw'].encode()).hexdigest(),
                    after_sha256=hashlib.sha256(new['raw'].encode()).hexdigest()))
        for start, end, replacement in sorted(edits, reverse=True):
            content = content[:start] + replacement + content[end:]
        if args.apply and edits:
            path.write_text(content)
    for p, digest in protected.items():
        assert hashlib.sha256((ROOT / p).read_bytes()).hexdigest() == digest
    report = dict(reference_commit='74c8121ffd01a27b349975693e18537dade38b34',
                  applied=args.apply, protected=protected, changed_entries=sum(counts.values()),
                  files=dict(counts), skipped=dict(skipped), changes=changes)
    args.report.write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n')
    print(json.dumps({k:v for k,v in report.items() if k not in ('files', 'changes')}, indent=2))
    print(f'Files: {len(counts)}; report: {args.report}')


if __name__ == '__main__':
    main()
