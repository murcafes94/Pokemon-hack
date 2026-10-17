#ifndef GUARD_LEGACY_BAG_H
#define GUARD_LEGACY_BAG_H

#define LEGACY_BAG_MAGIC 0x3147424C // LBG1: persistent format version 1.

bool32 LegacyBag_IsSaveValid(const struct LegacyBagExtension *bag);
void LegacyBag_Initialize(void);
void LegacyBag_PrepareSave(void);
struct ItemSlot *LegacyBag_GetSlot(struct BagPocket *pocket, u32 position);

#endif
