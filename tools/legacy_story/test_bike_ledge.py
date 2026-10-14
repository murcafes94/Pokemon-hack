"""Compile and execute the actual reverse-ledge predicate with collision fixtures."""
from pathlib import Path
import subprocess
import tempfile
import unittest
from test_prologue import ROOT

class BikeLedgeTests(unittest.TestCase):
    def test_reverse_jump_checks_direction_terrain_and_landing(self):
        source = (ROOT / 'src/bike.c').read_text()
        start = source.index('static bool8 AcroBike_CanHopBackOverLedge(')
        stop = source.index('\nstatic void AcroBikeTransition_WheelieHoppingMoving(enum Direction direction)\n{', start)
        helper = source[start:stop]
        fixture = r'''
#include <assert.h>
typedef short s16; typedef unsigned char u8; typedef int bool8;
enum Direction {DIR_NONE, DIR_SOUTH, DIR_NORTH, DIR_WEST, DIR_EAST};
enum {FALSE, TRUE};
enum {MB_NORMAL, MB_TALL_GRASS, MB_LONG_GRASS, MB_SHORT_GRASS, MB_PUDDLE, MB_FOOTPRINTS, WATER, WARP, WALL};
enum {COLLISION_NONE, BLOCKED, OBJECT_EVENTS_COUNT=16};
struct ObjectEvent {struct {s16 x,y;} currentCoords;};
static int ledge, occupied, terrain, collision, lastX, lastY;
static void MoveCoords(enum Direction d,s16 *x,s16 *y){if(d==DIR_SOUTH)++*y;if(d==DIR_NORTH)--*y;if(d==DIR_WEST)--*x;if(d==DIR_EAST)++*x;}
static enum Direction GetOppositeDirection(enum Direction d){return d==DIR_SOUTH?DIR_NORTH:d==DIR_NORTH?DIR_SOUTH:d==DIR_EAST?DIR_WEST:DIR_EAST;}
static int GetLedgeJumpDirection(s16 x,s16 y,enum Direction d){return d==ledge?d:DIR_NONE;}
static int GetObjectEventIdByXY(s16 x,s16 y){return occupied?0:OBJECT_EVENTS_COUNT;}
static int MapGridGetMetatileBehaviorAt(s16 x,s16 y){return terrain;}
static int GetCollisionAtCoords(struct ObjectEvent *p,s16 x,s16 y,enum Direction d){lastX=x;lastY=y;return collision;}
'''
        main = r'''
int main(void){
 struct ObjectEvent p={{10,10}};
 for(int d=DIR_SOUTH;d<=DIR_EAST;d++){
  ledge=GetOppositeDirection(d);occupied=0;terrain=MB_NORMAL;collision=COLLISION_NONE;
  assert(AcroBike_CanHopBackOverLedge(&p,d));
  assert(lastX==10+(d==DIR_EAST?2:d==DIR_WEST?-2:0));
  assert(lastY==10+(d==DIR_SOUTH?2:d==DIR_NORTH?-2:0));
  occupied=1;assert(!AcroBike_CanHopBackOverLedge(&p,d));occupied=0;
  collision=BLOCKED;assert(!AcroBike_CanHopBackOverLedge(&p,d));collision=0;
  for(terrain=WATER;terrain<=WALL;terrain++)assert(!AcroBike_CanHopBackOverLedge(&p,d));
  terrain=MB_TALL_GRASS;assert(AcroBike_CanHopBackOverLedge(&p,d));
  ledge=d;assert(!AcroBike_CanHopBackOverLedge(&p,d));
  ledge=DIR_NONE;assert(!AcroBike_CanHopBackOverLedge(&p,d));
 }
 assert(!AcroBike_CanHopBackOverLedge(&p,DIR_NONE));
 return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            c = Path(temp)/'bike.c'; exe=Path(temp)/'bike'
            c.write_text(fixture+helper+main)
            subprocess.run(['cc','-std=c99',str(c),'-o',str(exe)],check=True,capture_output=True)
            subprocess.run([str(exe)],check=True)

if __name__ == '__main__': unittest.main()
