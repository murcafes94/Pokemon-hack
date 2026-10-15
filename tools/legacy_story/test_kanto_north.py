"""Northern campaign routes, battle outcomes, badge persistence and encounters."""
import json,re,unittest
from test_prologue import ROOT,run_event
from test_kanto_expedition import resources,flood,CHAMPION,VISITED
BADGE='FLAG_LEGACY_BADGE_BOULDER'
TRAINER='TRAINER_LEGACY_BROCK'
PEWTER='FLAG_LEGACY_KANTO_PEWTER_VISITED'
class NorthKantoTests(unittest.TestCase):
    def test_round_trip_connections_and_gym_door_have_walkable_paths(self):
        chain=['LegacyKanto_ViridianOutpost','LegacyKanto_Route2','LegacyKanto_ViridianForest','LegacyKanto_PewterCity']
        for i,name in enumerate(chain):
            d,l,w,h,a=resources(name);seen=flood(name,(12,h-2))
            if i<len(chain)-1:
                self.assertIn((12,0),seen)
                target=resources(chain[i+1])[0]
                self.assertIn({'map':target['id'],'direction':'up','offset':0},d['connections'])
                self.assertIn({'map':d['id'],'direction':'down','offset':0},target['connections'])
            for o in d['object_events']:
                self.assertTrue(any(p in seen for p in ((o['x']+1,o['y']),(o['x']-1,o['y']),(o['x'],o['y']+1),(o['x'],o['y']-1))),o)
            for warp in d['warp_events']:
                # Exterior doors are solid tiles activated from the tile below.
                if name=='LegacyKanto_PewterCity':
                    self.assertIn((warp['x'],warp['y']+1),seen)
                    self.assertEqual(a[warp['y']*w+warp['x']] & 1023, 0x1CD)
                else:self.assertIn((warp['x'],warp['y']),seen)
        d,l,w,h,a=resources('LegacyKanto_PewterGym');seen=flood(d['name'],(5,18))
        self.assertIn((5,3),seen) # Can talk to Brock from below.
        for warp in d['warp_events']:self.assertIn((warp['x'],warp['y']),seen)
        town=resources(chain[-1])[0]
        for warp in d['warp_events']:
            self.assertEqual(warp['dest_map'],town['id'])
            self.assertEqual(town['warp_events'][int(warp['dest_warp_id'])]['dest_map'],d['id'])

    def test_brock_cancellation_defeat_victory_and_repeated_dialogue(self):
        base={CHAMPION,VISITED,PEWTER,'FLAG_BADGE01_GET','FLAG_BADGE08_GET','FLAG_LEGACY_KANTO_REPORTED'}
        for flags,answers,won in [(set(),[],True),(base,[0],True),(base,[1],False)]:
            after,msg,warp,locked=run_event('LegacyNorth_EventScript_Brock',flags,answers,trainer_wins=won)
            self.assertEqual(after,flags);self.assertFalse(locked);self.assertNotIn('LegacyNorth_Text_Boulder',msg)
        after,msg,_,locked=run_event('LegacyNorth_EventScript_Brock',base,[1])
        self.assertEqual(after,base|{BADGE,TRAINER});self.assertFalse(locked)
        self.assertEqual(msg.count('LegacyNorth_Text_Boulder'),1)
        repeated,msg,_,locked=run_event('LegacyNorth_EventScript_Brock',after)
        self.assertEqual(repeated,after);self.assertFalse(locked);self.assertNotIn('LegacyNorth_Text_Boulder',msg)
        # A completed trainer flag can recover a missing badge after an interrupted event.
        after,_,_,_=run_event('LegacyNorth_EventScript_Brock',base|{TRAINER})
        self.assertIn(BADGE,after)

    def test_badge_journal_is_read_only_and_shows_saved_result(self):
        for flags,expected in [({VISITED},'BadgePending'),({VISITED,BADGE},'BadgeRecorded')]:
            after,msg,_,locked=run_event('LegacyKanto_EventScript_Journal',flags)
            self.assertEqual(after,flags);self.assertFalse(locked)
            self.assertIn('LegacyNorth_Text_'+expected,msg)

    def test_pewter_arrival_and_healing_checkpoint(self):
        for label in ('PewterTransition','Heal'):
            respawns=[];healed=[]
            after,_,_,_=run_event('LegacyNorth_EventScript_'+label,{CHAMPION,VISITED},respawns=respawns,healed=healed)
            self.assertEqual(respawns,['HEAL_LOCATION_LEGACY_KANTO_PEWTER'])
            self.assertEqual(healed,[True] if label=='Heal' else [])
        loc=next(x for x in json.loads((ROOT/'src/data/heal_locations.json').read_text())['heal_locations'] if x['id']=='HEAL_LOCATION_LEGACY_KANTO_PEWTER')
        self.assertIn((loc['x'],loc['y']),flood('LegacyKanto_PewterCity',(12,22)))

    def test_encounters_trainer_capacity_and_badge_do_not_reuse_hoenn(self):
        enc=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]['encounters']
        for name,levels in [('ROUTE2',(50,54)),('VIRIDIANFOREST',(51,55))]:
            e=next(x for x in enc if x['map']=='MAP_LEGACY_KANTO_'+name)['land_mons']
            self.assertEqual(len(e['mons']),12)
            for mon in e['mons']:self.assertEqual((mon['min_level'],mon['max_level']),levels)
        header=(ROOT/'include/constants/opponents.h').read_text()
        self.assertRegex(header,r'TRAINER_LEGACY_BROCK\s+856')
        self.assertRegex(header,r'TRAINERS_COUNT_EMERALD\s+857')
        self.assertRegex(header,r'MAX_TRAINERS_COUNT_EMERALD\s+864')
        party=(ROOT/'src/data/trainers.party').read_text().split('=== TRAINER_LEGACY_BROCK ===')[1]
        self.assertEqual(re.findall(r'Level: (\d+)',party),['56','57','58'])
        for code,label in [('4BF','FLAG_LEGACY_KANTO_PEWTER_VISITED'),('4C0',BADGE)]:
            for file in ('flags.h','flags_frlg.h'):
                self.assertRegex((ROOT/f'include/constants/{file}').read_text(),r'0x'+code+r' // Reserved by Legacy:')
            self.assertRegex((ROOT/'include/constants/flags.h').read_text(),label+r'\s+0x'+code)
        script=(ROOT/'data/scripts/legacy_kanto_north.inc').read_text()
        self.assertNotRegex(script,r'(?:setflag|clearflag) FLAG_BADGE\d+_GET')

if __name__=='__main__':unittest.main()
