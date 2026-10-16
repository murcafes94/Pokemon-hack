"""Optional circuit respects the existing badge and research progress."""
import unittest
from test_prologue import run_event
BADGE = 'FLAG_LEGACY_BADGE_BOULDER'
RESEARCH = 'FLAG_LEGACY_FIRST_OBSERVATION'
TRAINER = 'TRAINER_LEGACY_BROCK_CIRCUIT'

class CircuitTests(unittest.TestCase):
    def test_requires_research_without_changing_existing_progress(self):
        flags = {BADGE, 'FLAG_SYS_GAME_CLEAR', 'FLAG_BADGE01_GET'}
        after, messages, _, locked = run_event('LegacyNorth_EventScript_Brock', flags)
        self.assertEqual(after, flags)
        self.assertIn('LegacyCircuit_Text_ResearchFirst', messages)
        self.assertFalse(locked)

    def test_cancel_loss_win_and_repeat(self):
        flags = {BADGE, RESEARCH, 'FLAG_SYS_GAME_CLEAR', 'FLAG_BADGE08_GET'}
        for answer, wins in [(0, True), (1, False)]:
            after, _, _, locked = run_event('LegacyNorth_EventScript_Brock', flags, [answer], trainer_wins=wins)
            self.assertEqual(after, flags)
            self.assertFalse(locked)
        after, messages, _, locked = run_event('LegacyNorth_EventScript_Brock', flags, [1])
        self.assertEqual(after, flags | {TRAINER})
        self.assertIn('LegacyCircuit_Text_Completed', messages)
        self.assertFalse(locked)
        repeated, messages, _, locked = run_event('LegacyNorth_EventScript_Brock', after)
        self.assertEqual(repeated, after)
        self.assertNotIn('LegacyCircuit_Text_Offer', messages)
        self.assertFalse(locked)

    def test_field_desk_changes_with_badge_and_preserves_flags(self):
        for flags, text in [(set(), 'DeskBadge'), ({BADGE}, 'DeskReady')]:
            after, messages, _, locked = run_event('LegacyCircuit_EventScript_FieldDesk', flags)
            self.assertEqual(after, flags)
            self.assertIn('LegacyCircuit_Text_' + text, messages)
            self.assertFalse(locked)
