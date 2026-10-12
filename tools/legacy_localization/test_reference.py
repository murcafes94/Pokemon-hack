import unittest
from import_reference import entries, safe, placeholders


class ReferenceTests(unittest.TestCase):
    def test_index_links_named_battle_text(self):
        src = 'static const u8 sText[] = _("Used {B_BUFF1}!");\nconst u8 *const table[] = {[STRINGID_TEST] = sText,};'
        parsed = entries(src, 'src/battle_message.c')
        self.assertEqual(parsed['index:STRINGID_TEST'][0]['raw'], 'Used {B_BUFF1}!')
        self.assertEqual(parsed['index:STRINGID_TEST'][0]['spans'], parsed['symbol:sText'][0]['spans'])

    def test_direct_battle_index(self):
        src = 'const u8 *const table[] = {[STRINGID_TEST] = COMPOUND_STRING("Usó {B_BUFF1}!"),};'
        self.assertEqual(entries(src, 'src/battle_message.c')['index:STRINGID_TEST'][0]['raw'], 'Usó {B_BUFF1}!')

    def test_shared_description_resolves_text_only(self):
        src = 'const struct Item table[] = {[ITEM_TEST] = {.description = SharedDesc,},};'
        parsed = entries(src, 'src/data/items.h', {'SharedDesc': 'Descripción.'})
        self.assertEqual(parsed['field:ITEM_TEST:description'][0]['raw'], 'Descripción.')
        self.assertEqual(parsed['field:ITEM_TEST:description'][0]['spans'], [])

    def test_reject_uninitialized_placeholders(self):
        self.assertEqual(safe('Hello {PLAYER}$', 'Hola {STR_VAR_1}$', {'PLAYER', 'STR_VAR_1'}, set('Hola $')), 'placeholders')

    def test_preserve_existing_spanish(self):
        self.assertEqual(safe('¡Hola!$', '¡Buenas!$', set(), set('¡Hola!Buenas$')), 'existing_spanish')

    def test_reject_terminator_change(self):
        self.assertEqual(safe('Hello$', 'Hola', set(), set('Hello$Hola')), 'terminators')


if __name__ == '__main__':
    unittest.main()
