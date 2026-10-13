#!/usr/bin/env python3
"""Check selected Spanish text widths, including bounded variable expansion."""
from pathlib import Path
from functools import cache
import json
import re
from import_reference import ROOT, entries, CALL, LITERAL
from inventory import without_comments


@cache
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


@cache
def symbol_widths():
    fonts = (ROOT / 'src/fonts.c').read_text()
    body = re.search(r'gFontNormalLatinGlyphWidths\[\]\s*=\s*\{([^}]+)', fonts, re.S)[1]
    glyphs = list(map(int, re.findall(r'\d+', body)))
    charmap = (ROOT / 'charmap.txt').read_text()
    widths = {}
    for token in ('POKEBLOCK', 'PKMN'):
        codes = re.search(r'^' + token + r'\s*=\s*([0-9A-Fa-f ]+)\s*$', charmap, re.M)[1]
        widths[token] = sum(glyphs[int(code, 16)] for code in codes.split())
    return widths


def bounded_text_width(text, variable_widths):
    """Measure selected controls using their glyphs or explicit expansion bounds."""
    control_width = 0
    for token in re.findall(r'\{([^}]+)\}', text):
        if token in variable_widths:
            control_width += variable_widths[token]
        elif token in {'POKEBLOCK', 'PKMN'}:
            control_width += symbol_widths()[token]
        else:
            raise ValueError(f'Unmeasured control: {token}')
    return text_width(re.sub(r'\{[^}]+\}', '', text)) + control_width


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
    oak = entries((ROOT / 'data/text/pokedex_rating.inc').read_text(), 'data/text/pokedex_rating.inc')
    for key, values in oak.items():
        if not key.startswith('label:PokedexRating_Text_'):
            continue
        for value in values:
            for line in re.split(r'\\[npl]', value['raw']):
                line = line.replace('{FONT_NORMAL}', '').rstrip('$')
                # Variable expansion must be checked separately in the emulator.
                if '{' not in line:
                    checks.append((key, line, 208))
    failures = [(name, text, text_width(text), limit) for name, text, limit in checks if text_width(text) > limit]
    targets = json.loads(Path(__file__).with_name('layout_targets.json').read_text())
    for filename, target in targets.items():
        parsed = entries((ROOT / filename).read_text(), filename)
        keys = target.get('keys', [key for key in parsed if key.startswith(target.get('prefix', ''))])
        for key in keys:
            if key not in parsed:
                raise ValueError(f'Missing text layout target: {filename}:{key}')
            for value in parsed[key]:
                lines = re.split(r'\\[npl]', value['raw'].rstrip('$'))
                if 'max_lines' in target and len(lines) > target['max_lines']:
                    raise ValueError(f'Too many text lines: {filename}:{key}')
                for line in lines:
                    width = bounded_text_width(line, target.get('variable_widths', {}))
                    checks.append((key, line, target['limit']))
                    if width > target['limit']:
                        failures.append((key, line, width, target['limit']))
    if failures:
        raise ValueError(f'Text exceeds its window: {failures}')
    print(f'Selected text widths verified: {len(checks)} lines')


if __name__ == '__main__':
    main()
