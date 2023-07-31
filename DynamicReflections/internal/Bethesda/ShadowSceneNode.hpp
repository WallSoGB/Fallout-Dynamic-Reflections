#pragma once

#include "NiNode.hpp"
#include "ShadowSceneLight.hpp"
#include "BSCompoundFrustum.hpp"
#include "BSCubeMapCamera.hpp"
#include "DList.hpp"
#include "BSFogProperty.hpp"

class BSCullingProcess;

class ShadowSceneNode : public NiNode {
public:
	UInt32									unk0AC[2];
	NiTListBase<ShadowSceneLight>			lights;
	NiTListBase<ShadowSceneLight>			actorShadowCasters;
	NiTListBase<ShadowSceneLight>*			unk0CC;
	NiTListBase<ShadowSceneLight>*			unk0D0;
	NiTListBase<ShadowSceneLight>*			unk0D4;
	ShadowSceneLight*						pSceneLight1;
	ShadowSceneLight*						pSceneLight2;
	ShadowSceneLight*						pSunLight;		
	NiTPointerListBase<ShadowSceneLight*>	lLightQueueAdd;
	NiTPointerListBase<ShadowSceneLight*>	lLightList;
	NiTPointerListBase<ShadowSceneLight*>	dynamicLights;
	NiTPointerListBase<NiNode*>				list108;
	NiTPointerListBase<NiNode*>				list114;
	UInt8									cSceneGraphIndex;
	NiObject*								pObject124;
	BSCubeMapCamera*						pShadowMapCubeCam;
	UInt32									unk12C;
	bool									bDisableLightUpdate;
	bool									bWireframe;
	BSFogPropertyPtr						spFog;
	BSCompoundFrustum						kCompoundFrustum;
	bool									bVisibleUnboundSpace;
	BSPortalGraph*							pBSPortalGraph;
	NiPoint3								kLightingOffset;
	NiPoint3								kCameraPos;
	bool									bAllowLightRemoveQueues;

	void DisableLightUpdate(bool abDisable);

	double GetLuminanceAtPoint(NiPoint3 position, int* aiNumberlights, float* afAmbientLum, float* a7, NiLight* apIgnore);

	void SetShadowCastToLight(NiLight* apLight, bool bEnableShadow);

	void PreOnVisible(BSCullingProcess* arCuller);

	static void __fastcall UpdateMultiBoundVisibility(ShadowSceneNode* apThis, void*, BSMultiBoundNode* apNode, NiPoint3 akViewPoint, BSCullingProcess* apCuller);
};

static_assert(sizeof(ShadowSceneNode) == 0x200);