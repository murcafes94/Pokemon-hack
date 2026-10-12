#!/usr/bin/env python3
"""Inventory editable Legacy text without translating or changing game sources."""
import argparse
from collections import Counter
import csv
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[2]
FIELDS = ['file', 'line', 'kind', 'symbol', 'text', 'visible']
EXTENSIONS = {'.c', '.h', '.inc', '.party'}
STRING = r'"(?:\\.|[^"\\])*"'
TOKENS = re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|' + STRING + r"|'(?:\\.|[^'\\])*'")
CALL = re.compile(r'\b(?P<kind>COMPOUND_STRING|_)\s*\(\s*(?P<literals>(?:' + STRING + r'\s*)+)\)')
LITERAL = re.compile(STRING)
ASM = re.compile(r'\.string[ \t]+(?P<literal>' + STRING + ')')
LABEL = re.compile(r'^[ \t]*(?P<symbol>[A-Za-z_][A-Za-z0-9_]*)::?[ \t]*$', re.MULTILINE)
DECLARATION = re.compile(r'\b([A-Za-z_][A-Za-z0-9_]*)\s*(?:\[[^\]]*\])?\s*=\s*$')
PARTY = re.compile(r'^===\s*(?P<symbol>\w+)\s*===[ \t]*$', re.MULTILINE)
NAME = re.compile(r'^Name:[ \t]*(?P<text>[^\r\n]+)', re.MULTILINE)


def without_comments(content):
    def mask(match):
        text = match.group()
        if text.startswith(('//', '/*')):
            return ''.join('\n' if c == '\n' else ' ' for c in text)
        return text
    return TOKENS.sub(mask, content)


def visible_text(text):
    return re.sub(r'\\[nplf]', ' ', text).replace(r'\\', '\\').strip()


def extract_content(content, filename):
    source = without_comments(content)
    records = []
    def add(pos, kind, symbol, raw):
        if raw:
            records.append(dict(file=filename, line=source.count('\n', 0, pos) + 1,
                                kind=kind, symbol=symbol, text=raw, visible=visible_text(raw)))
    if Path(filename).suffix in {'.c', '.h'}:
        # Scan tokens so macro-shaped content inside strings isn't inventoried as code.
        pos = 0
        for token in TOKENS.finditer(source):
            if token.start() < pos:
                continue
            before = source[pos:token.start()]
            prefix = re.search(r'\b(?:COMPOUND_STRING|_)\s*\(\s*$', before)
            if prefix:
                start = pos + prefix.start()
                match = CALL.match(source, start)
                if match:
                    decl = DECLARATION.search(source[max(0, start - 250):start])
                    raw = ''.join(m.group()[1:-1] for m in LITERAL.finditer(match['literals']))
                    add(start, 'compound' if match['kind'] == 'COMPOUND_STRING' else 'underscore',
                        decl.group(1) if decl else '', raw)
                    pos = match.end()
                    continue
            pos = token.end()
    elif Path(filename).suffix == '.inc':
        labels = list(LABEL.finditer(source))
        for i, label in enumerate(labels):
            end = labels[i + 1].start() if i + 1 < len(labels) else len(source)
            raw = ''.join(m['literal'][1:-1] for m in ASM.finditer(source, label.end(), end))
            add(label.start(), 'asm_string_block', label['symbol'], raw)
    elif Path(filename).suffix == '.party':
        trainers = list(PARTY.finditer(source))
        for i, trainer in enumerate(trainers):
            end = trainers[i + 1].start() if i + 1 < len(trainers) else len(source)
            name = NAME.search(source, trainer.end(), end)
            if name:
                add(name.start(), 'trainer_name', trainer['symbol'], name['text'].strip())
    return records


def source_paths(root):
    # Ignore build-generated headers; trainer names come from editable .party sources.
    result = subprocess.run(['git', '-C', str(root), 'ls-files', '-z', '--cached', '--others',
                             '--exclude-standard', '--', 'src', 'data'],
                            capture_output=True, check=True)
    return sorted({root / p.decode('utf-8') for p in result.stdout.split(b'\0') if p
                   and Path(p.decode('utf-8')).suffix in EXTENSIONS})


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT)
    parser.add_argument('--output', type=Path, default=Path(__file__).with_name('text_inventory.csv'))
    args = parser.parse_args()
    records = []
    for path in source_paths(args.root):
        content = path.read_text(encoding='utf-8')
        records.extend(extract_content(content, path.relative_to(args.root).as_posix()))
    # UTF-8 strict reading avoids silently replacing invalid source characters.
    with args.output.open('w', newline='', encoding='utf-8') as stream:
        writer = csv.DictWriter(stream, fieldnames=FIELDS, lineterminator='\n')
        writer.writeheader()
        writer.writerows(records)
    print('Pokémon Legacy — Inventario de localización')
    print(f'Entradas: {len(records):,}; archivos: {len({r["file"] for r in records}):,}')
    for kind, count in Counter(r['kind'] for r in records).most_common():
        print(f'  {kind}: {count:,}')
    print(f'CSV: {args.output}')


if __name__ == '__main__':
    main()
