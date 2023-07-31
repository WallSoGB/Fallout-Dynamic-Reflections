#include "TES.hpp"
#include "BSTempNode.hpp"

TES* TES::GetSingleton() {
	return *(TES**)0x11DEA10;
}

Sky* TES::GetSky() {
	return GetSingleton()->pSky;
}

// 0x4FD3E0
TESWorldSpace* TES::GetWorldSpace() {
	return GetSingleton()->pWorldSpace;
}

// 0x5F36F0
TESObjectCELL* TES::GetInterior() {
	return GetSingleton()->pInteriorCell;
}

// 0x4511E0
bool TES::IsCellLoaded(TESObjectCELL* apCell, bool abIgnoreBuffered) {
    if (!apCell)
        return 0;

    bool bResult = false;
    switch (apCell->GetState()) {
    case TESObjectCELL::CS_LOADING:
    case TESObjectCELL::CS_LOADED:
    case TESObjectCELL::CS_DETACHING:
        if (abIgnoreBuffered)
            break;
        bResult = true;
        break;
    case TESObjectCELL::CS_ATTACHING:
    case TESObjectCELL::CS_ATTACHED:
        bResult = true;
        break;
    default:
        break;
    }
    return bResult;
}

// 0x457050
GridCell* TES::GetGridCell(SInt32 aX, SInt32 aY) {
    return pGridCellArray->GetCell(aX, aY);
}

// 0x4568C0
void TES::CreateTextureImage(const char* apPath, NiSourceTexturePtr* aspTexture, bool abNoFileOK, bool abArchiveOnly) {
    ThisStdCall(0x4568C0, this, apPath, aspTexture, abNoFileOK, abArchiveOnly);
}