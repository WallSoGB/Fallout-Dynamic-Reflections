#include "TESObjectCELL.hpp"
#include "BGSLightingTemplate.hpp"
#include "TESWorldSpace.hpp"


// 0x450FD0
TESObjectCELL::CELL_STATE TESObjectCELL::GetState() {
	return static_cast<TESObjectCELL::CELL_STATE>(cCellState);
}

// 0x450FF0
bool TESObjectCELL::IsAttached() {
	return GetState() == CS_ATTACHED;
}

bool TESObjectCELL::GetInheritFlag(CELL_INHERIT_FLAGS aeFlag) {
	return (aeFlag & uiInheritFlags) != 0;
}

BGSLightingTemplate* TESObjectCELL::GetLightingTemplate() {
	return pLightingTemplate;
}

// 0x5471E0
float TESObjectCELL::GetExteriorWaterHeight() {
#if 1
	return ThisStdCall<float>(0x5471E0, this);
#else
	if (!HasWater() || IsInterior()) {
		return -3.4028235e38;
	}

	if (fWaterHeight != 3.402823466385289e38) {
		return fWaterHeight;
	}

	TESWorldSpace* pWorldspace = GetWorldspace();
	return pWorldspace ? pWorldspace->defaultWaterHeight : 0.0f;
#endif
}

// 0x545CB0
NiNode* TESObjectCELL::Get3D() {
	if (pLoadedData)
		return pLoadedData->spCell3D;
	return nullptr;
}

// 0x456FC0
NiNode* TESObjectCELL::GetChildNode(CELLNODE aeNode) {
	NiNode* pMaster = Get3D();
	if (pMaster)
		return static_cast<NiNode*>(pMaster->GetAt(aeNode));
	else
		return nullptr;
}

// 0x45C9A0
NiNode* TESObjectCELL::GetGeometry(UInt32 auiIndex) {
	NiNode* pLand = GetChildNode(CN_LAND);
	if (pLand)
		return static_cast<NiNode*>(pLand->GetAt(auiIndex));
	else
		return nullptr;
}

// 0x587410
SInt32 TESObjectCELL::GetCoord(SInt32 x, SInt32 y) {
	return (x << 16) | y;
}

TESObjectCELL::InteriorData* TESObjectCELL::GetInteriorData() {
	if (IsInterior()) {
		return pCellData.pCellDataInterior;
	}
	return nullptr;
}