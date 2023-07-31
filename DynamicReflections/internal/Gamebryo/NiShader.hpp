#pragma once

#include "NiRefObject.hpp"
#include "NiFixedString.hpp"
#include "NiRTTI.hpp"
#include "NiGeometry.hpp"

class NiDynamicEffectState;
class NiGeometryBufferData;
class NiSkinInstance;

class NiShader : public NiRefObject {
public:
	virtual NiRTTI* GetRTTI();
	virtual void Func_03();
	virtual void Func_04();
	virtual void Func_05();
	virtual void Func_06();
	virtual void Func_07();
	virtual void Func_08();
	virtual void Func_09();
	virtual void Func_10();
	virtual void Func_11();
	virtual void Func_12();
	virtual void Func_13();
	virtual void Func_14();
	virtual void Func_15();
	virtual void Func_16();
	virtual void Func_17();
	virtual bool IsInitialized();
	virtual void Initialize();
	virtual bool SetupGeometry(NiGeometry* pkGeometry);
	virtual UInt32 PreProcessPipeline(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound);
	virtual void UpdatePipeline(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound);
	virtual void SetupRenderingPass(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound);
	virtual UInt32 SetupTransformations(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound);
	virtual void Func_25(NiGeometry* geo, const NiSkinInstance* skinInstance, const NiSkinPartition::Partition* skinPartition, NiGeometryBufferData* rendererData, int shaderProperties, int a7, const NiTransform* worldTransform, NiBound* worldBound);
	virtual UInt32 SetupShaderPrograms(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound);
	virtual NiGeometryBufferData* PrepareGeometryForRendering(NiGeometry* pkGeometry, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState);
	virtual UInt32 PostRender(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound);
	virtual UInt32 PostProcessPipeline(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound);
	virtual void Func_30(NiPropertyState* pShaderProps);
	virtual void UpdateConstants(NiPropertyState* pShaderProps);
	// Do not use, call NiD3DShader::SetBlendAlpha instead
	virtual void vSetBlendAlpha(NiPropertyState* pShaderProps);
	virtual void SetTestAlpha(NiPropertyState* pShaderProps);
	virtual void Func_34(NiPropertyState* pShaderProps, bool bHasAlpha);
	virtual void Func_35(NiPropertyState* shaderProps);
	virtual int FirstPass();
	virtual int NextPass();
	virtual void StreamCanSkip();
	virtual void Func_39();
	virtual void Func_40();
	virtual void Func_41();
	virtual void Func_42();
	virtual void SetShaderConstant();
	virtual void Func_44();
	virtual void SetShaderConstantArray();
	virtual void Func_46();

	NiFixedString m_kName;
	UInt32 m_uiImplementation;
	bool m_bInitialized;
};

ASSERT_SIZE(NiShader, 0x14);