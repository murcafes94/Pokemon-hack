"""Exercise real regional-map C functions and the script/terrain destinations."""
import json
import re
import subprocess
import tempfile
from pathlib import Path
import unittest
from test_prologue import ROOT, run_event
from test_kanto_expedition import flood, CHAMPION, VISITED

VIRIDIAN = 'FLAG_LEGACY_KANTO_VIRIDIAN_VISITED'

class KantoNavigationTests(unittest.TestCase):
    def test_visiting_outpost_or_station_unlocks_only_viridian(self):
        for label in ('ViridianTransition', 'StationTransition'):
            after, _, _, _ = run_event('LegacyKanto_EventScript_' + label, {VISITED})
            self.assertEqual(after, {VISITED, VIRIDIAN})
        data = (ROOT/'data/maps/LegacyKanto_ViridianOutpost/scripts.inc').read_text()
        self.assertIn('MAP_SCRIPT_ON_TRANSITION, LegacyKanto_EventScript_ViridianTransition', data)

    def test_shortcuts_preserve_progress_and_require_visited_destinations(self):
        for label, flags, expected in (
            ('KantoPort', set(), None), ('KantoPort', {CHAMPION}, 'MAP_LILYCOVE_CITY_HARBOR'),
            ('KantoStation', {CHAMPION,VISITED}, None),
            ('KantoStation', {CHAMPION,VISITED,VIRIDIAN}, 'MAP_LEGACY_KANTO_RESEARCH_STATION'),
        ):
            after, _, warp, locked = run_event('LegacyDebug_EventScript_'+label, flags)
            self.assertEqual(after, flags)
            self.assertEqual(warp[0] if warp else None, expected)
            self.assertFalse(locked)
        flags = {CHAMPION,VISITED,VIRIDIAN}
        after, messages, warp, locked = run_event('LegacyDebug_EventScript_KantoJournal', flags)
        self.assertEqual(after, flags); self.assertIsNone(warp); self.assertFalse(locked)
        self.assertIn('LegacyKanto_Text_Journal', messages)

    def test_fly_lands_on_reachable_outdoor_tiles_without_npcs_or_warps(self):
        locations = json.loads((ROOT/'src/data/heal_locations.json').read_text())['heal_locations']
        for name, start in (('PALLET', (11,29)), ('VIRIDIAN', (12,22))):
            loc = next(x for x in locations if x['id']==f'HEAL_LOCATION_LEGACY_KANTO_{name}_FLY')
            map_name = 'LegacyKanto_Route1' if name=='PALLET' else 'LegacyKanto_ViridianOutpost'
            self.assertIn((loc['x'],loc['y']), flood(map_name, start))
            data = json.loads((ROOT/f'data/maps/{map_name}/map.json').read_text())
            self.assertEqual(loc['map'],data['id'])
            self.assertIn(data['map_type'], ('MAP_TYPE_TOWN','MAP_TYPE_ROUTE'))
            self.assertNotIn((loc['x'],loc['y']), {(w['x'],w['y']) for w in data['warp_events']})

    def test_actual_c_selection_blocks_unbuilt_cities_and_preserves_firered(self):
        source = (ROOT/'src/region_map.c').read_text()
        def function(start):
            a=source.index(start+'\n{'); return source[a:source.index('\n}',a)+2]
        functions = '\n'.join(function(s) for s in (
            'static u8 GetMapsecType(mapsec_u16_t mapSecId)',
            'u32 FilterFlyDestination(struct RegionMap* regionMap)',
            'void SetFlyDestination(struct RegionMap* regionMap)'))
        a=source.index('static const u8 sMapHealLocations')
        table=source[a:source.index('\n};',a)+3]
        fly=source[source.index('static const struct FlyLocation sFlyLocations[]'):]
        fly=fly[:fly.index('\n};')+3]
        all_text=functions+table+fly
        # Use the real generated section order, including every non-adapted destination.
        sections=json.loads((ROOT/'src/data/region_map/region_map_sections.json').read_text())['map_sections']
        defs='\n'.join(f'#define {x["id"]} {i}' for i,x in enumerate(sections))
        identifiers=set(re.findall(r'\b(?:MAP_[A-Z0-9_]+|HEAL_LOCATION_[A-Z0-9_]+|FLAG_[A-Z0-9_]+|MAPSECTYPE_[A-Z0-9_]+)\b',all_text))
        for prefix in ('MAP_', 'HEAL_LOCATION_', 'FLAG_', 'MAPSECTYPE_'):
            defs+='\n'+ '\n'.join(f'#define {key} {i+1}' for i,key in enumerate(sorted(k for k in identifiers if k.startswith(prefix))))
        defs+=f'\n#define MAPSEC_NONE {len(sections)}'
        harness='''
#include <assert.h>
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef unsigned short mapsec_u16_t;
#define MAP_GROUP(m) (m)
#define MAP_NUM(m) (m)
#define WARP_ID_NONE 65535
#define MALE 0
struct RegionMap {mapsec_u16_t mapSecId; u8 posWithinMapSec;};
struct {u8 playerGender;} save, *gSaveBlock2Ptr=&save;
static int visited[4096], heal, group, num;
static int FlagGet(int flag){return visited[flag];}
static void SetWarpDestinationToHealLocation(int h){heal=h;}
static void SetWarpDestinationToMapWarp(int g,int n,int w){group=g;num=n;}
struct FlyLocation {u16 regionMapType;mapsec_u16_t mapsec;u16 flag;};
'''
        # Icon table includes region-map constants as well.
        defs+='\n'+ '\n'.join(f'#define {key} {i}' for i,key in enumerate(sorted(set(re.findall(r'\bREGION_MAP_[A-Z0-9_]+\b',fly)))))
        main='''
int main(void) {
 struct RegionMap r={MAPSEC_PALLET_TOWN,0};
#if IS_FRLG
 visited[FLAG_WORLD_MAP_PALLET_TOWN]=1;
 assert(GetMapsecType(r.mapSecId)==MAPSECTYPE_CITY_CANFLY);
 SetFlyDestination(&r); assert(heal==HEAL_LOCATION_PALLET_TOWN);
 r.mapSecId=MAPSEC_CERULEAN_CITY;
 visited[FLAG_WORLD_MAP_CERULEAN_CITY]=1;
 assert(GetMapsecType(r.mapSecId)==MAPSECTYPE_CITY_CANFLY);
 SetFlyDestination(&r);assert(heal==HEAL_LOCATION_CERULEAN_CITY);
#else
 for(int i=MAPSEC_PALLET_TOWN;i<=MAPSEC_ROUTE_10_POKECENTER;i++)
   assert(GetMapsecType(i)==MAPSECTYPE_CITY_CANTFLY);
 visited[FLAG_LEGACY_KANTO_VISITED]=1;
 assert(GetMapsecType(r.mapSecId)==MAPSECTYPE_CITY_CANFLY);
 assert(GetMapsecType(MAPSEC_VIRIDIAN_CITY)==MAPSECTYPE_CITY_CANTFLY);
 SetFlyDestination(&r);assert(heal==HEAL_LOCATION_LEGACY_KANTO_PALLET_FLY);
 visited[FLAG_LEGACY_KANTO_VIRIDIAN_VISITED]=1;r.mapSecId=MAPSEC_VIRIDIAN_CITY;
 assert(GetMapsecType(r.mapSecId)==MAPSECTYPE_CITY_CANFLY);
 SetFlyDestination(&r);assert(heal==HEAL_LOCATION_LEGACY_KANTO_VIRIDIAN_FLY);
 visited[FLAG_WORLD_MAP_PEWTER_CITY]=1;
 assert(GetMapsecType(MAPSEC_PEWTER_CITY)==MAPSECTYPE_CITY_CANTFLY);
 visited[FLAG_LEGACY_KANTO_PEWTER_VISITED]=1;r.mapSecId=MAPSEC_PEWTER_CITY;
 assert(GetMapsecType(r.mapSecId)==MAPSECTYPE_CITY_CANFLY);
 SetFlyDestination(&r);assert(heal==HEAL_LOCATION_LEGACY_KANTO_PEWTER);
 visited[FLAG_WORLD_MAP_CERULEAN_CITY]=1;
 assert(GetMapsecType(MAPSEC_CERULEAN_CITY)==MAPSECTYPE_CITY_CANTFLY);
 visited[FLAG_LEGACY_KANTO_CERULEAN_VISITED]=1;r.mapSecId=MAPSEC_CERULEAN_CITY;
 assert(GetMapsecType(r.mapSecId)==MAPSECTYPE_CITY_CANFLY);
 SetFlyDestination(&r);assert(heal==HEAL_LOCATION_LEGACY_KANTO_CERULEAN);
#endif
 r.mapSecId=MAPSEC_LILYCOVE_CITY;visited[FLAG_VISITED_LILYCOVE_CITY]=1;
 assert(GetMapsecType(r.mapSecId)==MAPSECTYPE_CITY_CANFLY);
 SetFlyDestination(&r);assert(heal==HEAL_LOCATION_LILYCOVE_CITY);
 return 0;
}
'''
        with tempfile.TemporaryDirectory() as td:
            for version in (0,1):
                path=Path(td)/f'nav{version}'
                result=subprocess.run(['cc','-std=c99',f'-DIS_FRLG={version}','-x','c','-o',str(path),'-'],input=defs+'\n'+harness+table+'\n'+functions+'\n'+main,text=True,capture_output=True)
                self.assertEqual(result.returncode, 0, result.stderr)
                subprocess.run([str(path)],check=True)

if __name__=='__main__':unittest.main()
