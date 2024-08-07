#pragma once

#include "BSShader.hpp"
#include "NiVector4.hpp"
#include "NiShaderConstantMapEntry.hpp"

class NiD3DShaderConstantMap;
class BSFogProperty;
class BSShaderPPLightingProperty;

NiSmartPointer(NiDX9ShaderDeclaration);

class ShadowLightShader : public BSShader {
public:
	virtual void SetupShadowTexture(UInt32 aeRenderPass, BSShaderPPLightingProperty* apShaderProp);
	virtual void Func_80(); // nullsub
	virtual void InitShaders();
	virtual void InitVertexShaders();
	virtual void InitPixelShaders();
	virtual void CreatePasses();
	virtual void SetToggles(NiGeometry* apGeometry, BSFogProperty* apFogProp, NiMaterialProperty* apMatProp);

	NiDX9ShaderDeclarationPtr	spShaderDeclarationGlowParallaxSkin;
	NiDX9ShaderDeclarationPtr	spShaderDeclarationSkinned;
	NiDX9ShaderDeclarationPtr	spShaderDeclarationModelSpaceNormals;
	NiDX9ShaderDeclarationPtr	spShaderDeclarationLandscape;
	NiD3DShaderConstantMapPtr	spPixelConstantMap;
	NiD3DShaderConstantMapPtr	spVertexConstantMap;
	NiD3DShaderConstantMapPtr	spPixelConstantMap2;
	NiD3DShaderConstantMapPtr	spVertexConstantMap2;

	enum VertexEntries {
		kVX_WorldViewProjTranspose = 0,
		kVX_WorldTranspose = 1,
		kVX_SkinWorldViewProjTranspose = 2,
		kVX_ShadowProj = 3,
		kVX_ShadowProjData = 4,
		kVX_ShadowProjTransform = 5,
		kVX_LightData = 6,
		kVX_FogParam_ShadowVolumeFatness = 7,
		kVX_FogColor_ShadowVolumeExtrudeDistance = 8,
		kVX_EyePosition = 9,
		kVX_BoneMatrix3 = 10,
		kVX_PrevBoneMatrix3 = 11,
		kVX_SkinWorldTranspose = 12,
		kVX_WorldViewTranspose = 13,
		kVX_SkinWorldViewTranspose = 14,
		kVX_Time = 15,
		kVX_HighDetailRange = 16,
		kVX_BoundCenter = 17,
		kVX_DepthData = 18,
		kVX_PrevWorldViewPT = 19,
		kVX_PrevWorldViewT = 20,
		kVX_LODLandParams = 21,
	};

	enum PixelEntries {
		kPX_EyeDir = 0,
		kPX_AmbientColor = 1,
		kPX_LightColors = 2,
		kPX_EmittanceColor = 3,
		kPX_Toggles = 4,
		kPX_EyePosition = 5,
		kPX_LightDirection = 6,
		kPX_LightDirection0 = 7,
		kPX_LightDirection1 = 8,
		kPX_LightDirection2 = 9,
		kPX_LightDirection3 = 10,
		kPX_HairTint = 15,
		kPX_RefractionParams = 16,
		kPX_FogParams = 17,
		kPX_FogColor = 18,
		kPX_FogPlane = 19,
		kPX_LODTEXPARAMS = 20,
		kPX_STBBColorConstants = 21,
	};

	void SetDiffuseMap(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, UInt32 auiTextureNumber);

	static ShadowLightShader* GetShader();

	static NiD3DVertexShader* GetVertexShader(UInt32 auID);
	static void SetVertexShader(UInt32 auID, NiD3DVertexShader* apShader);

	static NiD3DPixelShader* GetPixelShader(UInt32 auID);
	static void SetPixelShader(UInt32 auID, NiD3DPixelShader* apShader);

	static void InitPasses_2xEnvMap();
};
ASSERT_SIZE(ShadowLightShader, 0x8C)

// Custom
class ShadowLightShaderManager {
public:
	struct FogProperties
	{
		struct FogParameters
		{
			float fDistFar;
			float fDistNear;
			float fPower;
			float fUnknown;
		};

		FogParameters Parameters;
		NiColorA Color;
	};

	struct Toggles
	{
		float bUseVertexColors;
		float Unknown;
		float fSpecularity;
		float fAlphaTestRef;
	};

	struct VertexConstants {
		// WorldViewProjTranspose 0
		// SkinWorldViewProjTranspose 1
		// WorldViewTranspose 4
		// SkinWorldViewTranspose 5

		// 8
		static __forceinline D3DMATRIX* GetWorldTranspose() {
			return (D3DMATRIX*)0x11FECC8;
		}

		// 9
		static __forceinline D3DMATRIX* GetSkinWorldTranspose() {
			return (D3DMATRIX*)0x11FEC88;
		}

		// 12
		static __forceinline NiVector4* GetHighDetailRange() {
			return (NiVector4*)0x11FA2E0;
		}

		// 13
		static __forceinline float* GetTime() {
			return (float*)0x11FD868;
		}

		// 14 - params, 15 - color
		static __forceinline FogProperties* GetFogParam() {
			return (FogProperties*)0x11FA280;
		}

		// 16
		static __forceinline NiVector4* EyePosition() {
			return (NiVector4*)0x11FD894;
		}

		// 17
		static __forceinline NiVector4* GetDepthData() {
			return (NiVector4*)0x11FD954;
		}

		// 18
		static __forceinline D3DMATRIX* GetShadowProj() {
			return (D3DMATRIX*)0x11FD968;
		}

		// 19
		static __forceinline NiVector4* GetLODLandParams() {
			return (NiVector4*)0x11FA0B0;
		}

		// 22
		static __forceinline NiVector4* GetShadowProjData() {
			return (NiVector4*)0x11FD874;
		}

		// 23
		static __forceinline NiVector4* GetShadowProjTransform() {
			return (NiVector4*)0x11FD884;
		}

		// 24
		static __forceinline NiVector4* GetBoundCenter() {
			return (NiVector4*)0x11FD8B4;
		}

		// 25; aka LightDirection
		static __forceinline NiVector4* GetLightData(UInt32 index) {
			return &((NiVector4*)0x11FD9A8)[index];
		}

		// 35
		static __forceinline D3DMATRIX* PrevWorldViewPT() {
			return (D3DMATRIX*)0x11FED08;
		}

		// 39
		static __forceinline D3DMATRIX* PrevWorldViewT() {
			return (D3DMATRIX*)0x11FED48;
		}

		// 98
		float* GetPrevBoneMatrix3() {
			return 0;
		}
	};

	struct PixelConstants {
		// 0
		static __forceinline NiVector4* GetEyeDir() {
			return (NiVector4*)0x11FD8A4;
		}

		// 1
		static __forceinline NiColorA* GetAmbientColor() {
			return (NiColorA*)0x11FA0C0;
		}

		// 2
		static __forceinline NiColorA* GetEmittanceColor() {
			return (NiColorA*)0x11FA270;
		}

		// 3
		static __forceinline NiColorA* GetLightColor(int index) {
			return &((NiColorA*)0x11FA0D0)[index];
		}

		// 14 - params, 15 - color
		static __forceinline FogProperties* GetFogParams() {
			return (FogProperties*)0x11FA280;
		}

		// 16
		static __forceinline float* GetFogPlane() {
			return (float*)0x11FA2A0;
		}

		// 18
		static __forceinline NiVector4* GetLightPosition(UInt32 index) {
			return &((NiVector4*)0x11FD9A8)[index];
		}

		// 17
		static __forceinline NiVector4* GetEyePosition() {
			return (NiVector4*)0x11FD894;
		}

		// 27
		static __forceinline Toggles* GetToggles() {
			return (Toggles*)0x11FA2D0;
		}

		// 28
		static __forceinline NiColorA* HairTint() {
			return (NiColorA*)0x11FA090;
		}

		// 29
		static __forceinline NiVector4* GetRefractionParams() {
			return (NiVector4*)0x11FD944;
		}

		// 30
		static __forceinline NiVector4* GetSTBBColorConstants() {
			return (NiVector4*)0x11FA2F0;
		}

		// 31
		static __forceinline NiPoint4* GetLODTEXPARAMS() {
			return (NiPoint4*)0x11FA300;
		}
	};

	static __forceinline NiShaderConstantMapEntry* GetPixelConstantMapEntry(ShadowLightShader::PixelEntries index) {
		return ((NiShaderConstantMapEntry**)0x11FEC30)[index];
	}
	static __forceinline NiShaderConstantMapEntry* GetVertexConstantMapEntry(ShadowLightShader::VertexEntries index) {
		return ((NiShaderConstantMapEntry**)0x11FEBD8)[index];
	}
};