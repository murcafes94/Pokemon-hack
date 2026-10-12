import unittest
from apply_exact import translate_content
from import_reference import entries, safe


class ExactTests(unittest.TestCase):
    def test_whole_literal_preserves_code_and_variables(self):
        source = 'const u8 text[] = _("Hello "\n"{PLAYER}!"); // Hello {PLAYER}!'
        result, seen = translate_content(source, {'Hello {PLAYER}!': '¡Hola {PLAYER}!'})
        self.assertEqual(seen, {'Hello {PLAYER}!'})
        self.assertIn('// Hello {PLAYER}!', result)
        self.assertIn('const u8 text[]', result)
        self.assertEqual(translate_content(result, {'Hello {PLAYER}!': '¡Hola {PLAYER}!'})[0], result)

    def test_reject_changed_dynamic_argument(self):
        with self.assertRaises(ValueError):
            translate_content('_("{DYNAMIC 0}")', {'{DYNAMIC 0}': '{DYNAMIC 1}'})

    def test_unnamed_struct_menu_entries(self):
        source = 'const struct Entry t[] = {[OPTION_EXIT] = {COMPOUND_STRING("Exit"), COMPOUND_STRING("Return")},};'
        parsed = entries(source, 'src/pc.c')
        self.assertEqual([x['raw'] for x in parsed['list:OPTION_EXIT']], ['Exit', 'Return'])

    def test_berry_index_aliases(self):
        source = 'const struct Berry t[] = {[ITEM_ORAN_BERRY - FIRST_BERRY_INDEX] = {.name = _("Aranja")},};'
        self.assertEqual(entries(source, 'src/berry.c')['field:BERRY_ID_ORAN:name'][0]['raw'], 'Aranja')

    def test_repeated_variable_is_initialized(self):
        tokens = {'PLAYER'}
        characters = set('Hola hello $')
        self.assertIsNone(safe('hello {PLAYER} {PLAYER}$', 'Hola {PLAYER}$', tokens, characters))


if __name__ == '__main__':
    unittest.main()
