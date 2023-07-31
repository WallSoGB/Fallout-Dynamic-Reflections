#include "TESWorldSpace.hpp"

BGSTerrainManager* TESWorldSpace::GetTerrainManager() {
    return ThisStdCall<BGSTerrainManager*>(0x586170, this);
}