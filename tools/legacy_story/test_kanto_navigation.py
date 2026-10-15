"""Run the actual fly-selection functions for Emerald and FireRed in a C harness."""
import json,re,subprocess,tempfile
from pathlib import Path
import unittest
from test_prologue import ROOT,run_event

VISITED='FLAG_LEGACY_KANTO_VISITED'
STATION='FLAG_LEGACY_KANTO_STATION_VISITED'

class KantoNavigationTests(unittest.TestCase):
 def test_quick_travel_rejects_unvisited_destinations_and_preserves_flags(self):
  for name,flag,destination in (
   ('Pewter','FLAG_LEGACY_KANTO_PEWTER_VISITED',('MAP_LEGACY_KANTO_PEWTER_OUTPOST','12','12')),
   ('KantoPort',VISITED,('MAP_LEGACY_KANTO_ARRIVAL_PORT','11','12')),
   ('KantoStation',STATION,('MAP_LEGACY_KANTO_RESEARCH_STATION','6','8')),
  ):
   flags,_,warp,locked=run_event('LegacyDebug_EventScript_'+name)
   self.assertEqual(flags,set());self.assertIsNone(warp);self.assertFalse(locked)
   before={flag,'FLAG_LEGACY_FOREST_REPORTED'}
   flags,_,warp,locked=run_event('LegacyDebug_EventScript_'+name,before)
   self.assertEqual(flags,before);self.assertEqual(warp,destination);self.assertFalse(locked)
 def test_station_transition_unlocks_only_its_visit_and_checkpoint(self):
  respawns=[]
  before={VISITED,'FLAG_LEGACY_KANTO_PIDGEY'}
  flags,_,_,locked=run_event('LegacyKanto_EventScript_StationTransition',before,respawns=respawns)
  self.assertEqual(flags,before|{STATION});self.assertEqual(respawns,['HEAL_LOCATION_LEGACY_KANTO_STATION']);self.assertFalse(locked)
 def test_quick_journal_is_read_only(self):
  before={VISITED,STATION,'FLAG_LEGACY_KANTO_PIDGEY'}
  flags,messages,warp,locked=run_event('LegacyDebug_EventScript_KantoJournal',before)
  self.assertEqual(flags,before);self.assertIsNone(warp);self.assertIn('LegacyKanto_Text_PidgeyNotes',messages);self.assertFalse(locked)
 def test_fly_lands_outdoors_on_reachable_tiles(self):
  from test_kanto_expedition import flood
  locations=json.loads((ROOT/'src/data/heal_locations.json').read_text())['heal_locations']
  for label,name,coords in (
   ('HEAL_LOCATION_LEGACY_KANTO_PEWTER','LegacyKanto_PewterOutpost',(12,12)),
   ('HEAL_LOCATION_LEGACY_KANTO_PORT','LegacyKanto_Route1',(11,29)),
   ('HEAL_LOCATION_LEGACY_KANTO_OUTPOST','LegacyKanto_ViridianOutpost',(12,12))):
   entry=next(h for h in locations if h['id']==label)
   data=json.loads((ROOT/f'data/maps/{name}/map.json').read_text())
   self.assertEqual(entry['map'],data['id']);self.assertNotEqual(data['map_type'],'MAP_TYPE_INDOOR')
   self.assertEqual((entry['x'],entry['y']),coords);self.assertIn(coords,flood(name,coords))
 def test_real_fly_functions_resolve_visit_flags_and_destinations_in_both_games(self):
  source=(ROOT/'src/region_map.c').read_text()
  def function(signature):
   start=source.index(signature+'\n{');return source[start:source.index('\n}',start)+2]
  get_type=function('static u8 GetMapsecType(mapsec_u16_t mapSecId)')
  filter_destination=function('u32 FilterFlyDestination(struct RegionMap* regionMap)')
  start=source.index('static const u8 sMapHealLocations[][3]')
  table=source[start:source.index('\n};',start)+3]
  start=source.index('#if IS_FRLG\n#define LEGACY_FLY_FLAG_PEWTER')
  macros=source[start:source.index('#endif',start)+6]
  combined=table+get_type+filter_destination+macros
  fixture='#include <assert.h>\ntypedef unsigned char u8; typedef unsigned int u32; typedef unsigned int mapsec_u16_t;\n'
  for prefix in ('MAPSEC_','FLAG_','HEAL_LOCATION_','MAP_','MAPSECTYPE_'):
   tokens=sorted(set(re.findall(r'\b'+prefix+r'[A-Z0-9_]+\b',combined))-{'MAP_GROUP','MAP_NUM'})
   fixture+='enum {'+','.join(tokens)+'};\n'
  fixture+='''
#define MAP_GROUP(x) 0
#define MAP_NUM(x) (x)
#define WARP_ID_NONE 255
#define MALE 0
struct RegionMap {unsigned mapSecId; unsigned posWithinMapSec;};
static struct {int playerGender;} save2;
#define gSaveBlock2Ptr (&save2)
static int flags[1024];
static int FlagGet(unsigned f){return flags[f];}
'''
  main='''
int main(void){
 struct RegionMap r={MAPSEC_PALLET_TOWN,0};
 assert(GetMapsecType(MAPSEC_PALLET_TOWN)==MAPSECTYPE_CITY_CANTFLY);
 assert(GetMapsecType(MAPSEC_VIRIDIAN_CITY)==MAPSECTYPE_CITY_CANTFLY);
#if IS_FRLG
 flags[FLAG_LEGACY_KANTO_VISITED]=1;
 flags[FLAG_LEGACY_KANTO_STATION_VISITED]=1;
 assert(GetMapsecType(MAPSEC_PALLET_TOWN)==MAPSECTYPE_CITY_CANTFLY);
 assert(FilterFlyDestination(&r)==HEAL_LOCATION_PALLET_TOWN);
 r.mapSecId=MAPSEC_VIRIDIAN_CITY;
 assert(FilterFlyDestination(&r)==HEAL_LOCATION_VIRIDIAN_CITY);
 flags[FLAG_WORLD_MAP_PALLET_TOWN]=1;
 flags[FLAG_WORLD_MAP_VIRIDIAN_CITY]=1;
 flags[FLAG_WORLD_MAP_PEWTER_CITY]=1;
#else
 flags[FLAG_WORLD_MAP_PALLET_TOWN]=1;
 flags[FLAG_WORLD_MAP_VIRIDIAN_CITY]=1;
 assert(GetMapsecType(MAPSEC_PALLET_TOWN)==MAPSECTYPE_CITY_CANTFLY);
 assert(FilterFlyDestination(&r)==HEAL_LOCATION_LEGACY_KANTO_PORT);
 r.mapSecId=MAPSEC_VIRIDIAN_CITY;
 assert(FilterFlyDestination(&r)==HEAL_LOCATION_LEGACY_KANTO_OUTPOST);
 flags[FLAG_LEGACY_KANTO_VISITED]=1;
 flags[FLAG_LEGACY_KANTO_STATION_VISITED]=1;
#endif
 assert(GetMapsecType(MAPSEC_PALLET_TOWN)==MAPSECTYPE_CITY_CANFLY);
 assert(GetMapsecType(MAPSEC_VIRIDIAN_CITY)==MAPSECTYPE_CITY_CANFLY);
#if !IS_FRLG
 assert(GetMapsecType(MAPSEC_PEWTER_CITY)==MAPSECTYPE_CITY_CANTFLY);
 flags[FLAG_LEGACY_KANTO_PEWTER_VISITED]=1;
 r.mapSecId=MAPSEC_PEWTER_CITY;
 assert(FilterFlyDestination(&r)==HEAL_LOCATION_LEGACY_KANTO_PEWTER);
#else
 r.mapSecId=MAPSEC_PEWTER_CITY;
 assert(FilterFlyDestination(&r)==HEAL_LOCATION_PEWTER_CITY);
#endif
 assert(GetMapsecType(MAPSEC_PEWTER_CITY)==MAPSECTYPE_CITY_CANFLY);
 assert(GetMapsecType(MAPSEC_LITTLEROOT_TOWN)==MAPSECTYPE_CITY_CANTFLY);
 flags[FLAG_VISITED_LITTLEROOT_TOWN]=1;
 assert(GetMapsecType(MAPSEC_LITTLEROOT_TOWN)==MAPSECTYPE_CITY_CANFLY);
 return 0;
}
'''
  with tempfile.TemporaryDirectory() as td:
   c=Path(td)/'fly.c';exe=Path(td)/'fly';c.write_text(fixture+macros+'\n'+table+'\n'+get_type+'\n'+filter_destination+'\n'+main)
   for game in (0,1):
    result=subprocess.run(['cc','-std=c99',f'-DIS_FRLG={game}',str(c),'-o',str(exe)],capture_output=True,text=True)
    self.assertEqual(result.returncode,0,result.stderr)
    subprocess.run([str(exe)],check=True)
  for name in ('PALLET','VIRIDIAN','PEWTER'):
   self.assertRegex(source,rf'\.mapsec = MAPSEC_{name}_'+('TOWN' if name=='PALLET' else 'CITY')+rf',\s+\.flag = LEGACY_FLY_FLAG_{name},')

if __name__=='__main__':unittest.main()
