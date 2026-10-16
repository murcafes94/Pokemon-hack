"""Check quantity widths and VRAM allocation in the edited UI templates."""
from pathlib import Path
import re
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools/legacy_localization'))
from check_text_layout import text_width


def window(file, name):
    source = (ROOT / file).read_text()
    body = re.search(r'\[' + name + r'\]\s*=\s*\{([^}]+)', source)[1]
    return {key: int(value, 0) for key, value in
            re.findall(r'\.(\w+)\s*=\s*(0x[\dA-Fa-f]+|\d+)', body)}


class QuantityWindowTests(unittest.TestCase):
    def test_four_digits_and_price_have_separate_space(self):
        self.assertLessEqual(text_width('×9999'), 34)
        for file, name in [('src/item_menu.c', 'ITEMWIN_QUANTITY_WIDE'),
                           ('src/shop.c', 'WIN_QUANTITY_PRICE')]:
            template = window(file, name)
            self.assertGreaterEqual(template['width'] * 8, 34 + 54)
            self.assertLessEqual(template['tilemapLeft'] + template['width'], 29)

    def test_bag_names_leave_room_for_four_digit_quantities(self):
        fonts = (ROOT / 'src/fonts.c').read_text()
        glyphs = list(map(int, re.findall(r'\d+', re.search(r'gFontNarrowLatinGlyphWidths\[\]\s*=\s*\{([^}]+)', fonts)[1])))
        charmap = (ROOT / 'charmap.txt').read_text()
        widths = {}
        for char in '×9':
            code = int(re.search("^'" + char + "'\\s*=\\s*([0-9A-Fa-f]{2})", charmap, re.M)[1], 16)
            widths[char] = glyphs[code]
        quantity_left = 119 - widths['×'] - 4 * widths['9']
        source = (ROOT / 'src/item_menu.c').read_text()
        self.assertIn('88 - BAG_EXTRA_QUANTITY_WIDTH', source)
        self.assertLessEqual(8 + 88 - widths['9'], quantity_left - 2)

    def test_shop_window_vram_regions_do_not_overlap(self):
        names = ['WIN_QUANTITY_IN_BAG', 'WIN_QUANTITY_PRICE', 'WIN_MESSAGE']
        templates = [window('src/shop.c', name) for name in names]
        for current, following in zip(templates, templates[1:]):
            self.assertLessEqual(current['baseBlock'] + current['width'] * current['height'],
                                 following['baseBlock'])
        message = templates[-1]
        source = (ROOT / 'src/shop.c').read_text().split('static const struct WindowTemplate sShopBuyMenuYesNoWindowTemplates =')[1]
        next_block = int(re.search(r'\.baseBlock = (0x[\dA-Fa-f]+)', source)[1], 0)
        self.assertLessEqual(message['baseBlock'] + message['width'] * message['height'], next_block)
