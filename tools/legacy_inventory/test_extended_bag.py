"""Compile the actual split-pocket, encryption and flash-selection functions."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


def function(source, name):
    match = re.search(r'^[^\n;]*\b' + name + r'\([^;{}]*\)\n\{', source, re.M)
    if not match:
        raise ValueError(name)
    end = match.end()
    depth = 1
    while depth:
        depth += (source[end] == '{') - (source[end] == '}')
        end += 1
    return source[match.start():end].replace('NONNULL ', '')


def struct(source, name):
    return re.search(r'struct ' + name + r'\s*\{.*?\n\};', source, re.S)[0]


class ExtendedBagTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.directory = tempfile.TemporaryDirectory()
        cls.addClassCleanup(cls.directory.cleanup)
        global_h = (ROOT/'include/global.h').read_text()
        constants = (ROOT/'include/constants/global.h').read_text()
        defines = '\n'.join(re.findall(r'^#define (?:BAG_|LEGACY_(?:EXTRA|BAG_))[^\n]+', constants, re.M))
        defines += '\n' + '\n'.join(re.findall(r'^#define MAX_(?:BAG|PC)_ITEM_CAPACITY[^\n]+', (ROOT/'include/constants/items.h').read_text(), re.M))
        types = '\n'.join(struct(global_h,n) for n in ['ItemSlot','LegacyBagExtension','Bag'])
        pocket = re.search(r'enum Pocket\n\{.*?\n\};',(ROOT/'include/constants/item.h').read_text(),re.S)[0]
        harness = r'''
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32;
typedef int8_t s8; typedef int32_t s32; typedef int bool32; typedef uint8_t bool8;
enum __attribute__((packed)) Item {ITEM_NONE, TEST_ITEM_MAX=65535};
#define TRUE 1
#define FALSE 0
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define AllocZeroed(n) calloc(1,n)
#define Free free
#define CpuFastFill(v,p,n) memset(p,v,n)
#define STATIC_ASSERT(a,b)
#define IS_FRLG 0
#define VAR_SECRET_BASE_LOW_TV_FLAGS 1
#define SECRET_BASE_USED_BAG 1
#define VAR_SECRET_BASE_LAST_ITEM_USED 2
#define ITEMS_COUNT 700
#define LEGACY_BAG_MAGIC 0x3147424C
static int CurMapIsSecretBase(void){return 0;}
static int VarGet(int v){(void)v;return 0;}
static void VarSet(int a,int b){(void)a;(void)b;}
'''
        fixture = r'''
struct SaveBlock1 {struct Bag bag; u8 mail[16];} sb1, *gSaveBlock1Ptr=&sb1;
struct SaveBlock2 {u32 encryptionKey;} sb2, *gSaveBlock2Ptr=&sb2;
struct SaveBlock3 {u32 oldPrefix; struct LegacyBagExtension legacyBag;} gSaveblock3, *gSaveBlock3Ptr=&gSaveblock3;
struct BagPocket {struct ItemSlot *itemSlots; u32 capacity; enum Pocket id;};
struct BagPocket gBagPockets[POCKETS_COUNT];
static void ApplyNewEncryptionKeyToHword(u16 *p,u32 key){*p^=gSaveBlock2Ptr->encryptionKey;*p^=key;}
void BagPocket_SetSlotData(struct BagPocket *,u32,struct ItemSlot);
static void BagPocket_CompactItems(struct BagPocket *);
static void BagPocket_SetSlotItemIdAndCount(struct BagPocket *p,u32 i,enum Item id,u16 q){BagPocket_SetSlotData(p,i,(struct ItemSlot){id,q});}
'''
        legacy = (ROOT/'src/legacy_bag.c').read_text()
        legacy = re.sub(r'^#include[^\n]+\n', '', legacy, flags=re.M)
        source = (ROOT/'src/item.c').read_text()
        names = ['BagPocket_GetSlotDataGeneric','BagPocket_GetSlotDataPC','BagPocket_SetSlotDataGeneric',
                 'BagPocket_SetSlotDataPC','BagPocket_GetSlotData','BagPocket_SetSlotData',
                 'ApplyNewEncryptionKeyToBagItems','SetBagItemsPointers','BagPocket_GetFreeSpaceForItem',
                 'CheckSlotAndUpdateCount','BagPocket_AddItem','BagPocket_RemoveItem',
                 'BagPocket_CompactItems','BagPocket_MoveItemSlot','ClearBag','BagPocket_CountTotalItemQuantity']
        inventory = '\n'.join(function(source,n) for n in names)
        wrappers = r'''
static enum Pocket GetItemPocket(enum Item id){(void)id;return POCKET_ITEMS;}
static enum Item GetBagItemId(enum Pocket p,u32 i){return BagPocket_GetSlotData(&gBagPockets[p],i).itemId;}
static bool32 CheckBagHasItem(enum Item id,u16 n){return BagPocket_CountTotalItemQuantity(&gBagPockets[GetItemPocket(id)],id)>=n;}
static bool32 CheckBagHasSpace(enum Item id,u16 n){return BagPocket_GetFreeSpaceForItem(&gBagPockets[GetItemPocket(id)],id)>=n;}
static bool32 AddBagItem(enum Item id,u16 n){return BagPocket_AddItem(&gBagPockets[GetItemPocket(id)],id,n);}
'''
        debug = (ROOT/'src/debug.c').read_text()
        debug = '\n'.join(function(debug,n) for n in ['DebugBagHasSpareSlots','DebugAction_PCBag_Fill_PocketItems'])
        menu = (ROOT/'src/item_menu.c').read_text()
        snapshots = struct(menu,'TempWallyBag') + r'''
#define MAIL_COUNT 16
static struct TempWallyBag *sTempWallyBag;
struct {u16 pocket;u16 cursorPosition[POCKETS_COUNT],scrollPosition[POCKETS_COUNT];} gBagPosition;
static void ResetBagScrollPositions(void){memset(&gBagPosition,0,sizeof(gBagPosition));}
struct {struct Bag bag; u8 mail[16];struct LegacyBagExtension legacyBag;} gLoadedSaveData;
static u32 gLastEncryptionKey;
'''
        snapshots += '\n'.join(function(menu,n) for n in ['PrepareBagForWallyTutorial','RestoreBagAfterWallyTutorial'])
        snapshots += '\n'.join(function((ROOT/'src/load_save.c').read_text(),n) for n in ['LoadPlayerBag','SavePlayerBag'])
        save = (ROOT/'src/save.c').read_text()
        flash = r'''
#define SECTOR_DATA_SIZE 3968
#define SAVE_BLOCK_3_CHUNK_SIZE 116
#define NUM_SECTORS_PER_SLOT 14
#define NUM_SAVE_SLOTS 2
#define SECTOR_SIGNATURE 0x8012025
#define SAVE_STATUS_OK 1
#define SAVE_STATUS_EMPTY 0
#define SAVE_STATUS_ERROR 255
#define SAVE_STATUS_CORRUPT 2
#define FULL_SAVE_SLOT 65535
struct SaveSector {u8 data[3968];u8 saveBlock3Chunk[116];u16 id,checksum;u32 signature,counter;};
struct SaveSectorLocation {void *data;u16 size;};
static struct SaveSector flash[28],buffer,*gReadWriteSector=&buffer;
static u32 gSaveCounter;
static u16 gLastWrittenSector;
static bool8 ReadFlashSector(u8 i,struct SaveSector *s){*s=flash[i];return TRUE;}
'''
        flash += '\n'.join(function(save,n) for n in ['SaveBlock3Size','ReadSaveBlock3Chunk','CopyToSaveBlock3','CopyFromSaveBlock3','CalculateChecksum','GetSaveValidStatus','CopySaveSlotData'])
        link = r'''
#define SECTORS_COUNT 32
#define SECTOR_ID_HOF_1 28
#define SECTOR_ID_HOF_2 29
#define SECTOR_ID_SAVEBLOCK2 0
#define GAME_STAT_ENTERED_HOF 0
enum {SAVE_NORMAL,SAVE_LINK,SAVE_EREADER,SAVE_HALL_OF_FAME,SAVE_OVERWRITE_DIFFERENT_FILE,SAVE_HALL_OF_FAME_ERASE_BEFORE};
static u32 *gTrainerHillVBlankCounter;
static void *gHoFSaveBuffer;
static bool32 gFlashMemoryPresent=TRUE;
static u32 gDamagedSaveSectors,writeMask,signatureMask;
static u16 gIncrementalSectorId;
static struct SaveSectorLocation gRamSaveSectorLocations[14];
static u32 primaryData[14];
static void UpdateSaveAddresses(void){for(int i=0;i<14;i++)gRamSaveSectorLocations[i]=(struct SaveSectorLocation){&primaryData[i],4};}
static void CopyPartyAndObjectsToSave(void){}
static void EraseFlashSector(int i){(void)i;}
static u32 GetGameStat(int i){(void)i;return 0;}
static void IncrementGameStat(int i){(void)i;}
static u8 WriteSaveSectorOrSlot(u16 i,const struct SaveSectorLocation *l){(void)i;(void)l;return 0;}
static u8 HandleWriteSectorNBytes(u8 i,u8 *p,u16 n){(void)i;(void)p;(void)n;return 0;}
static u8 HandleReplaceSector(u16 id,const struct SaveSectorLocation *l){
 assert(id<14);struct SaveSector *p=&flash[(gSaveCounter%2)*14+id];memset(p,0,sizeof *p);
 p->id=id;p->counter=gSaveCounter;p->checksum=CalculateChecksum(p->data,l[id].size);
 CopyFromSaveBlock3(id,p);writeMask|=1u<<id;return 0;
}
static u8 WriteSectorSignatureByte_NoOffset(u16 id,const struct SaveSectorLocation *l){
 (void)l;assert(id<14);flash[(gSaveCounter%2)*14+id].signature=SECTOR_SIGNATURE;signatureMask|=1u<<id;return 0;
}
static u8 WriteSectorSignatureByte(u16 id,const struct SaveSectorLocation *l){return WriteSectorSignatureByte_NoOffset((id-1)%14,l);}
static u8 HandleReplaceSectorAndVerify(u16 id,const struct SaveSectorLocation *l){return HandleReplaceSector(id-1,l);}
static u32 RestoreSaveBackupVars(const struct SaveSectorLocation *l){(void)l;gIncrementalSectorId=0;return 0;}
static void DoSaveFailedScreen(u8 type){(void)type;assert(0);}
'''
        link += '\n'.join(function(save,n) for n in ['HandleSavingData','WriteSaveBlock2','WriteSaveBlock1Sector'])
        checks = r'''
static void setup(void){sb2.encryptionKey=0x7145B39A;gSaveblock3.oldPrefix=0x00BA4321;SetBagItemsPointers();}
static void pockets(void){
 setup();struct BagPocket *p=&gBagPockets[POCKET_ITEMS];
 assert(p->capacity==254 && sizeof(struct ItemSlot)==4 && sizeof(gSaveblock3)==1484);
 for(int i=0;i<30;i++) assert(BagPocket_AddItem(p,100+i,9999));
 struct Bag before=sb1.bag;
 assert(BagPocket_AddItem(p,900,1)); // The exact full-original-pocket pickup regression.
 assert(!memcmp(&before,&sb1.bag,sizeof before));
 assert(BagPocket_GetSlotData(p,30).itemId==900 && BagPocket_GetSlotData(p,30).quantity==1);
 assert(BagPocket_RemoveItem(p,900,1));
 assert(!BagPocket_GetSlotData(p,30).itemId);
 for(int i=30;i<254;i++) assert(BagPocket_AddItem(p,100+i,1));
 assert(!BagPocket_AddItem(p,999,1));
 BagPocket_MoveItemSlot(p,253,0);assert(BagPocket_GetSlotData(p,0).itemId==353);
 assert(BagPocket_RemoveItem(p,353,1));BagPocket_CompactItems(p);
 assert(BagPocket_GetSlotData(p,0).itemId==100);
 u32 key=0x22114488;ApplyNewEncryptionKeyToBagItems(key);sb2.encryptionKey=key;
 assert(BagPocket_GetSlotData(p,0).quantity==9999 && BagPocket_GetSlotData(p,30).quantity==1);
 assert(gSaveblock3.oldPrefix==0x00BA4321);
 // Exact removal across stacks, even after a small stack is sorted to the front.
 ClearBag();p=&gBagPockets[POCKET_ITEMS];
 assert(BagPocket_AddItem(p,777,9999));assert(BagPocket_AddItem(p,777,1));
 BagPocket_MoveItemSlot(p,1,0);assert(BagPocket_GetSlotData(p,0).quantity==1);
 assert(BagPocket_AddItem(p,888,3));
 assert(BagPocket_RemoveItem(p,777,2));assert(BagPocket_CountTotalItemQuantity(p,777)==9998);
 assert(BagPocket_GetSlotData(p,0).itemId==777 && BagPocket_GetSlotData(p,0).quantity==9998);
 assert(BagPocket_GetSlotData(p,1).itemId==888 && BagPocket_GetSlotData(p,1).quantity==3);
 assert(BagPocket_GetSlotData(p,2).itemId==ITEM_NONE);
 // Every pocket uses the split boundary; PC remains an ordinary unsplit pocket.
 ClearBag();
 for(int n=0;n<POCKETS_COUNT;n++){
  p=&gBagPockets[n];
  for(u32 i=0;i<p->capacity;i++) assert(BagPocket_AddItem(p,1000+i,1));
  assert(!BagPocket_AddItem(p,2000,1));
  assert(BagPocket_RemoveItem(p,1000+p->capacity-1,1));
  assert(BagPocket_AddItem(p,2000,1));
 }
 struct ItemSlot pc[2]={{0}};struct BagPocket dummy={pc,2,POCKET_DUMMY};
 assert(BagPocket_AddItem(&dummy,600,999));assert(pc[0].quantity==999);
}
static void snapshots(void){
 setup();struct BagPocket *p=&gBagPockets[POCKET_ITEMS];
 for(int i=0;i<40;i++)assert(BagPocket_AddItem(p,100+i,5));
 struct Bag original=sb1.bag;struct LegacyBagExtension extra=gSaveblock3.legacyBag;
 gBagPosition.pocket=POCKET_BERRIES;gBagPosition.scrollPosition[0]=12;
 PrepareBagForWallyTutorial();assert(BagPocket_CountTotalItemQuantity(p,139)==0);
 assert(BagPocket_AddItem(p,600,1));RestoreBagAfterWallyTutorial();
 assert(!memcmp(&sb1.bag,&original,sizeof original));assert(!memcmp(&gSaveblock3.legacyBag,&extra,sizeof extra));
 assert(gBagPosition.pocket==POCKET_BERRIES && gBagPosition.scrollPosition[0]==12);
 LoadPlayerBag();
 ApplyNewEncryptionKeyToBagItems(0xAABBCCDD);sb2.encryptionKey=0xAABBCCDD;
 assert(BagPocket_RemoveItem(p,139,1));SavePlayerBag();
 assert(BagPocket_CountTotalItemQuantity(p,139)==5);
 assert(BagPocket_CountTotalItemQuantity(p,100)==5);
}
static void write_slot(int slot,int counter,int rotation){
 for(int id=0;id<14;id++){
  struct SaveSector *s=&flash[slot*14+(id+rotation)%14];memset(s,0,sizeof *s);
  s->id=id;s->counter=counter;s->signature=SECTOR_SIGNATURE;
  s->checksum=CalculateChecksum(s->data,4);CopyFromSaveBlock3(id,s);
 }
}
static void saves(void){
 setup();struct SaveSectorLocation locations[14];u32 data[14]={0};
 for(int i=0;i<14;i++)locations[i]=(struct SaveSectorLocation){&data[i],4};
 assert(LegacyBag_IsSaveValid(&gSaveblock3.legacyBag)); // Zero old padding is accepted.
 write_slot(0,14,3);
 struct BagPocket *p=&gBagPockets[POCKET_ITEMS];
 assert(BagPocket_AddItem(p,111,1));
 for(int i=0;i<40;i++)assert(BagPocket_AddItem(p,200+i,2));
 write_slot(1,15,7);
 assert(GetSaveValidStatus(locations)==SAVE_STATUS_OK && gSaveCounter==15);
 memset(&gSaveblock3,0,sizeof gSaveblock3);CopySaveSlotData(FULL_SAVE_SLOT,locations);
 assert(BagPocket_CountTotalItemQuantity(p,239)==2);
 assert(gSaveblock3.oldPrefix==0x00BA4321);
 // A damaged new extension must choose the older complete slot, not erase items silently.
 flash[14+(1+7)%14].saveBlock3Chunk[20]^=1;
 assert(GetSaveValidStatus(locations)==SAVE_STATUS_ERROR && gSaveCounter==14);
 CopySaveSlotData(FULL_SAVE_SLOT,locations);
 assert(!BagPocket_CountTotalItemQuantity(p,239)); // Only this newer extra item was absent in the older slot.
 // A real old save has entirely zero extension chunks, with the old prefix preserved.
 for(int n=0;n<14;n++)memset(flash[n].saveBlock3Chunk+(flash[n].id==0?4:0),0,116-(flash[n].id==0?4:0));
 assert(GetSaveValidStatus(locations)==SAVE_STATUS_ERROR && gSaveCounter==14);
 CopySaveSlotData(FULL_SAVE_SLOT,locations);assert(gSaveblock3.legacyBag.magic==LEGACY_BAG_MAGIC);
 assert(gSaveblock3.oldPrefix==0x00BA4321);
 // Future versions and corruption of the header are not mistaken for a legacy empty extension.
 gSaveblock3.legacyBag.magic^=1;assert(!LegacyBag_IsSaveValid(&gSaveblock3.legacyBag));
}
static void debug_fill(void){
 setup();DebugAction_PCBag_Fill_PocketItems(0);
 assert(BagPocket_CountTotalItemQuantity(&gBagPockets[0],1)==99);
 int used=0;for(u32 i=0;i<254;i++) used+=GetBagItemId(0,i)!=ITEM_NONE;
 assert(used==246);DebugAction_PCBag_Fill_PocketItems(0);
 int again=0;for(u32 i=0;i<254;i++)again+=GetBagItemId(0,i)!=ITEM_NONE;
 assert(again==used);assert(AddBagItem(900,1));
}
static void user_save(const char *path,u32 key){
 setup();sb2.encryptionKey=key;
 FILE *f=fopen(path,"rb");assert(f);assert(fread(&sb1.bag,1,sizeof sb1.bag,f)==sizeof sb1.bag);fclose(f);
 struct Bag original=sb1.bag;
 for(int n=0;n<POCKETS_COUNT;n++){
  struct BagPocket *p=&gBagPockets[n];
  enum Item newId=600;
  while(BagPocket_CountTotalItemQuantity(p,newId))newId++;
  assert(BagPocket_AddItem(p,newId,1));
 }
 // Every original pocket was full except MT/MO, so only its spare original slot may change.
 assert(!memcmp(sb1.bag.items,original.items,sizeof original.items));
 assert(!memcmp(sb1.bag.keyItems,original.keyItems,sizeof original.keyItems));
 assert(!memcmp(sb1.bag.pokeBalls,original.pokeBalls,sizeof original.pokeBalls));
 assert(!memcmp(sb1.bag.berries,original.berries,sizeof original.berries));
 for(int i=0;i<BAG_TMHM_COUNT;i++)if(original.TMsHMs[i].itemId)assert(!memcmp(&sb1.bag.TMsHMs[i],&original.TMsHMs[i],sizeof(struct ItemSlot)));
}
static void link_saves(void){
 setup();UpdateSaveAddresses();
 for(int i=0;i<80;i++)assert(BagPocket_AddItem(&gBagPockets[0],100+i,2));
 gSaveCounter=15;HandleSavingData(SAVE_LINK);
 assert(writeMask==0x3FFF && signatureMask==0x3FFF);
 assert(GetSaveValidStatus(gRamSaveSectorLocations)==SAVE_STATUS_OK && gSaveCounter==15);
 memset(&gSaveblock3,0,sizeof gSaveblock3);CopySaveSlotData(FULL_SAVE_SLOT,gRamSaveSectorLocations);
 assert(BagPocket_CountTotalItemQuantity(&gBagPockets[0],179)==2);
 assert(BagPocket_AddItem(&gBagPockets[0],901,1));
 writeMask=signatureMask=0;WriteSaveBlock2();int steps=0;
 while(!WriteSaveBlock1Sector())assert(++steps<14);
 assert(writeMask==0x3FFF && signatureMask==0x3FFF);
 assert(GetSaveValidStatus(gRamSaveSectorLocations)==SAVE_STATUS_OK);
 memset(&gSaveblock3,0,sizeof gSaveblock3);CopySaveSlotData(FULL_SAVE_SLOT,gRamSaveSectorLocations);
 assert(BagPocket_CountTotalItemQuantity(&gBagPockets[0],901)==1);
}
int main(int argc,char **argv){if(argc==4){user_save(argv[2],strtoul(argv[3],NULL,0));return 0;}assert(argc==2);if(!strcmp(argv[1],"pockets"))pockets();else if(!strcmp(argv[1],"saves"))saves();else if(!strcmp(argv[1],"snapshots"))snapshots();else if(!strcmp(argv[1],"link"))link_saves();else debug_fill();return 0;}
'''
        code = harness + defines + '\n' + pocket + '\n' + types + fixture + legacy + inventory + wrappers + debug + snapshots + flash + link + checks
        source_path=Path(cls.directory.name)/'extended.c'
        cls.executable=Path(cls.directory.name)/'extended'
        source_path.write_text(code)
        result=subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Wno-unused-parameter','-fsanitize=address,undefined',str(source_path),'-o',str(cls.executable)],capture_output=True,text=True)
        if result.returncode:
            raise AssertionError(result.stderr)

    def check_scenario(self, scenario):
        result=subprocess.run([str(self.executable),scenario],capture_output=True,text=True)
        self.assertEqual(result.returncode,0,result.stderr)

    def test_full_original_pockets_can_receive_more_and_rekey(self):
        self.check_scenario('pockets')

    def test_old_save_loading_round_trip_and_corrupt_extension_fallback(self):
        self.check_scenario('saves')

    def test_wally_and_link_bag_snapshots_restore_extra_slots(self):
        self.check_scenario('snapshots')

    def test_debug_fill_leaves_eight_slots_and_does_not_duplicate_stacks(self):
        self.check_scenario('debug')

    def test_link_and_incremental_saves_persist_all_extension_chunks(self):
        self.check_scenario('link')
