"""Regression checks for texts previously omitted from the localization inventory."""
import unittest
from inventory import extract_content, without_comments


class InventoryTests(unittest.TestCase):
    def test_adjacent_literals_and_controls(self):
        source = 'const u8 gText_Test[] = _("¡Hola, "\n/* keep position */ "{PLAYER}!\\p");'
        rows = extract_content(source, 'src/test.c')
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]['text'], '¡Hola, {PLAYER}!\\p')
        self.assertEqual(rows[0]['symbol'], 'gText_Test')

    def test_comments_and_macro_shaped_strings(self):
        source = '// _("unused")\nconst char *x = "_(\\"fake\\")";\nconst u8 y[] = COMPOUND_STRING("http://a/*b*/");'
        rows = extract_content(source, 'src/test.c')
        self.assertEqual([r['text'] for r in rows], ['http://a/*b*/'])
        self.assertEqual(rows[0]['line'], 3)
        self.assertEqual(source.count('\n'), without_comments(source).count('\n'))

    def test_asm_blocks_and_labels(self):
        source = '// .string "unused"\nFirst::\n .string "Hola\\n"\n .string "mundo$"\nSecond:\n .string "Adiós$"\n'
        rows = extract_content(source, 'data/text/test.inc')
        self.assertEqual([(r['symbol'], r['text']) for r in rows],
                         [('First', 'Hola\\nmundo$'), ('Second', 'Adiós$')])
        self.assertEqual(rows[0]['line'], 2)

    def test_editable_trainer_names(self):
        source = '/* Name: Fake */\n=== TRAINER_TEST ===\nName: RECLUTA\nPic: Grunt\n\nAbra\nLevel: 5\n'
        rows = extract_content(source, 'src/data/trainers.party')
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]['symbol'], 'TRAINER_TEST')
        self.assertEqual(rows[0]['text'], 'RECLUTA')


if __name__ == '__main__':
    unittest.main()
