#include "global.h"
#include "item.h"
#include "legacy_bag.h"

#if !IS_FRLG
STATIC_ASSERT(sizeof(struct SaveBlock1) == 15568, LegacySaveBlock1Size);
STATIC_ASSERT(sizeof(struct SaveBlock2) == 3884, LegacySaveBlock2Size);
STATIC_ASSERT(sizeof(struct Bag) == 744, LegacyOriginalBagSize);
STATIC_ASSERT(offsetof(struct SaveBlock1, bag) == 1376, LegacyBagOffset);
STATIC_ASSERT(offsetof(struct SaveBlock1, flags) == 4720, LegacyFlagsOffset);
STATIC_ASSERT(offsetof(struct SaveBlock1, vars) == 5020, LegacyVarsOffset);
STATIC_ASSERT(offsetof(struct SaveBlock2, encryptionKey) == 172, LegacyKeyOffset);
STATIC_ASSERT(offsetof(struct SaveBlock3, legacyBag) == 4, LegacySaveBlock3Prefix);
#endif
STATIC_ASSERT(LEGACY_BAG_ITEMS_COUNT < 255, LegacyBagListIndices);

// Hash raw stored quantities; validation does not depend on the current key.
static u32 LegacyBag_Checksum(const struct LegacyBagExtension *bag)
{
    const u8 *bytes = (const u8 *)bag->items;
    u32 hash = 2166136261u;
    for (u32 i = 0; i < sizeof(*bag) - offsetof(struct LegacyBagExtension, items); i++)
        hash = (hash ^ bytes[i]) * 16777619u;
    return hash;
}

bool32 LegacyBag_IsSaveValid(const struct LegacyBagExtension *bag)
{
    const u8 *bytes = (const u8 *)bag;
    bool32 legacy = TRUE;
    // Previous Legacy ROMs wrote zero into this unused sector padding.
    for (u32 i = 0; i < sizeof(*bag); i++)
        if (bytes[i] != 0)
            legacy = FALSE;
    if (legacy)
        return TRUE;
    return bag->magic == LEGACY_BAG_MAGIC && bag->checksum == LegacyBag_Checksum(bag);
}

void LegacyBag_Initialize(void)
{
    struct LegacyBagExtension *bag = &gSaveBlock3Ptr->legacyBag;
    if (bag->magic != LEGACY_BAG_MAGIC)
    {
        memset(bag, 0, sizeof(*bag));
        bag->magic = LEGACY_BAG_MAGIC;
        bag->checksum = LegacyBag_Checksum(bag);
    }
}

void LegacyBag_PrepareSave(void)
{
    LegacyBag_Initialize();
    gSaveBlock3Ptr->legacyBag.checksum = LegacyBag_Checksum(&gSaveBlock3Ptr->legacyBag);
}

struct ItemSlot *LegacyBag_GetSlot(struct BagPocket *pocket, u32 position)
{
    u32 baseCount;
    struct ItemSlot *extra;
    LegacyBag_Initialize();
    switch (pocket->id)
    {
    case POCKET_ITEMS:
        baseCount = BAG_ITEMS_COUNT;
        extra = gSaveBlock3Ptr->legacyBag.items;
        break;
    case POCKET_KEY_ITEMS:
        baseCount = BAG_KEYITEMS_COUNT;
        extra = gSaveBlock3Ptr->legacyBag.keyItems;
        break;
    case POCKET_POKE_BALLS:
        baseCount = BAG_POKEBALLS_COUNT;
        extra = gSaveBlock3Ptr->legacyBag.pokeBalls;
        break;
    case POCKET_TM_HM:
        baseCount = BAG_TMHM_COUNT;
        extra = gSaveBlock3Ptr->legacyBag.machines;
        break;
    case POCKET_BERRIES:
        baseCount = BAG_BERRIES_COUNT;
        extra = gSaveBlock3Ptr->legacyBag.berries;
        break;
    default:
        return &pocket->itemSlots[position];
    }
    return position < baseCount ? &pocket->itemSlots[position] : &extra[position - baseCount];
}
