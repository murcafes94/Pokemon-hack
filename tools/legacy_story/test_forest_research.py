"""Execute forest events and validate actual native map/encounter resources."""
from collections import Counter, deque
import json
import re
import struct
import unittest
from test_prologue import ROOT, run_event, REGISTERED, OBSERVED, BRIEFED
from test_field_research import ASSIGNED, FIELD_OBSERVED, REPORTED, WAITED

FOREST = 'FLAG_LEGACY_FOREST_'
JOINED, SHROOM, WURM, FILED, DISTANCE, QUIET = [FOREST + k for k in
    ('ASSIGNED', 'SHROOMISH', 'WURMPLE', 'REPORTED', 'DISTANCE', 'QUIET')]
BASE = {REGISTERED, OBSERVED, BRIEFED, ASSIGNED, FIELD_OBSERVED, REPORTED}
MAP = 'PetalburgWoods_LegacyClearing'


def neighbors(p):
    x, y = p
    return [(x+1, y), (x-1, y), (x, y+1), (x, y-1)]


def map_resources(name):
    data = json.loads((ROOT / f'data/maps/{name}/map.json').read_text())
    layout = next(l for l in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
                  if l['id'] == data['layout'])
    w, h = layout['width'], layout['height']
    raw = (ROOT / layout['blockdata_filepath']).read_bytes()
    assert len(raw) == 2*w*h
    blocks = struct.unpack('<' + str(w*h) + 'H', raw)
    return data, w, h, blocks


def reachable(name, start, occupied=None):
    data, w, h, blocks = map_resources(name)
    if occupied is None:
        occupied = {(o['x'], o['y']) for o in data['object_events']}
    header = re.sub(r'//[^\n]*', '', (ROOT / 'include/constants/metatile_behaviors.h').read_text())
    names = re.findall(r'\bMB_\w+', header.split('enum {', 1)[1].split('}', 1)[0])
    attrs = []
    for path in ('primary/general', 'secondary/rustboro'):
        b = (ROOT / f'data/tilesets/{path}/metatile_attributes.bin').read_bytes()
        attrs.append(struct.unpack('<' + str(len(b)//2) + 'H', b))
    safe = {'MB_NORMAL', 'MB_TALL_GRASS', 'MB_LONG_GRASS', 'MB_SHORT_GRASS',
            'MB_PUDDLE', 'MB_FOOTPRINTS', 'MB_SOUTH_ARROW_WARP', 'MB_NORTH_ARROW_WARP'}
    def passable(p):
        x, y = p
        if not (0 <= x < w and 0 <= y < h) or p in occupied:
            return False
        v = blocks[y*w+x]
        n = v & 1023
        return not v & 0xC00 and names[attrs[n>=512][n%512] & 255] in safe
    assert passable(start), start
    seen, todo = {start}, deque([start])
    while todo:
        for p in neighbors(todo.popleft()):
            if p not in seen and passable(p):
                seen.add(p)
                todo.append(p)
    return seen


class ForestTests(unittest.TestCase):
    def test_guide_requires_report_and_original_devon_event(self):
        for flags, woods, expected in ((set(), 1, 'NeedReport'), (BASE, 0, 'NeedDevon')):
            after, messages, warp, locked = run_event('LegacyForest_EventScript_Guide', flags,
                                                     woods_state=woods)
            self.assertEqual(after, flags)
            self.assertIsNone(warp)
            self.assertFalse(locked)
            self.assertEqual(messages, ['LegacyForest_Text_' + expected])

    def test_join_decline_accept_and_revisit_never_reset_state(self):
        flags, _, warp, locked = run_event('LegacyForest_EventScript_Guide', BASE, [0])
        self.assertEqual(flags, BASE)
        self.assertIsNone(warp)
        self.assertFalse(locked)
        flags, _, warp, locked = run_event('LegacyForest_EventScript_Guide', flags, [1])
        self.assertEqual(flags, BASE | {JOINED})
        self.assertEqual(warp, ('MAP_PETALBURG_WOODS_LEGACY_CLEARING', '11', '16'))
        self.assertFalse(locked)
        saved = flags | {SHROOM, DISTANCE}
        flags, _, _, locked = run_event('LegacyForest_EventScript_Guide', saved, [1])
        self.assertEqual(flags, saved)
        self.assertFalse(locked)

    def test_unassigned_observations_do_not_progress(self):
        for species in ('Shroomish', 'Wurmple'):
            flags, _, _, locked = run_event('LegacyForest_EventScript_' + species, BASE)
            self.assertEqual(flags, BASE)
            self.assertFalse(locked)

    def test_both_species_orders_and_all_decisions_persist(self):
        for order in (('Shroomish', 'Wurmple'), ('Wurmple', 'Shroomish')):
            for a in (0, 1):
                for b in (0, 1):
                    flags = BASE | {JOINED, WAITED}
                    for species in order:
                        answer = a if species == 'Shroomish' else b
                        flags, _, _, locked = run_event('LegacyForest_EventScript_' + species, flags, [answer])
                        self.assertFalse(locked)
                    self.assertTrue({SHROOM, WURM}.issubset(flags))
                    self.assertEqual(DISTANCE in flags, bool(a))
                    self.assertEqual(QUIET in flags, bool(b))
                    self.assertTrue((BASE | {WAITED}).issubset(flags))
                    saved = set(flags)
                    for species in order:
                        flags, _, _, locked = run_event('LegacyForest_EventScript_' + species, flags)
                        self.assertEqual(flags, saved)
                        self.assertFalse(locked)

    def test_reports_require_both_notes_and_can_be_filed_at_either_desk_once(self):
        for label in ('LegacyForest_EventScript_Researcher', 'Legacy_EventScript_Researcher'):
            for extra in (set(), {SHROOM}, {WURM}):
                before = BASE | {JOINED} | extra
                flags, _, _, locked = run_event(label, before)
                self.assertEqual(flags, before)
                self.assertFalse(locked)
            before = BASE | {JOINED, SHROOM, WURM}
            flags, messages, _, locked = run_event(label, before)
            self.assertEqual(flags, before | {FILED})
            self.assertIn('LegacyForest_Text_Report', messages)
            self.assertFalse(locked)
            flags, messages, _, locked = run_event(label, flags)
            self.assertEqual(messages, ['LegacyForest_Text_Done'])
            self.assertEqual(flags, before | {FILED})
            self.assertFalse(locked)

    def test_journal_keeps_all_three_studies_after_loading(self):
        for a in (False, True):
            for b in (False, True):
                saved = BASE | {JOINED, SHROOM, WURM, FILED} | ({DISTANCE} if a else set()) | ({QUIET} if b else set())
                flags, messages, _, locked = run_event('Legacy_EventScript_ResearchJournal', saved)
                self.assertEqual(messages, ['Legacy_Text_DistanceJournal', 'LegacyField_Text_JournalPassageReport',
                    'LegacyForest_Text_JournalOpen', 'LegacyForest_Text_JournalDistance' if a else 'LegacyForest_Text_JournalWait',
                    'LegacyForest_Text_JournalQuiet' if b else 'LegacyForest_Text_JournalPass', 'LegacyForest_Text_JournalReport'])
                self.assertEqual(flags, saved)
                self.assertFalse(locked)

    def test_permanent_flags_reserve_unused_bits_in_both_games(self):
        s = (ROOT / 'include/constants/flags.h').read_text()
        for i, name in enumerate((JOINED, SHROOM, WURM, FILED, DISTANCE, QUIET), 0x4A7):
            value = int(re.search(r'^#define ' + name + r'\s+(0x[\dA-Fa-f]+)', s, re.M)[1], 16)
            self.assertEqual(value, i)
            for f in ('flags.h', 'flags_frlg.h'):
                text = (ROOT / 'include/constants' / f).read_text()
                self.assertRegex(text, rf'FLAG_UNUSED_0x{i:03X}\s+0x{i:03X} // Reserved by Legacy:')

    def test_clearing_exit_npcs_sign_and_every_grass_patch_are_accessible(self):
        data, w, h, blocks = map_resources(MAP)
        self.assertEqual((w, h), (24, 20))
        seen = reachable(MAP, (11, 16))
        for event in data['object_events'] + data['bg_events']:
            self.assertTrue(any(p in seen for p in neighbors((event['x'], event['y']))), event)
        for obj in data['object_events']:
            self.assertEqual(blocks[obj['y']*w+obj['x']] >> 12, obj['elevation'])
        for i, v in enumerate(blocks):
            if v & 1023 == 0x00D:
                self.assertIn((i%w, i//w), seen)
        for warp in data['warp_events']:
            x, y = warp['x'], warp['y']
            self.assertIn((x, y-1), seen)
            self.assertEqual(blocks[y*w+x], 0x0204)  # Existing MB_SOUTH_ARROW_WARP.
            self.assertEqual(warp['dest_warp_id'], '6')
        species = {o['graphics_id'] for o in data['object_events']}
        for s in ('SHROOMISH', 'WURMPLE'):
            self.assertIn(f'OBJ_EVENT_GFX_SPECIES({s})', species)
            self.assertTrue((ROOT / f'graphics/pokemon/{s.lower()}/overworld.png').is_file())

    def test_new_guide_and_return_keep_south_entrance_and_devon_path_connected(self):
        data, _, _, _ = map_resources('PetalburgWoods')
        self.assertEqual(len(data['object_events']), 14)
        self.assertEqual(data['warp_events'][6]['dest_map'], 'MAP_PETALBURG_WOODS_LEGACY_CLEARING')
        self.assertEqual((data['warp_events'][6]['x'], data['warp_events'][6]['y']), (18, 34))
        seen = reachable('PetalburgWoods', (18, 34))
        self.assertIn((16, 37), seen)  # South entrance from Route 104.
        self.assertIn((26, 24), seen)  # Approach to the original Devon scene.
        self.assertTrue(any(p in seen for p in neighbors((18, 33))))
        occupied = {(o['x'], o['y']) for o in data['object_events'][:-1]}
        previous = reachable('PetalburgWoods', (18, 34), occupied)
        self.assertEqual(previous - seen, {(18, 33)})

    def test_wild_encounters_have_valid_slots_and_early_hoenn_levels(self):
        d = json.loads((ROOT / 'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]
        found = [e for e in d['encounters'] if e['map'] == 'MAP_PETALBURG_WOODS_LEGACY_CLEARING']
        self.assertEqual(len(found), 1)
        rates = next(f['encounter_rates'] for f in d['fields'] if f['type'] == 'land_mons')
        mons = found[0]['land_mons']['mons']
        self.assertEqual(len(mons), len(rates))
        shares = Counter()
        for mon, rate in zip(mons, rates):
            self.assertLessEqual(3, mon['min_level'])
            self.assertLessEqual(mon['min_level'], mon['max_level'])
            self.assertLessEqual(mon['max_level'], 6)
            shares[mon['species']] += rate
        self.assertEqual(shares, {'SPECIES_WURMPLE': 40, 'SPECIES_SHROOMISH': 30,
                                  'SPECIES_ZIGZAGOON': 20, 'SPECIES_TAILLOW': 10})


if __name__ == '__main__':
    unittest.main()
