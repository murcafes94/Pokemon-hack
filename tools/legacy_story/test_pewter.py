"""Exercise the second Kanto leg, terrain and persistent ninth badge."""
import json
import re
import unittest
from test_prologue import ROOT, run_event
from test_kanto_expedition import resources, flood

BADGE = 'FLAG_LEGACY_BADGE_BOULDER'
VISITED = 'FLAG_LEGACY_KANTO_PEWTER_VISITED'
READY = {'FLAG_SYS_GAME_CLEAR', 'FLAG_LEGACY_KANTO_REPORTED'}
NAMES = ['LegacyKanto_Route2', 'LegacyKanto_ViridianForest', 'LegacyKanto_PewterOutpost']

class PewterTests(unittest.TestCase):
    def test_map_script_tables_are_included_in_the_native_rom(self):
        source=(ROOT/'data/event_scripts.s').read_text()
        for name in NAMES + ['LegacyKanto_PewterGym']:
            self.assertIn(f'.include "data/maps/{name}/scripts.inc"', source)
            table=(ROOT/f'data/maps/{name}/scripts.inc').read_text()
            self.assertIn(name+'_MapScripts::', table)

    def test_connections_are_bidirectional_and_walkable(self):
        names = ['LegacyKanto_Route1', 'LegacyKanto_ViridianOutpost'] + NAMES
        for south, north in zip(names, names[1:]):
            sd, _, sw, sh, _ = resources(south)
            nd, _, nw, nh, _ = resources(north)
            self.assertIn({'map': nd['id'], 'offset': 0, 'direction': 'up'}, sd['connections'])
            self.assertIn({'map': sd['id'], 'offset': 0, 'direction': 'down'}, nd['connections'])
            self.assertIn((11, 0), flood(south, (11, sh-3)))
            self.assertIn((11, nh-1), flood(north, (11, nh-3)))
        for name in NAMES:
            d, _, _, h, _ = resources(name)
            seen = flood(name, (11, h-3))
            for obj in d['object_events']:
                x, y = obj['x'], obj['y']
                self.assertTrue(any(p in seen for p in ((x-1,y),(x+1,y),(x,y-1),(x,y+1))), (name,obj))
            self.assertIn((12,12), seen)

    def test_gym_doors_and_leader_are_reachable(self):
        d, _, _, _, _ = resources('LegacyKanto_PewterGym')
        seen = flood('LegacyKanto_PewterGym', (5,18))
        self.assertIn((5,3), seen)
        self.assertIn((5,19), seen)
        self.assertIn((6,19), seen)
        for warp in d['warp_events']:
            self.assertEqual((warp['dest_map'],warp['dest_warp_id']),('MAP_LEGACY_KANTO_PEWTER_OUTPOST','0'))
        # Outdoor door uses the proven Rustboro gym facade and door metatile.
        _, _, w, _, a = resources('LegacyKanto_PewterOutpost')
        _, _, ow, _, original = resources('RustboroCity')
        self.assertEqual(a[10*w+12], original[19*ow+27])
        self.assertIn((12,11), flood('LegacyKanto_PewterOutpost',(12,12)))

    def test_brock_requires_champion_and_report_and_accepts_cancellation(self):
        for flags in (set(), {'FLAG_SYS_GAME_CLEAR'}, {'FLAG_LEGACY_KANTO_REPORTED'}):
            after, _, warp, locked = run_event('LegacyPewter_EventScript_Brock', flags)
            self.assertEqual(after, flags)
            self.assertIsNone(warp)
            self.assertFalse(locked)
        after, _, _, locked = run_event('LegacyPewter_EventScript_Brock', READY, [0])
        self.assertEqual(after, READY)
        self.assertFalse(locked)

    def test_loss_awards_nothing_win_awards_once_and_preserves_hoenn(self):
        flags = READY | {f'FLAG_BADGE{i:02}_GET' for i in range(1,9)}
        after, _, _, _ = run_event('LegacyPewter_EventScript_Brock', flags, [1], battle_won=False)
        self.assertEqual(after, flags)
        after, _, _, locked = run_event('LegacyPewter_EventScript_Brock', flags, [1])
        self.assertEqual(after, flags | {BADGE})
        self.assertFalse(locked)
        repeated, messages, _, _ = run_event('LegacyPewter_EventScript_Brock', after)
        self.assertEqual(repeated, after)
        self.assertEqual(messages, ['LegacyPewter_Text_Done'])
        recovered, _, _, _ = run_event('LegacyPewter_EventScript_Brock', flags, trainers_defeated={'TRAINER_LEGACY_BROCK'})
        self.assertEqual(recovered, after)

    def test_checkpoint_and_journal(self):
        respawns = []
        after, _, _, _ = run_event('LegacyPewter_EventScript_Transition', READY, respawns=respawns)
        self.assertEqual(after, READY | {VISITED})
        self.assertEqual(respawns, ['HEAL_LOCATION_LEGACY_KANTO_PEWTER'])
        for flags in (after, after | {BADGE}):
            result, messages, warp, locked = run_event('LegacyPewter_EventScript_Journal', flags)
            self.assertEqual(result, flags)
            self.assertIsNone(warp)
            self.assertFalse(locked)
            self.assertEqual(messages[-1], 'LegacyPewter_Text_Done' if BADGE in flags else 'LegacyPewter_Text_Pending')
        healed=[]
        run_event('LegacyPewter_EventScript_Heal', after, healed=healed)
        self.assertEqual(healed,[True])

    def test_encounters_and_trainer_capacity(self):
        encounters = json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]['encounters']
        for map_id in ('MAP_LEGACY_KANTO_ROUTE2','MAP_LEGACY_KANTO_VIRIDIAN_FOREST'):
            mons = next(e for e in encounters if e['map']==map_id)['land_mons']['mons']
            self.assertEqual(len(mons),12)
            self.assertTrue(all(50 <= m['min_level'] <= m['max_level'] <= 54 for m in mons))
        text=(ROOT/'include/constants/opponents.h').read_text()
        self.assertRegex(text,r'TRAINER_LEGACY_BROCK\s+856')
        self.assertRegex(text,r'MAX_TRAINERS_COUNT_EMERALD\s+864')
        for fn in ('flags.h','flags_frlg.h'):
            text=(ROOT/f'include/constants/{fn}').read_text()
            for num in (0x4BF,0x4C0):
                self.assertRegex(text,rf'FLAG_(?:UNUSED_)?0x{num:03X}\s+0x{num:03X} // Reserved by Legacy:')

if __name__ == '__main__':
    unittest.main()
