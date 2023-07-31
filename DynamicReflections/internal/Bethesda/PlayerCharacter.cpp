#include "PlayerCharacter.hpp"
#include "Defines.hpp"
#include "MemoryManager.hpp"

static const UInt32 s_PlayerCharacter_GetCurrentQuestTargets = 0x00952BA0;	// BuildedQuestObjectiveTargets* : (void)
static const UInt32 s_PlayerCharacter_GenerateNiNode = 0x0094E1D0; // Func0072

PlayerCharacter* PlayerCharacter::GetSingleton() {
	return g_thePlayer;
}

QuestObjectiveTargets* PlayerCharacter::GetCurrentQuestObjectiveTargets() {
	return (QuestObjectiveTargets*)ThisStdCall(s_PlayerCharacter_GetCurrentQuestTargets, this);
}

NiNode* PlayerCharacter::GetNode(const bool bCurrentActive) {
	if (bCurrentActive) {
		return spPlayerNode.m_pObject;
	}
	else {
		TLSData* pTLSData = TLSData::GetTLSData();
		if (this == pTLSData->pLastNiNodeREFR)
			return pTLSData->pLastNiNode;
		else if (pLoadedData)
			return pLoadedData->spNode;
		else
			return 0;
	}
};
// Less worse version as used by some modders
bool PlayerCharacter::SetSkeletonPath_v1c(const char* newPath) {
	if (!bThirdPerson) {
		// ###TODO: enable in first person
		return false;
	}

	return true;
}

// Current basically not functioning version, but should show some progress in the end.. I hope
bool PlayerCharacter::SetSkeletonPath(const char* newPath) {
	if (!bThirdPerson) {
		// ###TODO: enable in first person
		return false;
	}

#ifdef NVSE_CORE
#ifdef _DEBUG
	// store parent of current niNode
	/*NiNode* niParent = (NiNode*)(renderState->niNode->m_parent);

	if (renderState->niNode) renderState->niNode->Dump(0, "");

	// set niNode to NULL via BASE CLASS Set3D() method
	ThisStdCall(s_TESObjectREFR_Set3D, this, NULL, true);

	// modify model path
	if (newPath) {
		TESNPC* base = DYNAMIC_CAST(baseForm, TESForm, TESNPC);
		base->model.SetPath(newPath);
	}

	// create new NiNode, add to parent
	//*(g_bUpdatePlayerModel) = 1;

	// s_PlayerCharacter_GenerateNiNode = (MobileObject::Func0053 in Oblivion)
	NiNode* newNode = (NiNode*)ThisStdCall(s_PlayerCharacter_GenerateNiNode, this, false);	// got a body WITHOUT the head :)

	if (newNode) newNode->Dump(0, "");

	if (niParent)
		niParent->AddObject(newNode, 1);	// no complaints
	//*(g_bUpdatePlayerModel) = 0;

	newNode->SetName("Player");	// no complaints

	if (newNode) newNode->Dump(0, "");

	if (playerNode) playerNode->Dump(0, "");

	// get and store camera node
	// ### TODO: pretty this up
	UInt32 vtbl = *((UInt32*)newNode);				// ok
	UInt32 vfunc = *((UInt32*)(vtbl + 0x9C));		// ok
	NiObject* cameraNode = (NiObject*)ThisStdCall(vfunc, newNode, "Camera3rd");				// returns NULL !!!
	*g_3rdPersonCameraNode = cameraNode;

	cameraNode = (NiObject*)ThisStdCall(vfunc, (NiNode*)this->playerNode, "Camera1st");		// returns NULL !!!
	*g_1stPersonCameraNode = cameraNode;

	AnimateNiNode();*/
#endif
#endif
	return true;
}