#pragma once

#include "BSSceneGraph.hpp"

class SceneGraph : public BSSceneGraph {
public:
	static double __fastcall CalculateNoLODFarDistEx(SceneGraph* apThis);

	static __forceinline SceneGraph* GetWorldRoot() { return *(SceneGraph**)0x11DEB7C; };
	__forceinline NiCamera* GetCamera() { return spCamera.m_pObject; };
	__forceinline BSCullingProcess* GetCullingProcess() { return pCuller; };
	__forceinline void SetCameraFOV(float afFOV, bool a3, NiCamera* apCamera, bool bSetLODAdjust) {
		ThisStdCall(0xC52020, this, afFOV, a3, apCamera, bSetLODAdjust);
	}
	static __forceinline void UpdateParticleShaderFoVData(float afFOV) {
#if 1
		CdeclCall(0xB54000, afFOV);
#else
		double f1 = afFOV * 0.5f * 0.0175f;
		ParticleShader::SetFOVAdjust((std::sin(f1) / std::cos(f1)) / (std::sin(0.65) / std::cos(0.65)));
#endif
	}

	NiNode* GetFlyCamNode() {
		return ThisStdCall<NiNode*>(0x45BC00, this, 0);
	}
};