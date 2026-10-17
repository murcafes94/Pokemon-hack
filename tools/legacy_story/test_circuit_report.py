"""Optional Hoenn synthesis preserves research progress and existing saves."""
import unittest
from test_prologue import run_event

BROCK = 'TRAINER_LEGACY_BROCK_CIRCUIT'
MISTY = 'TRAINER_LEGACY_MISTY_CIRCUIT'
FIRST = 'FLAG_LEGACY_FIRST_OBSERVATION'


class CircuitReportTests(unittest.TestCase):
    def test_requires_both_exhibitions(self):
        for flags in [set(), {BROCK}, {MISTY}]:
            after, messages, _, locked = run_event('LegacyField_EventScript_MissionDesk', flags)
            self.assertEqual(after, flags)
            self.assertNotIn('LegacyField_Text_CircuitReportOffer', messages)
            self.assertFalse(locked)

    def test_report_is_repeatable_and_does_not_change_progress(self):
        flags = {FIRST, BROCK, MISTY, 'FLAG_BADGE08_GET', 'FLAG_LEGACY_FIELD_ASSIGNED'}
        for _ in range(2):
            after, messages, _, locked = run_event('LegacyField_EventScript_MissionDesk', flags, [1])
            self.assertEqual(after, flags)
            self.assertIn('LegacyField_Text_CircuitReport', messages)
            self.assertNotIn('LegacyField_Text_Directions', messages)
            self.assertFalse(locked)

    def test_declining_report_keeps_field_assignment_available(self):
        flags = {FIRST, BROCK, MISTY}
        after, messages, _, locked = run_event('LegacyField_EventScript_MissionDesk', flags, [0, 1])
        self.assertEqual(after, flags | {'FLAG_LEGACY_FIELD_ASSIGNED'})
        self.assertIn('LegacyField_Text_Directions', messages)
        self.assertNotIn('LegacyField_Text_CircuitReport', messages)
        self.assertFalse(locked)

    def test_declining_returns_to_existing_forest_mission(self):
        flags = {FIRST, BROCK, MISTY, 'FLAG_LEGACY_FOREST_ASSIGNED'}
        baseline = run_event('LegacyField_EventScript_ResearchDesk', flags)
        actual = run_event('LegacyField_EventScript_MissionDesk', flags, [0])
        self.assertEqual(actual[0], baseline[0])
        self.assertEqual(actual[1][1:], baseline[1])
        self.assertEqual(actual[2:], baseline[2:])

    def test_annex_researcher_reaches_report_from_saved_progress(self):
        flags = {FIRST, BROCK, MISTY, 'FLAG_LEGACY_FIELD_ASSIGNED',
                 'FLAG_LEGACY_PROLOGUE_BRIEFED'}
        after, messages, _, locked = run_event('Legacy_EventScript_Researcher', flags, [1])
        self.assertEqual(after, flags)
        self.assertIn('LegacyField_Text_CircuitReport', messages)
        self.assertFalse(locked)
