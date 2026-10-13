"""Check the actual introductory scripts and native map without emulating the GBA."""
import json
from pathlib import Path
import re
import struct
import unittest
from collections import deque

ROOT = Path(__file__).resolve().parents[2]
ANNEX = 'LittlerootTown_LegacyResearchAnnex'
REGISTERED = 'FLAG_LEGACY_RESEARCH_REGISTERED'
PATIENT = 'FLAG_LEGACY_APPROACH_PATIENTLY'
OBSERVED = 'FLAG_LEGACY_FIRST_OBSERVATION'
BRIEFED = 'FLAG_LEGACY_PROLOGUE_BRIEFED'


def script_program():
    labels, code = {}, []
    for line in (ROOT / 'data/scripts/legacy_prologue.inc').read_text().splitlines():
        line = line.split('@', 1)[0].strip()
        if not line or line.startswith('.'):
            continue
        if line.endswith('::'):
            labels[line[:-2]] = len(code)
        else:
            command, _, args = line.partition(' ')
            code.append((command, [a.strip() for a in args.split(',')] if args else []))
    return labels, code


def run_event(label, flags=(), responses=(), lab_state=5):
    labels, code = script_program()
    flags = set(flags)
    responses = iter(responses)
    variables = {'VAR_BIRCH_LAB_STATE': lab_state, 'VAR_RESULT': 0}
    constants = {'YES': 1, 'NO': 0}
    stack, messages, warp = [], [], None
    locked = False
    pc = labels[label]
    for _ in range(200):
        command, args = code[pc]
        pc += 1
        if command == 'end':
            return flags, messages, warp, locked
        if command == 'return':
            if not stack:
                return flags, messages, warp, locked
            pc = stack.pop()
        elif command in ('lock', 'lockall'):
            locked = True
        elif command in ('release', 'releaseall'):
            locked = False
        elif command in ('faceplayer', 'waitmoncry', 'playmoncry', 'closemessage', 'waitstate'):
            pass
        elif command == 'setflag':
            flags.add(args[0])
        elif command == 'clearflag':
            flags.discard(args[0])
        elif command == 'msgbox':
            messages.append(args[0])
            if args[1] == 'MSGBOX_YESNO':
                variables['VAR_RESULT'] = next(responses)
        elif command == 'warp':
            warp = tuple(args)
        elif command == 'goto':
            pc = labels[args[0]]
        elif command in ('goto_if_set', 'goto_if_unset', 'call_if_unset'):
            condition = args[0] in flags
            if command.endswith('unset'):
                condition = not condition
            if condition:
                if command.startswith('call'):
                    stack.append(pc)
                pc = labels[args[1]]
        elif command in ('goto_if_eq', 'goto_if_lt'):
            a = variables[args[0]]
            b = constants.get(args[1], int(args[1]) if args[1].isdigit() else None)
            if (a == b if command.endswith('eq') else a < b):
                pc = labels[args[2]]
        else:
            raise AssertionError(f'Unmodelled story command: {command}')
    raise AssertionError('Story event did not terminate')


class PrologueTests(unittest.TestCase):
    def test_exit_tiles_have_the_expected_directional_warp_behavior(self):
        header = (ROOT / 'include/constants/metatile_behaviors.h').read_text()
        header = re.sub(r'//[^\n]*', '', header)
        enum_names = re.findall(r'\bMB_\w+', header.split('enum {', 1)[1].split('}', 1)[0])
        attrs = (ROOT / 'data/tilesets/secondary/lab/metatile_attributes.bin').read_bytes()
        for index in (6, 7):
            behavior = struct.unpack_from('<H', attrs, index * 2)[0] & 0xFF
            self.assertEqual(behavior, enum_names.index('MB_SOUTH_ARROW_WARP'))

    def test_story_flags_are_permanent_and_within_the_existing_save(self):
        header = (ROOT / 'include/constants/flags.h').read_text()
        for index, name in enumerate((REGISTERED, PATIENT, OBSERVED, BRIEFED), 0x20):
            value = int(re.search(r'^#define ' + name + r'\s+(0x[0-9A-Fa-f]+)', header, re.M)[1], 16)
            self.assertEqual(value, index)
            self.assertGreater(value, 0x1F)  # Map-local temporary flags end here.
            self.assertLess(value, 0x900)   # Both base games already allocate these bits.

    def test_early_visit_does_not_advance_the_story(self):
        for label in ('Legacy_EventScript_Researcher', 'Legacy_EventScript_AnnexGuide'):
            flags, messages, warp, locked = run_event(label, lab_state=3)
            self.assertFalse(flags)
            self.assertIsNone(warp)
            self.assertFalse(locked)
            self.assertEqual(messages, ['Legacy_Text_FinishBirchsTask'])

    def test_join_can_be_declined_and_later_accepted(self):
        flags, _, _, locked = run_event('Legacy_EventScript_Researcher', responses=[0])
        self.assertNotIn(REGISTERED, flags)
        self.assertIn(BRIEFED, flags)
        self.assertFalse(locked)
        flags, messages, _, locked = run_event('Legacy_EventScript_Researcher', flags, [1])
        self.assertIn(REGISTERED, flags)
        self.assertNotIn('Legacy_Text_BirchResearchBriefing', messages)
        self.assertFalse(locked)

    def test_observation_requires_registration(self):
        flags, messages, _, locked = run_event('Legacy_EventScript_FirstObservation')
        self.assertNotIn(OBSERVED, flags)
        self.assertEqual(messages, ['Legacy_Text_RegisterFirst'])
        self.assertFalse(locked)

    def test_both_decisions_persist_and_cannot_be_changed_by_repeating(self):
        for answer in (0, 1):
            flags, _, _, locked = run_event('Legacy_EventScript_FirstObservation', [REGISTERED], [answer])
            self.assertIn(OBSERVED, flags)
            self.assertEqual(PATIENT in flags, bool(answer))
            self.assertFalse(locked)
            # Reconstruct state as after loading the stored flags.
            saved = set(flags)
            flags, messages, _, locked = run_event('Legacy_EventScript_FirstObservation', saved)
            self.assertEqual(flags, saved)
            self.assertEqual(messages, ['Legacy_Text_PoochyenaRecognizesYou'])
            self.assertFalse(locked)
            _, journal, _, locked = run_event('Legacy_EventScript_ResearchJournal', saved)
            expected = 'Legacy_Text_PatientJournal' if answer else 'Legacy_Text_DistanceJournal'
            self.assertEqual(journal, [expected])
            self.assertFalse(locked)

    def test_guide_transitions_only_after_accepting(self):
        for answer in (0, 1):
            _, _, warp, locked = run_event('Legacy_EventScript_AnnexGuide', responses=[answer])
            self.assertEqual(warp is not None, bool(answer))
            self.assertFalse(locked)

    def test_native_map_can_reach_exit_and_all_interactions(self):
        layout = next(l for l in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
                      if l['id'] == 'LAYOUT_LITTLEROOT_TOWN_LEGACY_RESEARCH_ANNEX')
        w, h = layout['width'], layout['height']
        raw = (ROOT / layout['blockdata_filepath']).read_bytes()
        self.assertEqual(len(raw), w * h * 2)
        blocks = struct.unpack('<' + 'H' * (w * h), raw)
        mapdata = json.loads((ROOT / f'data/maps/{ANNEX}/map.json').read_text())
        occupied = {(o['x'], o['y']) for o in mapdata['object_events']}
        def neighbors(p):
            x, y = p
            return [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]
        def passable(p):
            x, y = p
            return 0 <= x < w and 0 <= y < h and not blocks[y * w + x] & 0xC00 and p not in occupied
        reached, pending = {(6, 8)}, deque([(6, 8)])
        while pending:
            for p in neighbors(pending.popleft()):
                if p not in reached and passable(p):
                    reached.add(p)
                    pending.append(p)
        for warp in mapdata['warp_events']:
            self.assertIn((warp['x'], warp['y']), reached)
            destination = json.loads((ROOT / 'data/maps/LittlerootTown_ProfessorBirchsLab/map.json').read_text())
            dest = destination['warp_events'][int(warp['dest_warp_id'])]
            self.assertEqual((dest['x'], dest['y']), (11, 5))
        for event in mapdata['object_events'] + mapdata['bg_events']:
            self.assertTrue(any(p in reached for p in neighbors((event['x'], event['y']))), event)
        # Return position and guide access are valid in both existing lab layouts.
        for name in ('LittlerootTown_ProfessorBirchsLab', 'LittlerootTown_ProfessorBirchsLabWithTable'):
            raw = (ROOT / f'data/layouts/{name}/map.bin').read_bytes()
            for x, y in ((11, 4), (11, 5)):
                self.assertEqual(struct.unpack_from('<H', raw, 2 * (y * 13 + x))[0] & 0xC00, 0)
            lab = json.loads((ROOT / 'data/maps/LittlerootTown_ProfessorBirchsLab/map.json').read_text())
            occupied = {(o['x'], o['y']) for o in lab['object_events']}
            occupied.update({(8, 4), (9, 4), (10, 4), (5, 5), (6, 4)})
            lab_blocks = struct.unpack('<169H', raw[:338])
            reached, pending = {(11, 5)}, deque([(11, 5)])
            while pending:
                for x, y in neighbors(pending.popleft()):
                    if (0 <= x < 13 and 0 <= y < 13 and (x, y) not in occupied
                            and (x, y) not in reached and not lab_blocks[y * 13 + x] & 0xC00):
                        reached.add((x, y))
                        pending.append((x, y))
            self.assertIn((6, 12), reached, name)

    def test_annex_is_appended_after_all_existing_littleroot_maps(self):
        groups = json.loads((ROOT / 'data/maps/map_groups.json').read_text())
        self.assertEqual(groups['gMapGroup_IndoorLittleroot'], [
            'LittlerootTown_BrendansHouse_1F', 'LittlerootTown_BrendansHouse_2F',
            'LittlerootTown_MaysHouse_1F', 'LittlerootTown_MaysHouse_2F',
            'LittlerootTown_ProfessorBirchsLab', ANNEX])


if __name__ == '__main__':
    unittest.main()
