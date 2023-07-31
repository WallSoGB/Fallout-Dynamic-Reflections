#pragma once

#include "ShadowLightShader.hpp"
#include "NiRefObject.hpp"
#include "NiProperty.hpp"
#include "TES.hpp"
#include "NiSourceCubeMap.hpp"

class TESMain;

NiSmartPointer(CubemapRenderer);

class CubemapRenderer {
public:
	enum SkipMode {
		SKIP_NONE = 0,
		SKIP_PLAYER = 1,
		SKIP_ALL = 2,
	};

	static bool bIsInterior;

	static NiSourceCubeMapPtr spExteriorCubemap;
	static NiSourceCubeMapPtr spInteriorCubemap;
	static NiTexture* pSourceEyeCubeMap;
	static NiRenderedCubeMapPtr spRenderedCubemapPlayer;
	static NiRenderedCubeMapPtr spRenderedCubemapWorld;
	static BSCubeMapCameraPtr spPlayerCubeCam;
	static BSCubeMapCameraPtr spWorldCubeCam;
	
	static bool bEnabled;
	static bool bOverride;
	static bool bOverrideBrightness;
	static bool bHighQuality;
	static bool bLowQuality;
	static bool bRenderObjectLOD;
	static bool bRenderLandLOD;
	static bool bScreenSpaceInterior;
	static bool bNoWorldInInteriors;
	static bool bNoWorldInExteriors;

	static UInt32 uiPlayerCubemapSize;
	static UInt32 uiWorldCubemapSize;
	static UInt32 uiPlayerUpdateRate;
	static UInt32 uiWorldUpdateRate;

	static UInt32 uiScreenSpaceCubemapSize;
	static UInt32 uiScreenSpaceBlurRadius;

	static float fPlayerViewDistance;
	static float fWorldViewDistance;

	static float fExteriorBrightnessMult;
	static float fInteriorBrightnessMult;

	static void InitHooks();
	static void UpdateFog(ShadowSceneNode* apScene, float afViewDistance);
	static void RestoreFog(ShadowSceneNode* apScene);
	static void RenderCubemap();
	static void RenderSceenSpaceCubemap();
	static const NiTexture* __fastcall GetTexture_Hook(ShadowLightShader* apThis, void*, BSShaderPPLightingProperty* apShaderProp, UInt32 auiTextureNumber);
	static const void __fastcall Render_Hook(TESMain* apThis);
	static void __fastcall SetOffScreenRTGroup_Hook(TESMain* apThis, void*, BSRenderedTexture* pTexture, BOOL bIsMSAA, UInt32 uiClearMode);
	static void __fastcall UpdateToggles_Hook(ShadowLightShader* apThis, void*, RenderPassTypes aeRenderPassType, NiGeometry* apGeo, BSShaderPPLightingProperty* apShaderProp, NiMaterialProperty* apMatProp, BSRenderPass* apRenderPass, NiAlphaProperty* apAlphaProp);
	static void __fastcall BSShaderProperty_LoadBinary_Hook(BSShaderProperty* apThis, void*, DWORD* kStream);
};