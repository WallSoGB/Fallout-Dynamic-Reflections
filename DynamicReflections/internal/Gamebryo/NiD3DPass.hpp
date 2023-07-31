#pragma once

#include "NiD3DShaderConstantMap.hpp"
#include "NiD3DTextureStage.hpp"
#include "NiGeometry.hpp"
#include "NiD3DPixelShader.hpp"
#include "NiD3DVertexShader.hpp"
#include "NiTArray.hpp"

class NiD3DRenderStateGroup;
class NiDX9RenderState;

class NiD3DPass {
public:
	virtual void Destroy(bool);
	virtual UInt32 SetupShaderPrograms(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkBuffData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound, UInt32 uiPass);
	virtual void SetupRenderingPass(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, NiGeometryBufferData* pkBuffData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform& kWorld, const NiBound& kWorldBound, unsigned int uiPass);
	virtual UInt32 PostProcessRenderingPass(UInt32 uiPass);

	char m_szName[16];
	UInt32 m_uiCurrentStage;
	UInt32 m_uiStageCount;
	UInt32 m_uiTexturesPerPass;
	NiTObjectArray<NiPointer<NiD3DTextureStage>> m_kStages;
	NiD3DRenderStateGroup* m_pkRenderStateGroup;
	NiD3DShaderConstantMapPtr m_spPixelConstantMap;
	char* m_pcPixelShaderProgramFile;
	char* m_pcPixelShaderEntryPoint;
	char* m_pcPixelShaderTarget;
	NiD3DPixelShaderPtr m_spPixelShader;
	NiD3DShaderConstantMapPtr m_spVertexConstantMap;
	char* m_pcVertexShaderProgramFile;
	char* m_pcVertexShaderEntryPoint;
	char* m_pcVertexShaderTarget;
	float float58;
	NiD3DVertexShaderPtr m_spVertexShader;
	bool m_bSoftwareVP;
	bool m_bRendererOwned;
	UInt32 m_uiRefCount;

	static NiDX9RenderState* GetD3DRenderState() { return *(NiDX9RenderState**)0x126F728; };
	static NiD3DRenderer* GetRenderer() { return *(NiD3DRenderer**)0x126F724; };
	static UInt32 GetMaxTextureBlendStages() { return *(UInt32*)0x11BF558; };
	void SetRenderState(D3DRENDERSTATETYPE uiRenderState, UInt32 uiValue, bool bSave) { ThisStdCall(0xB71A10, this, uiRenderState, uiValue, bSave); };
	void RemoveRenderState(UInt32 uiRenderState) { ThisStdCall(0xE7F550, this, uiRenderState); };

	int SetStage(NiD3DTextureStage* uiStageNum, NiD3DTextureStage* pkStage) { return ThisStdCall<int>(0xE802B0, this, uiStageNum, pkStage); };

	void SetVertexShader(NiD3DVertexShader* pkVertexShader) { m_spVertexShader = pkVertexShader; };
	NiD3DVertexShader* GetVertexShader() { return m_spVertexShader; };
	void SetPixelShader(NiD3DPixelShader* pkPixelShader) { m_spPixelShader = pkPixelShader; };
	NiD3DPixelShader* GetPixelShader() { return m_spPixelShader; };

	void SetPixelConstantMap(NiD3DShaderConstantMap* pMap) { m_spPixelConstantMap = pMap; };
	void SetVertexConstantMap(NiD3DShaderConstantMap* pMap) { m_spVertexConstantMap = pMap; };

	void CreateNewPass() { ThisStdCall(0xE804D0, NiPointer(this)); };

	__forceinline void IncRefCount()
	{
		InterlockedIncrement(&m_uiRefCount);
	}

	__forceinline void DecRefCount()
	{
		if (InterlockedDecrement(&m_uiRefCount) == 0)
			Destroy(true);
	}
};

ASSERT_SIZE(NiD3DPass, 0x68);
ASSERT_OFFSET(NiD3DPass, m_uiStageCount, 0x18);