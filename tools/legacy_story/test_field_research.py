"""Exercise the actual Hoenn field scripts and pedestrian access to their NPCs."""
from collections import deque
import json
from pathlib import Path
import re
import struct
import unittest
from test_prologue import ROOT, run_event, REGISTERED, PATIENT, OBSERVED, BRIEFED

ASSIGNED = 'FLAG_LEGACY_FIELD_ASSIGNED'
FIELD_OBSERVED = 'FLAG_LEGACY_FIELD_OBSERVED'
REPORTED = 'FLAG_LEGACY_FIELD_REPORTED'
WAITED = 'FLAG_LEGACY_FIELD_WAITED'
BASE = {REGISTERED, OBSERVED, BRIEFED}


class FieldResearchTests(unittest.TestCase):
    def test_assignment_requires_the_first_observation(self):
        flags, messages, _, locked = run_event('LegacyField_EventScript_MissionDesk')
        self.assertNotIn(ASSIGNED, flags)
        self.assertEqual(messages, ['LegacyField_Text_FinishFirstObservation'])
        self.assertFalse(locked)

    def test_assignment_can_be_declined_and_later_accepted(self):
        flags, _, _, locked = run_event('Legacy_EventScript_Researcher', BASE, [0])
        self.assertEqual(flags, BASE)
        self.assertFalse(locked)
        flags, messages, _, locked = run_event('Legacy_EventScript_Researcher', flags, [1])
        self.assertEqual(flags, BASE | {ASSIGNED})
        self.assertIn('LegacyField_Text_Directions', messages)
        self.assertFalse(locked)

    def test_route_interactions_do_not_start_an_unassigned_mission(self):
        for label, message in (
            ('LegacyField_EventScript_FieldResearcher', 'LegacyField_Text_CampNotReady'),
            ('LegacyField_EventScript_ObserveZigzagoon', 'LegacyField_Text_ZigzagoonBeforeAssignment'),
        ):
            flags, messages, _, locked = run_event(label, BASE)
            self.assertEqual(flags, BASE)
            self.assertEqual(messages, [message])
            self.assertFalse(locked)

    def test_advice_recalls_the_original_decision(self):
        for patient in (False, True):
            before = BASE | {ASSIGNED} | ({PATIENT} if patient else set())
            flags, messages, _, locked = run_event('LegacyField_EventScript_FieldResearcher', before)
            self.assertEqual(flags, before)
            expected = 'LegacyField_Text_PatienceAdvice' if patient else 'LegacyField_Text_DistanceAdvice'
            self.assertIn(expected, messages)
            self.assertFalse(locked)

    def test_new_decision_does_not_overwrite_the_first_and_cannot_be_repeated(self):
        for prior in (False, True):
            for answer in (0, 1):
                before = BASE | {ASSIGNED} | ({PATIENT} if prior else set())
                flags, _, _, locked = run_event('LegacyField_EventScript_ObserveZigzagoon', before, [answer])
                self.assertIn(FIELD_OBSERVED, flags)
                self.assertEqual(PATIENT in flags, prior)
                self.assertEqual(WAITED in flags, bool(answer))
                self.assertFalse(locked)
                saved = set(flags)
                flags, _, _, locked = run_event('LegacyField_EventScript_ObserveZigzagoon', saved)
                self.assertEqual(flags, saved)
                self.assertFalse(locked)

    def test_report_requires_notes_and_is_filed_once(self):
        before = BASE | {ASSIGNED}
        flags, messages, _, locked = run_event('Legacy_EventScript_Researcher', before)
        self.assertEqual(flags, before)
        self.assertEqual(messages, ['LegacyField_Text_Directions'])
        self.assertFalse(locked)
        for waited in (False, True):
            before = BASE | {ASSIGNED, FIELD_OBSERVED} | ({WAITED} if waited else set())
            flags, messages, _, locked = run_event('Legacy_EventScript_Researcher', before)
            self.assertEqual(flags, before | {REPORTED})
            expected = 'LegacyField_Text_PatientReport' if waited else 'LegacyField_Text_PassageReport'
            self.assertIn(expected, messages)
            self.assertFalse(locked)
            saved = set(flags)
            flags, messages, _, locked = run_event('Legacy_EventScript_Researcher', saved)
            self.assertEqual(flags, saved)
            self.assertEqual(messages, ['LegacyField_Text_ReportAlreadyFiled'])
            self.assertFalse(locked)

    def test_journal_keeps_the_first_entry_and_adds_each_field_stage(self):
        for extra, expected in (
            ({ASSIGNED}, 'LegacyField_Text_JournalAssigned'),
            ({ASSIGNED, FIELD_OBSERVED}, 'LegacyField_Text_JournalReturn'),
            ({ASSIGNED, FIELD_OBSERVED, REPORTED}, 'LegacyField_Text_JournalPassageReport'),
            ({ASSIGNED, FIELD_OBSERVED, REPORTED, WAITED}, 'LegacyField_Text_JournalPatientReport'),
        ):
            before = BASE | extra
            flags, messages, _, locked = run_event('Legacy_EventScript_ResearchJournal', before)
            self.assertEqual(messages, ['Legacy_Text_DistanceJournal', expected])
            self.assertEqual(flags, before)
            self.assertFalse(locked)

    def test_looking_around_requires_a_completed_patient_observation(self):
        for flags in (BASE, BASE | {WAITED}, BASE | {FIELD_OBSERVED}, BASE | {FIELD_OBSERVED, WAITED}):
            updates = []
            result, _, _, locked = run_event('LegacyField_EventScript_Route102Transition', flags,
                                             movement_updates=updates)
            expected = [('LOCALID_LEGACY_FIELD_ZIGZAGOON', 'MOVEMENT_TYPE_LOOK_AROUND')] if WAITED in flags and FIELD_OBSERVED in flags else []
            self.assertEqual(updates, expected)
            self.assertEqual(result, flags)
            self.assertFalse(locked)

    def test_field_flags_use_separate_existing_permanent_bits(self):
        header = (ROOT / 'include/constants/flags.h').read_text()
        for index, name in enumerate((ASSIGNED, FIELD_OBSERVED, REPORTED, WAITED), 0x24):
            value = int(re.search(r'^#define ' + name + r'\s+(0x[0-9A-Fa-f]+)', header, re.M)[1], 16)
            self.assertEqual(value, index)
            self.assertGreater(value, 0x23)
            self.assertLess(value, 0x900)

    def test_route_access_without_surf_and_original_object_order(self):
        mapdata = json.loads((ROOT / 'data/maps/Route102/map.json').read_text())
        original_scripts = ['Route102_EventScript_LittleBoy', 'Route102_EventScript_Calvin',
                            'Route102_EventScript_Rick', 'Route102_EventScript_Tiana',
                            'Route102_EventScript_Boy', 'Common_EventScript_FindItem',
                            'BerryTreeScript', 'BerryTreeScript', 'Route102_EventScript_Allen']
        self.assertEqual([o['script'] for o in mapdata['object_events'][:9]], original_scripts)
        self.assertLessEqual(len(mapdata['object_events']), 16)
        layout = next(l for l in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
                      if l['id'] == 'LAYOUT_ROUTE102')
        w, h = layout['width'], layout['height']
        blocks = struct.unpack('<' + 'H' * (w * h), (ROOT / layout['blockdata_filepath']).read_bytes())
        attrs = []
        for f in ('primary/general', 'secondary/petalburg'):
            b = (ROOT / f'data/tilesets/{f}/metatile_attributes.bin').read_bytes()
            attrs.append(struct.unpack('<' + 'H' * (len(b) // 2), b))
        header = re.sub(r'//[^\n]*', '', (ROOT / 'include/constants/metatile_behaviors.h').read_text())
        names = re.findall(r'\bMB_\w+', header.split('enum {', 1)[1].split('}', 1)[0])
        safe = {'MB_NORMAL', 'MB_TALL_GRASS', 'MB_LONG_GRASS', 'MB_SHORT_GRASS', 'MB_PUDDLE', 'MB_FOOTPRINTS'}
        occupied = {(o['x'], o['y']) for o in mapdata['object_events']}
        def neighbors(p):
            x, y = p
            return [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]
        def passable(p):
            x, y = p
            if not (0 <= x < w and 0 <= y < h) or p in occupied:
                return False
            block = blocks[y * w + x]
            n = block & 1023
            return not block & 0xC00 and names[attrs[n >= 512][n % 512] & 255] in safe
        def flood(start):
            reached, pending = {start}, deque([start])
            while pending:
                for p in neighbors(pending.popleft()):
                    if p not in reached and passable(p):
                        reached.add(p)
                        pending.append(p)
            return reached
        reached = flood((49, 10))  # Entrance from Oldale.
        self.assertIn((0, 6), reached)  # Exit toward Petalburg remains open.
        for obj in mapdata['object_events'][9:]:
            self.assertEqual(blocks[obj['y'] * w + obj['x']] >> 12, obj['elevation'])
            self.assertTrue(any(p in reached for p in neighbors((obj['x'], obj['y']))), obj)
        # All original traversable tiles remain reachable: the additions do not cut a corridor.
        occupied.difference_update((o['x'], o['y']) for o in mapdata['object_events'][9:])
        baseline = flood((49, 10))
        added_positions = {(o['x'], o['y']) for o in mapdata['object_events'][9:]}
        self.assertEqual(baseline - reached, added_positions)


if __name__ == '__main__':
    unittest.main()
