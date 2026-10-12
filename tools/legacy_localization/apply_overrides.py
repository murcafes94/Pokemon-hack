#!/usr/bin/env python3
"""Apply explicitly reviewed Legacy translations without changing surrounding code."""
import json
from pathlib import Path
from import_reference import ROOT, entries, placeholders


def main():
    changes = 0
    for filename, replacements in json.loads(Path(__file__).with_name('spanish_overrides.json').read_text()).items():
        path = ROOT / filename
        content = path.read_text()
        found = entries(content, filename)
        edits = {}
        for key, text in replacements.items():
            if key not in found:
                raise ValueError(f'Missing translation target: {filename} {key}')
            for old in found[key]:
                if placeholders(old['raw']) != placeholders(text):
                    raise ValueError(f'Placeholder mismatch: {filename} {key}')
                if old['raw'] == text:
                    continue
                for i, (start, end) in enumerate(old['spans']):
                    edits[(start, end)] = '"' + (text if i == 0 else '') + '"'
                changes += 1
        for (start, end), replacement in sorted(edits.items(), reverse=True):
            content = content[:start] + replacement + content[end:]
        if edits:
            path.write_text(content)
    print(f'Reviewed translations applied: {changes}')


if __name__ == '__main__':
    main()
