"""Verify native test shortcuts, including cancellation and story/save boundaries."""
import subprocess
import tempfile
import unittest
from test_prologue import ROOT, run_event
from test_forest_research import BASE, JOINED, SHROOM, WURM, FILED, DISTANCE, QUIET, reachable, MAP
from test_field_research import ASSIGNED, REPORTED


class DebugShortcutsTests(unittest.TestCase):
    def test_native_generators_report_capacity_failures_and_accept_large_item_ids(self):
        # Compile the actual C callbacks with mocked storage APIs. Full ROM
        # compilation checks their integration; these cases check result handling.
        source = (ROOT / 'src/debug.c').read_text()
        bodies = []
        for name in ('DebugSelection_GiveItem_Complete', 'DebugSelection_GiveSimplePokemon_OnComplete'):
            start = source.index('static bool32 ' + name + '(u8 taskId)\n{')
            stop = source.index('\n}', start) + 2
            bodies.append(source[start:stop])
        harness = '''
#include <assert.h>
typedef unsigned int u32;
typedef unsigned char u8;
typedef int bool32;
#define TRUE 1
#define ITEM_NONE 0
#define MON_CANT_GIVE 2
#define SE_SUCCESS 1
#define SE_FAILURE 2
static int allowed, sound, returned;
static u32 DebugSelection_GetData(u8 task, u32 slot) { return slot ? 23 : 1005; }
static bool32 AddBagItem(u32 item, u32 amount) { assert(item == 1005 && amount == 23); return allowed; }
static u32 ScriptGiveMon(u32 species, u32 level, u32 item) { return allowed ? 0 : MON_CANT_GIVE; }
static void DebugSelectionStep_ReturnToGiveMenu(u8 task) { returned++; }
static void PlaySE(u32 value) { sound = value; }
''' + '\n'.join(bodies) + '''
int main(void) {
    for (allowed = 0; allowed <= 1; allowed++) {
        assert(DebugSelection_GiveItem_Complete(0));
        assert(sound == (allowed ? SE_SUCCESS : SE_FAILURE));
        assert(DebugSelection_GiveSimplePokemon_OnComplete(0));
        assert(sound == (allowed ? SE_SUCCESS : SE_FAILURE));
    }
    assert(returned == 4);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            exe = tmp + '/callbacks'
            subprocess.run(['cc', '-x', 'c', '-o', exe, '-'], input=harness,
                           text=True, capture_output=True, check=True)
            subprocess.run([exe], check=True)

    def test_kit_requires_confirmation_and_never_changes_story_flags(self):
        for answer in (0, 1):
            items = []
            flags, _, _, locked = run_event('LegacyDebug_EventScript_Kit', BASE, [answer], items=items)
            self.assertEqual(flags, BASE)
            self.assertFalse(locked)
            expected = [('ITEM_POKE_BALL', '20'), ('ITEM_POTION', '10'),
                        ('ITEM_ANTIDOTE', '10'), ('ITEM_REPEL', '5')] if answer else []
            self.assertEqual(items, expected)

    def test_full_bag_stops_kit_and_does_not_claim_success(self):
        items = []
        flags, messages, _, locked = run_event('LegacyDebug_EventScript_Kit', BASE, [1],
                                              items=items, bag_accepts=False)
        self.assertEqual(flags, BASE)
        self.assertEqual(items, [])
        self.assertEqual(messages[-1], 'LegacyDebug_Text_BagFull')
        self.assertNotIn('LegacyDebug_Text_KitDone', messages)
        self.assertFalse(locked)

    def test_shortcuts_refuse_unfinished_story_points(self):
        for destination, flags, lab, woods in (
            ('Annex', BASE, 3, 1), ('Route', set(), 5, 1),
            ('Woods', set(), 5, 1), ('Woods', BASE, 5, 0),
            ('Clearing', BASE, 5, 1), ('Clearing', BASE | {JOINED}, 5, 0),
        ):
            after, messages, warp, locked = run_event('LegacyDebug_EventScript_' + destination,
                                                       flags, lab_state=lab, woods_state=woods)
            self.assertEqual(after, flags)
            self.assertIsNone(warp)
            self.assertEqual(messages, ['LegacyDebug_Text_NotReady'])
            self.assertFalse(locked)

    def test_unlocked_shortcuts_preserve_flags_and_have_reachable_landings(self):
        for destination, flags, expected in (
            ('Annex', BASE, ('MAP_LITTLEROOT_TOWN_LEGACY_RESEARCH_ANNEX', '6', '8')),
            ('Route', BASE, ('MAP_ROUTE102', '28', '6')),
            ('Woods', BASE, ('MAP_PETALBURG_WOODS', '18', '34')),
            ('Clearing', BASE | {JOINED}, ('MAP_PETALBURG_WOODS_LEGACY_CLEARING', '11', '16')),
        ):
            after, _, warp, locked = run_event('LegacyDebug_EventScript_' + destination, flags)
            self.assertEqual(after, flags)
            self.assertEqual(warp, expected)
            self.assertFalse(locked)
        self.assertIn((18, 34), reachable('PetalburgWoods', (18, 34)))
        self.assertIn((11, 16), reachable(MAP, (11, 16)))

    def test_replay_cancels_or_only_clears_five_forest_bits(self):
        saved = BASE | {JOINED, SHROOM, WURM, FILED, DISTANCE, QUIET, 'FLAG_BADGE01_GET'}
        for answer in (0, 1):
            flags, _, _, locked = run_event('LegacyDebug_EventScript_ReplayForest', saved, [answer])
            self.assertEqual(flags, saved - {SHROOM, WURM, FILED, DISTANCE, QUIET} if answer else saved)
            self.assertFalse(locked)

    def test_opening_journal_does_not_write_or_teleport(self):
        flags, messages, warp, locked = run_event('LegacyDebug_EventScript_Journal', BASE | {JOINED})
        self.assertEqual(flags, BASE | {JOINED})
        self.assertIn('LegacyForest_Text_JournalOpen', messages)
        self.assertIsNone(warp)
        self.assertFalse(locked)

    def test_cpp_disables_quick_menu_and_scripts_on_release(self):
        source = '''#include "constants/global.h"
#include "config/debug.h"
#if DEBUG_OVERWORLD_MENU
LEGACY_TEST_MENU_ENABLED
#endif
'''
        def preprocess(extra):
            return subprocess.run(['cpp', '-P', '-I', str(ROOT / 'include'), '-DTRUE=1', '-DFALSE=0', *extra, '-'],
                                  input=source, text=True, check=True, capture_output=True).stdout
        self.assertIn('LEGACY_TEST_MENU_ENABLED', preprocess([]))
        self.assertNotIn('LEGACY_TEST_MENU_ENABLED', preprocess(['-DRELEASE']))
        # The same condition surrounds the actual C submenu and ASM script include.
        c = (ROOT / 'src/debug.c').read_text()
        self.assertIn('#if DEBUG_OVERWORLD_MENU\nextern const u8 LegacyDebug_EventScript_Kit[];', c)
        self.assertIn('#if DEBUG_OVERWORLD_MENU\n    { COMPOUND_STRING("Legacy rápido…")', c)
        asm = (ROOT / 'data/event_scripts.s').read_text()
        self.assertIn('\t.if DEBUG_OVERWORLD_MENU\n\t.include "data/scripts/legacy_debug.inc"\n\t.endif', asm)

    def test_assembler_condition_uses_native_true_false_symbols(self):
        # ASM scripts define TRUE/FALSE as assembler symbols, not CPP macros.
        # A CPP #if would silently omit the scripts even in a development ROM.
        source = '''#include "constants/global.h"
.set TRUE, 1
.set FALSE, 0
.if DEBUG_OVERWORLD_MENU
.global legacy_debug_probe
legacy_debug_probe:
.byte 0
.endif
'''
        with tempfile.TemporaryDirectory() as tmp:
            for release in (False, True):
                cpp = subprocess.run(['cpp', '-P', '-I', str(ROOT / 'include'),
                                      *(['-DRELEASE'] if release else []), '-'],
                                     input=source, text=True, check=True, capture_output=True).stdout
                # The project preproc tool converts the preceding C enums for
                # ARM ASM; this host probe needs only the conditional block.
                cpp = cpp[cpp.index('.set TRUE'):]
                obj = tmp + '/probe.o'
                subprocess.run(['cc', '-x', 'assembler', '-c', '-o', obj, '-'], input=cpp,
                               text=True, capture_output=True, check=True)
                symbols = subprocess.run(['nm', obj], text=True, capture_output=True, check=True).stdout
                self.assertEqual('legacy_debug_probe' in symbols, not release)


if __name__ == '__main__':
    unittest.main()
