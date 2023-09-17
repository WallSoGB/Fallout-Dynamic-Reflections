#pragma once

#include "BSShaderLightingProperty.hpp"
#include "EffectShaderProperty.hpp"
#include "BSShaderTextureSet.hpp"
#include "NiPoint4.hpp"
#include "TangentSpaceData.hpp"

class NiSourceTexture;
class BSShaderAccumulator;
class Lighting30ShaderProperty;

NiSmartPointer(BSShaderPPLightingProperty);

class BSShaderPPLightingProperty : public BSShaderLightingProperty {
public:
	BSShaderPPLightingProperty();
	virtual ~BSShaderPPLightingProperty();

	virtual void							CopyTo3(Lighting30ShaderProperty* apTarget);
	virtual void							CopyProperties(BSShaderProperty* apTarget);
	virtual void							Unk_52();
	virtual void							Unk_53();
	virtual void							PickClampMode(UInt32 auiMode);
	virtual NiTexturingProperty::ClampMode	GetClampMode();
	virtual void							SetClampMode(NiTexturingProperty::ClampMode aeClamp);
	virtual UInt16							GetLandscapeTextureCount();
	virtual int								GetLandPassCount();
	virtual void							SetTexture(BSTextureSet::TextureSlots aeTextureSlot, UInt32 auiTextureNumber, NiTexture* apTexture);
	virtual NiTexture*						GetTexture(BSTextureSet::TextureSlots aeTextureSlot, UInt32 auiTextureNumber);
	virtual void							Unk_61();
	virtual void							SetDiffuseTexture(int, NiTexture* apTexture);
	virtual void							SetNormalTexture(int, NiTexture* apTexture);
	virtual void							SetGlowMask();
	virtual void							SetSpecular();
	virtual float							GetSpecularFade();
	virtual float							GetEnvMapFade();
	virtual void							AddPassesOld(NiTriShape* apGeometry, UInt32 aeEnabledPasses, WORD* apusPassCount, UInt32 eRenderMode, BSShaderAccumulator* apShaderAccum, NiTListItem<ShadowSceneLight>* a4);
	virtual void							AddPasses(NiTriShape* apGeometry, UInt32 aeEnabledPasses, WORD* apusPassCount, UInt32 eRenderMode, BSShaderAccumulator* apShaderAccum, int a4);

	struct Unk0C4 {
		char cUnk0[10];
	};

	UInt32 unk07C;
	UInt32 unk080;
	NiColorA kHairTint;
	NiColorA kLandBlendParams;
	BSShaderTextureSetPtr spTextureSet;
	UInt16 usLandscapeTextures;
	NiSourceTexturePtr* ppTextures[6];
	BSShaderPPLightingProperty::Unk0C4* ptr0C4;
	UInt16 unk0C8;
	BSShaderPPLightingProperty::Unk0C4* pbTextureIsSpecular;
	TangentSpaceDataPtr spTangentSpaceData;
	UInt32 unk0D4;
	NiTexturingProperty::ClampMode eClampMode;
	EffectShaderPropertyPtr spTexEffectData;
	float fRefractionStrength;
	UInt32 iRefractionFirePeriod;
	float fParallaxMaxPasses;
	float fParallaxScale;
	NiPoint4 kLODTextureParams;
	BSRenderPass* pDepthPass;

	CREATE_OBJECT(BSShaderPPLightingProperty, 0xB68D50);

	NiTexture* GetDiffuse(UInt32 auID = 0)		{ return ppTextures[0][auID]; };
	NiTexture* GetNormal(UInt32 auID = 0)		{ return ppTextures[1][auID]; };
	NiTexture* GetGlow(UInt32 auID = 0)			{ return ppTextures[2][auID]; };
	NiTexture* GetParallax(UInt32 auID = 0)		{ return ppTextures[3][auID]; };
	NiTexture* GetCubeMap(UInt32 auID = 0)		{ return ppTextures[4][auID]; };
	NiTexture* GetEnvMask(UInt32 auID = 0)		{ return ppTextures[5][auID]; };
};

ASSERT_SIZE(BSShaderPPLightingProperty, 0x104);