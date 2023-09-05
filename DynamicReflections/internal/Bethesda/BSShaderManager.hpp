#pragma once

#include "BSShaderAccumulator.hpp"
#include "NiDX9Renderer.hpp"
#include "TangentSpaceData.hpp"

class BSShader;

enum eSceneGraphEnum {
	BSSM_SSN_WORLD = 0x0,
	BSSM_SSN_UI = 0x1,
	BSSM_SSN_PREVIEW = 0x2,
	BSSM_SSN_UI_LOADING_MENU = 0x3,
	BSSM_SSN_COUNT = 0x4,
};


class BSShaderManager {
public:
	enum Shader {
		kShader_Default = 0x0,
		kShader_ShadowLightShader = 0x1,
		kShader_TallGrassShader = 0x2,
		kShader_DistantLODShader = 0x3,
		kShader_SpeedTreeBranchShader = 0x4,
		kShader_SpeedTreeFrondShader = 0x5,
		kShader_SpeedTreeLeafShader = 0x6,
		kShader_BSShaderBloodSplatter = 0x7,
		kShader_BSDistantTreeShader = 0x8,
		kShader_DebugShader = 0x9,
		kShader_SkyShader = 0xA,
		kShader_HairShader = 0xD,
		kShader_SkinShader = 0xE,
		kShader_ParallaxShader = 0xF,
		kShader_NiDX9ShaderDeclaration = 0x10,
		kShader_WaterShader = 0x11,
		kShader_ParticleShader = 0x18,
		kShader_BoltShader = 0x19,
		kShader_BeamShader = 0x1A,
		kShader_Lighting30Shader = 0x1D,
		kShader_PrecipitationShader = 0x1E,
		kShader_TileShader = 0x20,
		kShader_BSShaderNoLighting = 0x21,
		kShader_VolumetricFogShader = 0x22,
	};

	enum LightingPasses {
		AMBIENT = 0x1,
		DIFFUSE = 0x2,
		TEXTURE = 0x4,
		SPECULAR = 0x8,
		SHADOW = 0x10,
		CANOPYSHADOW = 0x20,
		OPT = 0x100,
		ALL = AMBIENT | DIFFUSE | TEXTURE | SPECULAR | SHADOW | CANOPYSHADOW | OPT,
	};

	struct ShaderPackage {
		struct RawShader {
			char cFileName[260];
			DWORD shader;
		};

		const char* pcPackagePath;
		DWORD dword4;
		NiTStringMap<RawShader*> kShaders;

		static ShaderPackage* GetInstance() { return *(ShaderPackage**)0x11F9498; }
		RawShader* GetShader(const char* apcShaderName) {
			return ThisStdCall<RawShader*>(0xB7FAC0, this, apcShaderName);
		}
	};


	static bool* bIsHDR;

	static __forceinline ShadowSceneNode* GetShadowSceneNode(eSceneGraphEnum aeType) {
		return ((ShadowSceneNode**)0x11F91C8)[aeType];
	};

	static __forceinline NiRect<float> GetViewport() { return *(NiRect<float>*)0x11AD840; };

	static BSShaderAccumulator* GetAccumulator() { return (*(BSShaderAccumulatorPtr*)0x11F95EC); }

	static void SetAccumulator(BSShaderAccumulator* apAccumulator) { *(BSShaderAccumulatorPtr*)0x11F95EC = apAccumulator; }

	static NiDX9Renderer* GetRenderer() { return *(NiD3DRenderer**)0x11F9508; }

	static __forceinline NiCamera* GetCamera() { return *(NiCamera**)0x11F917C;	}

	static __forceinline void SetCamera(NiCamera* apCamera) { *(NiCamera**)0x11F917C = apCamera; }

	static __forceinline void SetRenderMode15ShaderAccumulator(BSShaderAccumulator* apAccumulator) { *(BSShaderAccumulatorPtr*)0x11F95F0 = apAccumulator; }

	static __forceinline void SetRenderMode(BSShaderAccumulator::etRenderMode auiRenderMode) {
		CdeclCall(0xB4F450, auiRenderMode);
	}

	static NiTexture* GetArmorReflectionCubeMap() { return *(NiTexture**)0x11F95D4; }
	static NiTexture* GetEyeReflectionCubeMap() { return *(NiTexture**)0x11F9544; }
	static void SetArmorReflectionCubeMap(NiTexture* apTexture) { *(NiTexture**)0x11F95D4 = apTexture; }
	static void SetEyeReflectionCubeMap(NiTexture* apTexture) { *(NiTexture**)0x11F9544 = apTexture; }
};