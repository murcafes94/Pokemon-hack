#!/usr/bin/env python3
"""Check static berry and PC-menu text against actual Legacy font/window widths."""
from pathlib import Path
import re
from import_reference import ROOT, entries, CALL, LITERAL
from inventory import without_comments


def normal_font_widths():
    fonts = (ROOT / 'src/fonts.c').read_text()
    body = re.search(r'gFontNormalLatinGlyphWidths\[\]\s*=\s*\{([^}]+)', fonts, re.S)[1]
    widths = list(map(int, re.findall(r'\d+', body)))
    charmap = (ROOT / 'charmap.txt').read_text()
    return {char: widths[int(code, 16)] for char, code in
            re.findall(r"^'(.)'\s*=\s*([0-9A-Fa-f]{2})\s*$", charmap, re.M)}


def text_width(text):
    widths = normal_font_widths()
    return sum(widths[char] for char in text)


def main():
    checks = []
    berries = entries((ROOT / 'src/berry.c').read_text(), 'src/berry.c')
    for key, values in berries.items():
        if key.endswith(('description1', 'description2')):
            checks.extend((key, value['raw'], 200) for value in values)
    pc = without_comments((ROOT / 'src/pokemon_storage_system.c').read_text())
    start = pc.index('static const sMainMenuTexts')
    end = pc.index('};', start)
    for match in CALL.finditer(pc, start, end):
        text = ''.join(s.group()[1:-1] for s in LITERAL.finditer(match['literals']))
        checks.extend(('PC menu', line, 184) for line in text.split(r'\n'))
    failures = [(name, text, text_width(text), limit) for name, text, limit in checks if text_width(text) > limit]
    if failures:
        raise ValueError(f'Text exceeds its window: {failures}')
    print(f'Static text widths verified: {len(checks)} lines')


if __name__ == '__main__':
    main()
