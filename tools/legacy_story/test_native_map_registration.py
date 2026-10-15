"""Keep curated native map tables linked and test the Pewter return shortcut."""
import json
import re
import unittest
from collections import Counter
from test_prologue import ROOT, run_event
from test_kanto_expedition import flood

class NativeMapRegistrationTests(unittest.TestCase):
    def test_every_curated_map_script_table_is_included_once(self):
        source=(ROOT/'data/event_scripts.s').read_text()
        checked=[]
        for path in (ROOT/'data/maps').glob('LegacyKanto_*/map.json'):
            data=json.loads(path.read_text())
            if data.get('legacy_game_version')!='emerald':
                continue
            include=f'.include "data/maps/{path.parent.name}/scripts.inc"'
            self.assertEqual(source.count(include),1,include)
            scripts=path.with_name('scripts.inc').read_text()
            self.assertIn(data['name']+'_MapScripts::',scripts)
            checked.append(data['name'])
        self.assertGreaterEqual(len(checked),8)

    def test_legacy_labels_are_unique(self):
        files=list((ROOT/'data/scripts').glob('legacy*.inc'))
        files+=list((ROOT/'data/maps').glob('LegacyKanto_*/scripts.inc'))
        labels=Counter(label for p in files for label in re.findall(r'^([A-Za-z_0-9]+)::',p.read_text(),re.M))
        self.assertEqual([label for label,n in labels.items() if n!=1],[])

    def test_pewter_shortcut_requires_visit_and_keeps_badges(self):
        flag='FLAG_LEGACY_KANTO_PEWTER_VISITED'
        after,_,warp,locked=run_event('LegacyDebug_EventScript_Pewter')
        self.assertEqual(after,set());self.assertIsNone(warp);self.assertFalse(locked)
        before={flag,'FLAG_LEGACY_BADGE_BOULDER','FLAG_BADGE01_GET','FLAG_BADGE08_GET'}
        after,_,warp,locked=run_event('LegacyDebug_EventScript_Pewter',before)
        self.assertEqual(after,before)
        self.assertEqual(warp,('MAP_LEGACY_KANTO_PEWTERCITY','12','18'))
        self.assertFalse(locked)
        self.assertIn((12,18),flood('LegacyKanto_PewterCity',(12,22)))

if __name__=='__main__':
    unittest.main()
