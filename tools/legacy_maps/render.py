"""Render native Emerald metatiles for map review (static animation frame)."""
from pathlib import Path
import json,struct
from functools import lru_cache
from PIL import Image,ImageDraw
ROOT=Path(__file__).resolve().parents[2]
PATHS={'gTileset_General':'primary/general','gTileset_Rustboro':'secondary/rustboro','gTileset_Cave':'secondary/cave'}

@lru_cache(None)
def metatile(primary,secondary,index):
    dirs=[ROOT/'data/tilesets'/PATHS[t] for t in (primary,secondary)]
    images=[Image.open(d/'tiles.png') for d in dirs]
    raw=(dirs[index>=512]/'metatiles.bin').read_bytes()
    words=struct.unpack_from('<8H',raw,index%512*16)
    out=Image.new('RGB',(16,16))
    for layer in range(2):
        for quadrant in range(4):
            word=words[layer*4+quadrant];tile=word&1023;pal=word>>12
            palette=[tuple(map(int,line.split())) for line in (dirs[pal>=6]/'palettes'/f'{pal:02}.pal').read_text().splitlines()[3:19]]
            image=images[tile>=512];n=tile%512
            tileimg=image.crop(((n%16)*8,(n//16)*8,(n%16+1)*8,(n//16+1)*8))
            if word&0x400:tileimg=tileimg.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
            if word&0x800:tileimg=tileimg.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            for y in range(8):
                for x in range(8):
                    color=tileimg.getpixel((x,y))
                    if not layer or color:
                        out.putpixel(((quadrant%2)*8+x,(quadrant//2)*8+y),palette[color])
    return out

def render(name):
    m=json.loads((ROOT/'data/maps'/name/'map.json').read_text())
    layout=next(l for l in json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts'] if l['id']==m['layout'])
    w,h=layout['width'],layout['height'];data=struct.unpack('<'+str(w*h)+'H',(ROOT/layout['blockdata_filepath']).read_bytes())
    out=Image.new('RGB',(w*16,h*16))
    for i,value in enumerate(data):out.paste(metatile(layout['primary_tileset'],layout['secondary_tileset'],value&1023),((i%w)*16,(i//w)*16))
    return out

if __name__=='__main__':
    import argparse
    p=argparse.ArgumentParser();p.add_argument('map');p.add_argument('output');a=p.parse_args();render(a.map).save(a.output)
