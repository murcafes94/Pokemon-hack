"""Native east-Kanto terrain, return routes and optional encounter flows."""
import json
import re
import unittest
from test_prologue import ROOT, run_event
from test_kanto_expedition import resources, flood

RANGER = 'TRAINER_LEGACY_ROUTE3_RANGER'
BADGE = 'FLAG_LEGACY_BADGE_BOULDER'
CIRCUIT = 'TRAINER_LEGACY_BROCK_CIRCUIT'

class EastKantoTests(unittest.TestCase):
    def test_town_connection_and_cave_warps_allow_round_trip(self):
        town = resources('LegacyKanto_PewterCity')[0]
        route = resources('LegacyKanto_Route3')[0]
        cave = resources('LegacyKanto_MoonChamber')[0]
        self.assertIn(dict(map=route['id'], direction='right', offset=0), town['connections'])
        self.assertIn(dict(map=town['id'], direction='left', offset=0), route['connections'])
        town_seen = flood(town['name'], (12,18))
        route_seen = flood(route['name'], (0,12))
        for y in (11,12,13):
            self.assertIn((23,y), town_seen)
            self.assertIn((0,y), route_seen)
        for data, start in [(route,(0,12)),(cave,(11,18))]:
            seen = flood(data['name'],start)
            for warp in data['warp_events']:
                self.assertIn((warp['x'],warp['y']),seen)
            for obj in data['object_events']:
                self.assertTrue(any(p in seen for p in [(obj['x']+1,obj['y']), (obj['x']-1,obj['y']), (obj['x'],obj['y']+1),(obj['x'],obj['y']-1)]))
        for source, dest in [(route,cave),(cave,route)]:
            warp = source['warp_events'][0]
            self.assertEqual(warp['dest_map'],dest['id'])
            self.assertEqual(dest['warp_events'][int(warp['dest_warp_id'])]['dest_map'],source['id'])
        self.assertFalse(cave['requires_flash'])
        self.assertTrue(cave['allow_escaping'])
        self.assertEqual(cave['map_type'],'MAP_TYPE_UNDERGROUND')

    def test_map_music_is_present_in_the_engine_song_table(self):
        definitions = (ROOT/'include/constants/songs.h').read_text()
        songs = (ROOT/'sound/song_table.inc').read_text()
        for name, music in [('LegacyKanto_Route3','MUS_RG_ROUTE3'),('LegacyKanto_MoonChamber','MUS_RG_MT_MOON')]:
            data = resources(name)[0]
            self.assertEqual(data['music'],music)
            self.assertRegex(definitions,r'#define '+music+r'\s+\d+')
            self.assertIn('song '+music.lower()+',',songs)

    def test_ranger_is_optional_and_records_only_his_trainer_flag(self):
        flags = {'FLAG_BADGE01_GET', BADGE, CIRCUIT, 'FLAG_LEGACY_APPROACH_PATIENTLY'}
        for answer, wins in [(0,True),(1,False)]:
            after,_,warp,locked = run_event('LegacyEast_EventScript_Ranger',flags,[answer],trainer_wins=wins)
            self.assertEqual(after,flags)
            self.assertIsNone(warp)
            self.assertFalse(locked)
        after,messages,_,locked = run_event('LegacyEast_EventScript_Ranger',flags,[1])
        self.assertEqual(after, flags | {RANGER})
        self.assertIn('LegacyEast_Text_RangerDone',messages)
        self.assertFalse(locked)
        repeated,messages,_,locked = run_event('LegacyEast_EventScript_Ranger',after)
        self.assertEqual(repeated,after)
        self.assertNotIn('LegacyEast_Text_RangerOffer',messages)
        self.assertFalse(locked)

    def test_research_dialogue_recognizes_progress_without_changing_it(self):
        for flags, expected in [(set(),'ResearchNotes'),({CIRCUIT},'CircuitNotes')]:
            after,messages,warp,locked = run_event('LegacyEast_EventScript_MoonNotes',flags)
            self.assertEqual(after,flags)
            self.assertIn('LegacyEast_Text_'+expected,messages)
            self.assertFalse(locked)
            self.assertIsNone(warp)
        for flags, expected in [(set(),'CampBeforeBadge'),({BADGE},'CampAfterBadge')]:
            after,messages,_,locked = run_event('LegacyEast_EventScript_Camp',flags)
            self.assertEqual(after,flags)
            self.assertIn('LegacyEast_Text_'+expected,messages)
            self.assertFalse(locked)
        after,_,_,locked = run_event('LegacyEast_EventScript_Clefairy',{BADGE})
        self.assertEqual(after,{BADGE})
        self.assertFalse(locked)

    def test_encounters_include_clefairy_and_optional_paths_avoid_grass(self):
        encounters = json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]['encounters']
        for suffix, levels in [('ROUTE3',(54,57)),('MOONCHAMBER',(55,58))]:
            table = next(e for e in encounters if e['map']=='MAP_LEGACY_KANTO_'+suffix)['land_mons']
            self.assertEqual(len(table['mons']),12)
            for mon in table['mons']:
                self.assertEqual((mon['min_level'],mon['max_level']),levels)
        table = next(e for e in encounters if e['map']=='MAP_LEGACY_KANTO_MOONCHAMBER')['land_mons']
        self.assertIn('SPECIES_CLEFAIRY',{m['species'] for m in table['mons']})
        # All cells in the principal trail are plain ground, not tall grass.
        _,_,w,_,tiles = resources('LegacyKanto_Route3')
        points = [(x,12) for x in range(17)] + [(16,y) for y in range(12,17)] + [(x,16) for x in range(16,33)] + [(32,y) for y in range(10,17)]
        self.assertTrue(all(tiles[y*w+x] & 1023 == 0x2BB for x,y in points))
        self.assertGreater(sum(t & 1023 == 0xD for t in tiles),0)
        _,_,_,_,tiles = resources('LegacyKanto_MoonChamber')
        self.assertGreater(sum(t & 1023 == 0x211 for t in tiles),0)

    def test_map_and_trainer_ids_append_without_expanding_save_capacity(self):
        groups = json.loads((ROOT/'data/maps/map_groups.json').read_text())['gMapGroup_LegacyKanto']
        self.assertEqual(groups[:8],['LegacyKanto_ArrivalPort','LegacyKanto_Route1','LegacyKanto_ViridianOutpost','LegacyKanto_ResearchStation','LegacyKanto_Route2','LegacyKanto_ViridianForest','LegacyKanto_PewterCity','LegacyKanto_PewterGym'])
        self.assertEqual(groups[8:10],['LegacyKanto_Route3','LegacyKanto_MoonChamber'])
        header = (ROOT/'include/constants/opponents.h').read_text()
        self.assertRegex(header,r'TRAINER_LEGACY_ROUTE3_RANGER\s+858')
        self.assertRegex(header,r'MAX_TRAINERS_COUNT_EMERALD\s+864')
        party = (ROOT/'src/data/trainers.party').read_text().split('=== TRAINER_LEGACY_ROUTE3_RANGER ===')[1].split('=== TRAINER_LEGACY_MISTY ===')[0]
        self.assertEqual(re.findall(r'Level: (\d+)',party),['58','59'])
        source = (ROOT/'data/scripts/legacy_kanto_east.inc').read_text()
        self.assertNotRegex(source,r'\b(setflag|clearflag|giveitem)\b')
