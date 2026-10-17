"""Celeste traversal, recovery, independent badges and optional exhibitions."""
import json,re,unittest
from test_prologue import ROOT,run_event
from test_kanto_expedition import resources,flood
VISIT='FLAG_LEGACY_KANTO_CERULEAN_VISITED'
BOULDER='FLAG_LEGACY_BADGE_BOULDER'
CASCADE='FLAG_LEGACY_BADGE_CASCADE'
MISTY='TRAINER_LEGACY_MISTY'
BROCK_CIRCUIT='TRAINER_LEGACY_BROCK_CIRCUIT'
CIRCUIT='TRAINER_LEGACY_MISTY_CIRCUIT'

class CeruleanTests(unittest.TestCase):
    def test_round_trip_cave_route_city_and_services(self):
        cave=resources('LegacyKanto_MoonChamber')[0]
        route=resources('LegacyKanto_Route4')[0]
        city=resources('LegacyKanto_CeruleanCity')[0]
        for data,start in [(cave,(11,18)),(route,(5,10)),(city,(0,13))]:
            seen=flood(data['name'],start)
            for warp in data['warp_events']:self.assertIn((warp['x'],warp['y']),seen)
            for obj in data['object_events']:
                x,y=obj['x'],obj['y']
                self.assertTrue(any(p in seen for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]),obj)
        self.assertEqual(cave['warp_events'][1]['dest_map'],route['id'])
        self.assertEqual(cave['warp_events'][1]['dest_warp_id'],'0')
        self.assertEqual(route['warp_events'][0]['dest_map'],cave['id'])
        self.assertEqual(route['warp_events'][0]['dest_warp_id'],'1')
        self.assertIn(dict(map=city['id'],direction='right',offset=0),route['connections'])
        self.assertIn(dict(map=route['id'],direction='left',offset=0),city['connections'])
        for y in (12,13,14):
            self.assertIn((31,y),flood(route['name'],(5,10)))
            self.assertIn((0,y),flood(city['name'],(0,13)))

    def test_arrival_healing_and_fly_checkpoint_preserve_progress(self):
        flags={BOULDER,'FLAG_BADGE01_GET','FLAG_BADGE08_GET',BROCK_CIRCUIT}
        respawns=[]
        after,_,_,_=run_event('LegacyCerulean_EventScript_Transition',flags,respawns=respawns)
        self.assertEqual(after,flags|{VISIT})
        self.assertEqual(respawns,['HEAL_LOCATION_LEGACY_KANTO_CERULEAN'])
        healed=[];respawns=[]
        result,_,_,locked=run_event('LegacyCerulean_EventScript_Heal',after,healed=healed,respawns=respawns)
        self.assertEqual(result,after);self.assertFalse(locked)
        self.assertEqual(healed,[True]);self.assertEqual(respawns,['HEAL_LOCATION_LEGACY_KANTO_CERULEAN'])
        heal=next(x for x in json.loads((ROOT/'src/data/heal_locations.json').read_text())['heal_locations'] if x['id']=='HEAL_LOCATION_LEGACY_KANTO_CERULEAN')
        data=resources('LegacyKanto_CeruleanCity')[0]
        self.assertEqual(heal['map'],data['id'])
        point=(heal['x'],heal['y']);self.assertIn(point,flood(data['name'],(0,13)))
        self.assertNotIn(point,{(o['x'],o['y']) for o in data['object_events']+data['warp_events']})
        self.assertIn('MAP_SCRIPT_ON_TRANSITION, LegacyCerulean_EventScript_Transition',(ROOT/'data/maps/LegacyKanto_CeruleanCity/scripts.inc').read_text())

    def test_misty_requires_boulder_can_be_declined_or_lost_and_awards_once(self):
        for flags,answers,won in [({VISIT},[],True),({VISIT,BOULDER},[0],True),({VISIT,BOULDER},[1],False)]:
            after,_,_,locked=run_event('LegacyCerulean_EventScript_Misty',flags,answers,trainer_wins=won)
            self.assertEqual(after,flags);self.assertFalse(locked)
        flags={VISIT,BOULDER,'FLAG_BADGE08_GET','FLAG_LEGACY_FIRST_OBSERVATION'}
        after,msg,_,locked=run_event('LegacyCerulean_EventScript_Misty',flags,[1])
        self.assertEqual(after,flags|{MISTY,CASCADE});self.assertFalse(locked)
        self.assertEqual(msg.count('LegacyCerulean_Text_Cascade'),1)
        repeated,msg,_,locked=run_event('LegacyCerulean_EventScript_Misty',after)
        self.assertEqual(repeated,after);self.assertNotIn('LegacyCerulean_Text_Cascade',msg)
        self.assertFalse(locked)
        recovered,_,_,_=run_event('LegacyCerulean_EventScript_Misty',flags|{MISTY})
        self.assertIn(CASCADE,recovered)

    def test_circuit_is_separate_and_can_be_cancelled_lost_won_and_revisited(self):
        flags={VISIT,BOULDER,CASCADE,MISTY}
        after,msg,_,locked=run_event('LegacyCerulean_EventScript_Misty',flags)
        self.assertEqual(after,flags);self.assertFalse(locked)
        self.assertIn('LegacyCerulean_Text_CircuitBrockFirst',msg)
        flags.add(BROCK_CIRCUIT)
        for answer,won in [(0,True),(1,False)]:
            after,_,_,locked=run_event('LegacyCerulean_EventScript_Misty',flags,[answer],trainer_wins=won)
            self.assertEqual(after,flags);self.assertFalse(locked)
        after,msg,_,locked=run_event('LegacyCerulean_EventScript_Misty',flags,[1])
        self.assertEqual(after,flags|{CIRCUIT});self.assertFalse(locked)
        self.assertNotIn('LegacyCerulean_Text_Cascade',msg)
        repeated,msg,_,locked=run_event('LegacyCerulean_EventScript_Misty',after)
        self.assertEqual(repeated,after);self.assertFalse(locked)
        self.assertNotIn('LegacyCerulean_Text_CircuitOffer',msg)

    def test_journal_and_research_show_two_badges_without_mutating_them(self):
        flags={BOULDER,CASCADE,VISIT,'FLAG_LEGACY_KANTO_VISITED'}
        for label in ['LegacyCerulean_EventScript_Research','LegacyNorth_EventScript_BadgeJournal']:
            after,msg,_,locked=run_event(label,flags)
            self.assertEqual(after,flags);self.assertFalse(locked)
            self.assertIn('LegacyCerulean_Text_ResearchBadge',msg)

    def test_ids_flags_teams_and_wild_encounters_use_reserved_space(self):
        groups=json.loads((ROOT/'data/maps/map_groups.json').read_text())['gMapGroup_LegacyKanto']
        self.assertEqual(groups[10:],['LegacyKanto_Route4','LegacyKanto_CeruleanCity'])
        text=(ROOT/'include/constants/flags.h').read_text()
        for name,bit in [(VISIT,'4C1'),(CASCADE,'4C2')]:
            self.assertRegex(text,name+r'\s+0x'+bit)
            for file in ['flags.h','flags_frlg.h']:
                self.assertRegex((ROOT/'include/constants'/file).read_text(),r'0x'+bit+r' // Reserved by Legacy:')
        trainer=(ROOT/'include/constants/opponents.h').read_text()
        for name,num in [(MISTY,859),(CIRCUIT,860)]:self.assertRegex(trainer,name+r'\s+'+str(num))
        self.assertRegex(trainer,r'MAX_TRAINERS_COUNT_EMERALD\s+864')
        party=(ROOT/'src/data/trainers.party').read_text()
        for name,levels in [(MISTY,['60','61','62']),(CIRCUIT,['64','65','66'])]:
            section=party.split('=== '+name+' ===')[1].split('===')[0]
            self.assertEqual(re.findall(r'Level: (\d+)',section),levels)
        encounters=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]['encounters']
        table=next(e for e in encounters if e['map']=='MAP_LEGACY_KANTO_ROUTE4')['land_mons']
        self.assertEqual(len(table['mons']),12)
        for mon in table['mons']:self.assertEqual((mon['min_level'],mon['max_level']),(56,59))
        script=(ROOT/'data/scripts/legacy_kanto_cerulean.inc').read_text()
        self.assertNotRegex(script,r'(setflag|clearflag) FLAG_BADGE\d+_GET')
