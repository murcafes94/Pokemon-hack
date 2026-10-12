#!/usr/bin/env python3
"""Apply reviewed whole-string translations, including unnamed menu table entries."""
import json
from pathlib import Path
from import_reference import ROOT, CALL, LITERAL, PROTECTED, entries, placeholders
from inventory import without_comments


def translate_content(content, translations, filename='src/text.c'):
    if filename in PROTECTED:
        raise ValueError(f'Protected Legacy text: {filename}')
    clean = without_comments(content)
    edits = []
    seen = set()
    if Path(filename).suffix == '.inc':
        values = [value for group in entries(content, filename).values() for value in group]
    else:
        values = []
        for match in CALL.finditer(clean):
            strings = list(LITERAL.finditer(clean, match.start('literals'), match.end('literals')))
            values.append(dict(raw=''.join(s.group()[1:-1] for s in strings),
                               spans=[(s.start(), s.end()) for s in strings]))
    for value in values:
        raw = value['raw']
        if raw not in translations:
            continue
        new = translations[raw]
        if new == raw:
            continue
        if placeholders(raw) != placeholders(new) or raw.count('$') != new.count('$'):
            raise ValueError(f'Incompatible text controls: {raw}')
        for i, (start, end) in enumerate(value['spans']):
            edits.append((start, end, '"' + (new if i == 0 else '') + '"'))
        seen.add(raw)
    for start, end, replacement in sorted(edits, reverse=True):
        content = content[:start] + replacement + content[end:]
    return content, seen


def main():
    count = 0
    mapping = json.loads(Path(__file__).with_name('spanish_exact.json').read_text())
    for filename, translations in mapping.items():
        path = ROOT / filename
        content, seen = translate_content(path.read_text(), translations, filename)
        if seen:
            path.write_text(content)
        count += len(seen)
    print(f'Whole-string translations applied: {count}')


if __name__ == '__main__':
    main()
