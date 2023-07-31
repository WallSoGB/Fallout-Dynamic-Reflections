#include "Actor.hpp"
#include "TESObjectWEAP.hpp"

static const UInt32	s_Actor_EquipItem = 0x0088C650;	// maybe, also, would be: 007198E0 for FOSE	4th call from the end of TESObjectREFR::RemoveItem (func5F)
static const UInt32	s_Actor_UnequipItem = 0x0088C790;	// maybe, also, would be: 007133E0 for FOSE next sub after EquipItem

void Actor::EquipItem(TESForm* objType, UInt32 equipCount, ExtraDataList* itemExtraList, UInt32 unk3, bool lockEquip, UInt32 unk5) {
	ThisStdCall(s_Actor_EquipItem, this, objType, equipCount, itemExtraList, unk3, lockEquip, unk5);
}

void Actor::UnequipItem(TESForm* objType, UInt32 unk1, ExtraDataList* itemExtraList, UInt32 unk3, bool lockUnequip, UInt32 unk5) {
	ThisStdCall(s_Actor_UnequipItem, this, objType, unk1, itemExtraList, unk3, lockUnequip, unk5);
}

bool Actor::IsInReloadAnim() {
	return ThisStdCall(0x8A8870, this);
}

bool Actor::IsWeaponOut() {
	return pBaseProcess && pBaseProcess->IsWeaponOut();
}

bool Actor::IsAiming() {
	return pBaseProcess && pBaseProcess->IsAiming();
}