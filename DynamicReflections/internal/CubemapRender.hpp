#pragma once

#include "ShadowLightShader.hpp"
#include "Lighting30Shader.hpp"
#include "NiRefObject.hpp"
#include "NiProperty.hpp"
#include "TES.hpp"
#include "NiSourceCubeMap.hpp"

class TESMain;

class CubemapRenderer {
public:
	enum SkipMode {
		SKIP_NONE = 0,
		SKIP_PLAYER = 1,
		SKIP_WORLD = 2,
		SKIP_ALL = 3,
	};

	enum PurgeTextures {
		PURGE_WORLD = 1,
		PURGE_PLAYER = 2,
		PURGE_INTERIOR = 4,
		PURGE_ALL = PURGE_WORLD | PURGE_PLAYER | PURGE_INTERIOR,
	};

	static NiSourceCubeMapPtr spExteriorCubemap;
	static NiSourceCubeMapPtr spInteriorCubemap;
	static NiTexture* pSourceEyeCubeMap;
	static NiRenderedCubeMapPtr spRenderedCubemapPlayer;
	static NiRenderedCubeMapPtr spRenderedCubemapWorld;
	static BSCubeMapCameraPtr spPlayerCubeCam;
	static BSCubeMapCameraPtr spWorldCubeCam;
	
	static bool bRendering;

	static bool bEnabled;
	static bool bOverride;
	static bool bOverrideBrightness;
	static bool bHighQuality;
	static bool bLowQuality;
	static bool bRenderObjectLOD;
	static bool bRenderCloseObjectLOD;
	static bool bRenderLandLOD;
	static bool bScreenSpaceInterior;
	static bool bNoWorldInInteriors;
	static bool bNoWorldInExteriors;
	static bool bUseAmbient;


	// Script toggles
	static bool bRefreshCell;
	static bool bDumpToFile;


	static UInt32 uiCubemapSize;

	static UInt32 uiPlayerUpdateRate;
	static UInt32 uiWorldUpdateRate;

	static UInt32 uiScreenSpaceCubemapSize;
	static UInt32 uiScreenSpaceBlurRadius;

	static float fPlayerViewDistance;
	static float fWorldViewDistance;

	static float fExteriorBrightnessMult;
	static float fInteriorBrightnessMult;

	static void InitHooks();
	static void LoadShaders();
	static void CheckILSStatus();
	static bool SearchCamera(TESObjectCELL* apCell);
	static void UpdateFog(ShadowSceneNode* apScene, float afViewDistance, NiCamera* apCamera);
	static void RestoreFog(ShadowSceneNode* apScene);
	static void ManageTextureResidency(UInt32 uiForcePurge = 0);
	static bool CanRenderInteriorCubemap();


	static BSCubeMapCamera* GetPlayerCamera();
	static BSCubeMapCamera* GetWorldCamera();

	static BSRenderedTexture* GetPlayerTexture();
	static BSRenderedTexture* GetWorldTexture();



	static void CreateScreenSpaceTextures(UInt32 uiCubeSize);

	static void RenderCubemap();

	static void RenderSceenSpaceCubemap();

	static void SaveCubemapToFiles();

	static void __fastcall SLS_SetCubeMap_Hook(ShadowLightShader* apThis, void*, BSShaderPPLightingProperty* apShaderProp, UInt32 auiTexturePass, UInt32 auiTextureNumber);
	static void __fastcall Shader30_SetCubeMap_Hook(Lighting30Shader* apThis, void*, NiD3DPass* apPass, BSShaderPPLightingProperty* apShaderProp, RenderPassTypes aeRenderPass);
	static void* __fastcall Render_Hook(void* apThis);
	static void __fastcall SetOffScreenRTGroup_Hook(TESMain* apThis, void*, BSRenderedTexture* pTexture, BOOL bIsMSAA, UInt32 uiClearMode);
	static void __fastcall SLS_UpdateToggles_Hook(ShadowLightShader* apThis, void*, RenderPassTypes aeRenderPassType, NiGeometry* apGeo, BSShaderPPLightingProperty* apShaderProp, NiMaterialProperty* apMatProp, BSRenderPass* apRenderPass, NiAlphaProperty* apAlphaProp);
	static void __fastcall Shader30_UpdateToggles_Hook(Lighting30Shader* apThis, void*, BSShaderPPLightingProperty* apShaderProp);
	static void __fastcall BSShaderProperty_LoadBinary_Hook(BSShaderProperty* apThis, void*, DWORD* kStream);
};