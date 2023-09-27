#pragma once

#include "BSShaderAccumulator.hpp"
#include "NiDX9Renderer.hpp"
#include "TangentSpaceData.hpp"

class BSShader;

class BSShaderManager {
public:
	enum eSceneGraphEnum {
		BSSM_SSN_WORLD = 0x0,
		BSSM_SSN_UI = 0x1,
		BSSM_SSN_PREVIEW = 0x2,
		BSSM_SSN_UI_LOADING_MENU = 0x3,
		BSSM_SSN_COUNT = 0x4,
	};

	enum Shader {
		BSSM_SHADER_DEFAULT = 0x0,
		BSSM_SHADER_SHADOWLIGHT = 0x1,
		BSSM_SHADER_TALL_GRASS = 0x2,
		BSSM_SHADER_DISTANT_LOD = 0x3,
		BSSM_SHADER_ST_BRANCH = 0x4,
		BSSM_SHADER_ST_FROND = 0x5,
		BSSM_SHADER_ST_LEAF = 0x6,
		BSSM_SHADER_BLOOD_SPLATTER = 0x7,
		BSSM_SHADER_DISTANT_TREE = 0x8,
		BSSM_SHADER_DEBUG = 0x9,
		BSSM_SHADER_SKY = 0xA,
		BSSM_SHADER_HAIR = 0xD,
		BSSM_SHADER_SKIN = 0xE,
		BSSM_SHADER_PARALLAX = 0xF,
		BSSM_SHADER_NiDX9ShaderDeclaration = 0x10,
		BSSM_SHADER_WATER = 0x11,
		BSSM_SHADER_PARTICLE = 0x18,
		BSSM_SHADER_BOLT = 0x19,
		BSSM_SHADER_BEAM = 0x1A,
		BSSM_SHADER_LIGHTING30 = 0x1D,
		BSSM_SHADER_PRECIPITATION = 0x1E,
		BSSM_SHADER_TILE = 0x20,
		BSSM_SHADER_NOLIGHTING = 0x21,
		BSSM_SHADER_VOLUMETRIC_FOG = 0x22,
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


	static bool* const bIsHDR;
	static bool* const bIsInInterior;
	static float* const fLODLandDrop;

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