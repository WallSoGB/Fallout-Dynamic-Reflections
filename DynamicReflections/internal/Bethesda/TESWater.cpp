#include "TESWater.hpp"
#include "TES.hpp"
#include <GameSettings.h>

bool* const TESWater::bPauseTime = (bool*)0x11F91C5;

void* TESWater::RenderSurface_Hook(NiRefObjectPtr* apThis) {
	if(*bPauseTime)
		return nullptr;
	return apThis->m_pObject;
}
// 0x4E3320
void TESWater::UpdateLOD(NiCamera* apCamera, bool abForceDisplay) {
	ThisStdCall(0x4E3320, this, apCamera, abForceDisplay);
}

// 0x4E21B0
void TESWater::RenderWater(NiCamera* apSceneCamera, bool abForceDisplay) {
	ThisStdCall(0x4E21B0, this, apSceneCamera, abForceDisplay);
}

bool TESWater::ReflectionFix_Hook() {
	if (!*eRendererSettingCollection::Water_bUseWaterReflections)
		return true;
	else
		return TESWater::IsUnderwater();
}

TESObjectCELL* __fastcall TESWater::ReflectionFix_Hook2(TES* tes) {
	if (!*eRendererSettingCollection::Water_bUseWaterReflections)
		return (TESObjectCELL*)1;
	else
		return tes->pInteriorCell;
}