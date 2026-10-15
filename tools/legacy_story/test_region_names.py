"""Verify localization preserves region geometry and the engine name-buffer bound."""
import hashlib,json,unittest
from test_prologue import ROOT

class RegionNameTests(unittest.TestCase):
 def test_names_fit_the_engine_buffer_and_keep_all_geometry(self):
  sections=json.loads((ROOT/'src/data/region_map/region_map_sections.json').read_text())['map_sections']
  meta=[{k:v for k,v in entry.items() if k!='name'} for entry in sections]
  # Geometry checksum from the last published base, 87f6e3a2.
  self.assertEqual(hashlib.sha256(json.dumps(meta,sort_keys=True).encode()).hexdigest(),"35c3cc86a9003629995d69323642c52b5627f78f4bbe2016eb9feefbdc20b978")
  for entry in sections:
   # mapSecName holds 20 encoded Latin glyphs, including the terminator.
   name=entry.get('name','').replace('{AQUA}','AQUA')
   self.assertLessEqual(len(name),19,name)
  names={x['id']:x.get('name') for x in sections}
  self.assertEqual(names['MAPSEC_PALLET_TOWN'],'Pueblo Paleta')
  self.assertEqual(names['MAPSEC_VIRIDIAN_CITY'],'Ciudad Verde')
  self.assertEqual(names['MAPSEC_FIVE_ISLE_MEADOW'],'Prado de Isla Inta')

if __name__=='__main__':unittest.main()
