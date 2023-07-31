#include "BGSTerrainManager.hpp"
#include "BSMultiBoundNode.hpp"
#include "BSSegmentedTriShape.hpp"
#include "PlayerCharacter.hpp"
#include <TES.hpp>
#include <GameAPI.h>

bool BGSTerrainManager::HasRootNode() {
    return pRootNode != nullptr;
}

NiNode* BGSTerrainManager::GetWaterLODNode() {
    return spWaterLODNode;
}

NiNode* BGSTerrainManager::GetLODRoot() {
	return spLODRoot;
}

UInt32 BGSTerrainManager::GetLODLevel() {
    return uiLODLevel;
}

NiNode* BGSTerrainManager::GetRootLandLODNode() {
    return *(NiNodePtr*)0x11D86A8;
}

NiNode* BGSTerrainManager::GetRootObjectLODNode() {
    return *(NiNodePtr*)0x11D8690;
}

NiNode* BGSTerrainManager::GetRootTreeLODNode() {
    return *(NiNodePtr*)0x11D8690;
}