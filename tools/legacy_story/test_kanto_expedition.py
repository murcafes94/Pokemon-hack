"""Execute expedition progress and verify the terrain, connections and build filter."""
from collections import deque
from pathlib import Path
import json,re,struct,subprocess,tempfile
import unittest
from test_prologue import ROOT,run_event
VISITED='FLAG_LEGACY_KANTO_VISITED'
PIDGEY='FLAG_LEGACY_KANTO_PIDGEY'
RATTATA='FLAG_LEGACY_KANTO_RATTATA'
REPORTED='FLAG_LEGACY_KANTO_REPORTED'
CHAMPION='FLAG_SYS_GAME_CLEAR'
NAMES=['LegacyKanto_ArrivalPort','LegacyKanto_Route1','LegacyKanto_ViridianOutpost','LegacyKanto_ResearchStation']

def resources(name):
 d=json.loads((ROOT/f'data/maps/{name}/map.json').read_text())
 l=next(x for x in json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts'] if x['id']==d['layout'])
 w,h=l['width'],l['height'];raw=(ROOT/l['blockdata_filepath']).read_bytes()
 assert len(raw)==2*w*h
 a=struct.unpack('<'+str(w*h)+'H',raw)
 return d,l,w,h,a

def flood(name,start):
 d,l,w,h,a=resources(name);blocked={(o['x'],o['y']) for o in d['object_events']}
 header=re.sub(r'//[^\n]*','',(ROOT/'include/constants/metatile_behaviors.h').read_text())
 behaviors=re.findall(r'\bMB_\w+',header.split('enum {',1)[1].split('}',1)[0])
 paths={'gTileset_General':'primary/general','gTileset_Building':'primary/building','gTileset_Facility':'secondary/facility','gTileset_Rustboro':'secondary/rustboro','gTileset_Lab':'secondary/lab','gTileset_RustboroGym':'secondary/rustboro_gym'}
 attrs=[]
 for key in ('primary_tileset','secondary_tileset'):
  b=(ROOT/f'data/tilesets/{paths[l[key]]}/metatile_attributes.bin').read_bytes();attrs.append(struct.unpack('<'+str(len(b)//2)+'H',b))
 safe={'MB_NORMAL','MB_TALL_GRASS','MB_LONG_GRASS','MB_SHORT_GRASS','MB_PUDDLE','MB_FOOTPRINTS','MB_SOUTH_ARROW_WARP','MB_NORTH_ARROW_WARP'}
 def usable(p):
  x,y=p
  if not (0<=x<w and 0<=y<h) or p in blocked:return False
  v=a[y*w+x];n=v&1023
  return not v&0xC00 and behaviors[attrs[n>=512][n%512]&255] in safe
 assert usable(start), (name,start,hex(a[start[1]*w+start[0]]))
 seen={start};q=deque([start])
 while q:
  x,y=q.popleft()
  for p in ((x+1,y),(x-1,y),(x,y+1),(x,y-1)):
   if p not in seen and usable(p):seen.add(p);q.append(p)
 return seen

class KantoTests(unittest.TestCase):
 def test_sailing_requires_champion_and_can_be_declined(self):
  after,msg,warp,locked=run_event('LegacyKanto_EventScript_Depart')
  self.assertEqual(after,set());self.assertIsNone(warp);self.assertFalse(locked)
  after,_,warp,locked=run_event('LegacyKanto_EventScript_Depart',{CHAMPION},[0])
  self.assertEqual(after,{CHAMPION});self.assertIsNone(warp);self.assertFalse(locked)
  after,_,warp,locked=run_event('LegacyKanto_EventScript_Depart',{CHAMPION},[1])
  self.assertEqual(after,{CHAMPION,VISITED});self.assertEqual(warp,('MAP_LEGACY_KANTO_ARRIVAL_PORT','11','12'));self.assertFalse(locked)
 def test_observations_any_order_decline_and_repeat(self):
  for order in ((PIDGEY,RATTATA),(RATTATA,PIDGEY)):
   flags={CHAMPION,VISITED,'FLAG_LEGACY_APPROACH_PATIENTLY'}
   for flag in order:
    label='LegacyKanto_EventScript_'+('Pidgey' if flag==PIDGEY else 'Rattata')
    before=set(flags)
    flags,_,_,locked=run_event(label,flags,[0]);self.assertEqual(flags,before);self.assertFalse(locked)
    flags,_,_,locked=run_event(label,flags,[1]);self.assertEqual(flags,before|{flag});self.assertFalse(locked)
    repeated,_,_,locked=run_event(label,flags);self.assertEqual(repeated,flags);self.assertFalse(locked)
   saved=set(flags)
   flags,_,_,locked=run_event('LegacyKanto_EventScript_Report',flags);self.assertEqual(flags,saved|{REPORTED});self.assertFalse(locked)
   repeated,_,_,_=run_event('LegacyKanto_EventScript_Report',flags);self.assertEqual(repeated,flags)
 def test_report_needs_both_and_journal_is_read_only(self):
  for flags in ({VISITED},{VISITED,PIDGEY},{VISITED,RATTATA}):
   after,_,_,_=run_event('LegacyKanto_EventScript_Report',flags);self.assertEqual(after,flags)
  flags={VISITED,PIDGEY,RATTATA,REPORTED}
  after,msg,_,locked=run_event('LegacyKanto_EventScript_Journal',flags)
  self.assertEqual(after,flags);self.assertEqual(len(msg),4);self.assertFalse(locked)
 def test_healing_checkpoint_and_return_reset_to_hoenn(self):
  respawns=[];healed=[]
  flags,_,_,locked=run_event('LegacyKanto_EventScript_Heal',{VISITED},respawns=respawns,healed=healed)
  self.assertEqual(respawns,['HEAL_LOCATION_LEGACY_KANTO_STATION']);self.assertEqual(healed,[True]);self.assertFalse(locked)
  flags,_,warp,locked=run_event('LegacyKanto_EventScript_Return',flags,[1],respawns=respawns)
  self.assertEqual(flags,{VISITED,'FLAG_LEGACY_KANTO_VIRIDIAN_VISITED'});self.assertEqual(warp,('MAP_LILYCOVE_CITY_HARBOR','5','13'));self.assertEqual(respawns[-1],'HEAL_LOCATION_LILYCOVE_CITY');self.assertFalse(locked)
  heal=next(h for h in json.loads((ROOT/'src/data/heal_locations.json').read_text())['heal_locations'] if h['id']=='HEAL_LOCATION_LEGACY_KANTO_STATION')
  self.assertEqual((heal['map'],heal['x'],heal['y']),('MAP_LEGACY_KANTO_RESEARCH_STATION',6,8))
  self.assertIn((6,8),flood(NAMES[3],(6,8)))
 def test_native_map_entrances_services_and_connections(self):
  starts=[(11,12),(11,29),(12,22),(6,8)]
  for name,start in zip(NAMES,starts):
   data,layout,w,h,blocks=resources(name);seen=flood(name,start)
   self.assertEqual(data['region'],'REGION_KANTO');self.assertEqual(data['legacy_game_version'],'emerald')
   for obj in data['object_events']+data['bg_events']:
    x,y=obj['x'],obj['y'];self.assertTrue(any(p in seen for p in ((x+1,y),(x-1,y),(x,y+1),(x,y-1))),obj)
   for warp in data['warp_events']:
    self.assertIn((warp['x'],warp['y']),seen)
  self.assertIn((11,0),flood(NAMES[1],(11,29)))
  self.assertIn((12,23),flood(NAMES[2],(12,22)))
  route=resources(NAMES[1])[0];outpost=resources(NAMES[2])[0]
  self.assertEqual(route['connections'][0]['map'],outpost['id']);self.assertEqual(outpost['connections'][0]['map'],route['id'])
  self.assertIn((5,13),flood('LilycoveCity_Harbor',(11,13)))
 def test_wild_levels_and_trainer_use_existing_save_capacity(self):
  d=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]
  found=next(x for x in d['encounters'] if x['map']=='MAP_LEGACY_KANTO_ROUTE1')['land_mons']
  self.assertEqual(len(found['mons']),12)
  for mon in found['mons']:self.assertEqual((mon['min_level'],mon['max_level']),(48,52))
  header=(ROOT/'include/constants/opponents.h').read_text()
  self.assertRegex(header,r'TRAINER_LEGACY_KANTO_SCOUT\s+855')
  self.assertRegex(header,r'MAX_TRAINERS_COUNT_EMERALD\s+864')
  for filename in ('flags.h','flags_frlg.h'):
   text=(ROOT/f'include/constants/{filename}').read_text()
   for n in (0x4bd,0x4ad,0x4ae,0x4af):self.assertRegex(text,rf'FLAG_(?:UNUSED_)?0x{n:03X}\s+0x{n:03X} // Reserved by Legacy:')
 def test_build_filter_includes_curated_kanto_only_in_emerald(self):
  # CI runs these tests before the ROM build; compile the host tool first.
  subprocess.run(['make','-C',str(ROOT/'tools/mapjson')],check=True,capture_output=True)
  # Run the native generator on the real complete map catalog, not a mirrored predicate.
  with tempfile.TemporaryDirectory() as td:
   maps=[str(p) for p in (ROOT/'data/maps').glob('*/map.json')]
   for version in ('emerald','firered'):
    out=Path(td)/version;out.mkdir();c=out/'include';c.mkdir()
    subprocess.run([str(ROOT/'tools/mapjson/mapjson'),'groups',version,str(ROOT/'data/maps/map_groups.json'),*maps,str(out),str(c)],check=True,capture_output=True)
    generated=(out/'headers.inc').read_text()
    self.assertEqual('LegacyKanto_ArrivalPort' in generated,version=='emerald')
    self.assertEqual('VermilionCity_Frlg' in generated,version=='firered')

if __name__=='__main__':unittest.main()
