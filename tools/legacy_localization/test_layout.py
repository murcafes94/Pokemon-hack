import unittest
from check_text_layout import bounded_text_width, text_width


class LayoutTests(unittest.TestCase):
    def test_variable_can_make_a_short_line_overflow(self):
        self.assertLess(text_width('Hola '), 208)
        self.assertGreater(bounded_text_width('Hola {PLAYER}', {'PLAYER': 200}), 208)

    def test_repeated_names_reserve_space_each_time(self):
        self.assertEqual(bounded_text_width('{PLAYER} y {PLAYER}', {'PLAYER': 42}),
                         84 + text_width(' y '))

    def test_unknown_variable_cannot_be_silently_ignored(self):
        with self.assertRaises(ValueError):
            bounded_text_width('Hola {STR_VAR_2}', {})

    def test_compound_symbol_occupies_rendered_space(self):
        self.assertGreater(bounded_text_width('Guarda {POKEBLOCK}s', {}),
                           text_width('Guarda s'))


if __name__ == '__main__':
    unittest.main()
