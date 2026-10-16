"""Run the actual inventory C functions with a small host-side save fixture."""
import pathlib
import re
import subprocess
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[2]


def function(source, name):
    start = source.rfind('\n', 0, source.index(name + '(')) + 1
    brace = source.index('{', start)
    depth = 1
    end = brace + 1
    while depth:
        depth += (source[end] == '{') - (source[end] == '}')
        end += 1
    return source[start:end].replace('NONNULL ', '')


class CapacityTests(unittest.TestCase):
    def test_actual_c_inventory_boundaries(self):
        source = (ROOT / 'src/item.c').read_text()
        constants = (ROOT / 'include/constants/items.h').read_text()
        defines = '\n'.join(re.findall(r'^#define MAX_(?:BAG|PC)_ITEM_CAPACITY[^\n]+', constants, re.M))
        functions = '\n'.join(function(source, n) for n in (
            'BagPocket_GetFreeSpaceForItem', 'CheckSlotAndUpdateCount',
            'BagPocket_AddItem', 'BagPocket_CountTotalItemQuantity'))
        harness = r'''
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
typedef uint32_t u32;
typedef uint16_t u16;
typedef int bool32;
enum Item { ITEM_NONE, POTION, BERRY };
enum { POCKET_ITEMS, POCKET_TM_HM, POCKET_BERRIES, POCKET_DUMMY };
#define TRUE 1
#define FALSE 0
#define min(a,b) ((a) < (b) ? (a) : (b))
#define AllocZeroed(n) calloc(1,n)
#define Free free
struct ItemSlot { enum Item itemId; u16 quantity; };
struct BagPocket { struct ItemSlot *itemSlots; u32 capacity; int id; };
static struct ItemSlot BagPocket_GetSlotData(struct BagPocket *p, u32 i) { return p->itemSlots[i]; }
static void BagPocket_SetSlotItemIdAndCount(struct BagPocket *p, u32 i, enum Item id, u16 n) {
    p->itemSlots[i] = (struct ItemSlot){id, n};
}
'''
        checks = r'''
int main(void) {
    struct ItemSlot slots[30] = {{0}};
    struct BagPocket p = {slots, 2, POCKET_ITEMS};
    assert(MAX_BAG_ITEM_CAPACITY == 9999);
    assert(BagPocket_AddItem(&p, POTION, 999));
    assert(BagPocket_AddItem(&p, POTION, 9000));
    assert(slots[0].quantity == 9999);
    assert(BagPocket_AddItem(&p, POTION, 1));
    assert(slots[1].quantity == 1);
    assert(BagPocket_AddItem(&p, POTION, 9998));
    struct ItemSlot before[30]; memcpy(before, slots, sizeof slots);
    assert(!BagPocket_AddItem(&p, POTION, 1));
    assert(!memcmp(before, slots, sizeof slots));
    assert(!BagPocket_GetFreeSpaceForItem(&p, BERRY));
    for (int id = POCKET_TM_HM; id <= POCKET_BERRIES; id++) {
        memset(slots, 0, sizeof slots); p.id = id;
        assert(BagPocket_AddItem(&p, BERRY, 9999));
        assert(!BagPocket_GetFreeSpaceForItem(&p, BERRY));
        assert(!BagPocket_AddItem(&p, BERRY, 1));
        assert(slots[1].itemId == ITEM_NONE);
        slots[1] = slots[0]; slots[0] = (struct ItemSlot){ITEM_NONE, 0};
        assert(!BagPocket_GetFreeSpaceForItem(&p, BERRY));
        assert(!BagPocket_AddItem(&p, BERRY, 1));
        slots[1].quantity = 9998;
        assert(BagPocket_AddItem(&p, BERRY, 1));
        assert(slots[0].itemId == ITEM_NONE && slots[1].quantity == 9999);
    }
    memset(slots, 0, sizeof slots); p.id = POCKET_DUMMY; p.capacity = 1;
    assert(BagPocket_AddItem(&p, POTION, 999));
    assert(!BagPocket_GetFreeSpaceForItem(&p, POTION));
    assert(!BagPocket_AddItem(&p, POTION, 1));
    p.id = POCKET_ITEMS; p.capacity = 30;
    for (int i = 0; i < 30; i++) slots[i] = (struct ItemSlot){POTION, 9999};
    assert(BagPocket_CountTotalItemQuantity(&p, POTION) == 65535);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as directory:
            c = pathlib.Path(directory) / 'inventory.c'
            exe = pathlib.Path(directory) / 'inventory'
            c.write_text(harness + defines + '\n' + functions + checks)
            subprocess.run(['cc', '-std=c99', '-Wall', '-Wextra', '-Werror',
                            str(c), '-o', str(exe)], check=True, capture_output=True)
            subprocess.run([str(exe)], check=True, capture_output=True)
