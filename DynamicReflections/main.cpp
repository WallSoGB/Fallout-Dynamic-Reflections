#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "d3dx9.lib")
#include "nvse/PluginAPI.h"
#include "windows.h"
#include "SafeWrite.h"
#include "GameData.h"
#include "fstream"
#include "string"
#include "simpleini/SimpleIni.h"
#include "d3d9.h"
#include "CubemapRender.hpp"
#include "BSShaderManager.hpp"
#include <GameSettings.h>

NVSEInterface* g_nvseInterface{};
IDebugLog	   gLog("logs\\DynamicReflections.log");

static LPSTR g_CurrentDir;

void MessageHandler(NVSEMessagingInterface::Message* msg) {
	switch (msg->type) {
	case NVSEMessagingInterface::kMessage_DeferredInit:
		CubemapRenderer::pSourceEyeCubeMap = *(NiSourceTexture**)0x11F9544;
		CubemapRenderer::CheckILSStatus();
		break;
	case NVSEMessagingInterface::kMessage_PreLoadGame:
		CubemapRenderer::bRefreshCell = true;
		break;
	default:
		break;
	}
}

bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info) {
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "Dynamic Reflections";
	info->version = 135;

	return true;
}

#define RegisterScriptCommand(name) 	nvse->RegisterCommand(&kCommandInfo_ ##name)
#define REG_CMD(name) RegisterScriptCommand(name)

bool Cmd_CubemapRefreshCell_Execute(COMMAND_ARGS) {
	*result = true;
	CubemapRenderer::bRefreshCell = true;
	return true;
}

bool Cmd_CubemapSaveToFile_Execute(COMMAND_ARGS) {
	*result = true;
	CubemapRenderer::bDumpToFile = true;
	return true;
}

DEFINE_COMMAND_PLUGIN(CubemapSaveToFile, "Saves player's cubemap as a DDS file in the root folder", false, NULL)
DEFINE_COMMAND_PLUGIN(CubemapRefreshCell, "Forcibly scans the current cell for new cubemap cameras", false, NULL)

bool NVSEPlugin_Load(NVSEInterface* nvse) {

	UInt32 const uiOpCodeBase = 0x3F00;

	nvse->SetOpcodeBase(uiOpCodeBase);

	REG_CMD(CubemapRefreshCell);
	REG_CMD(CubemapSaveToFile);

	if (!nvse->isEditor) {
		CSimpleIniA ini;
		ini.SetUnicode();
		SI_Error rc = ini.LoadFile("Data\\NVSE\\Plugins\\DynamicReflections.ini");
		if (rc < 0) { 
			_MESSAGE("INI not found!");
		};

		((NVSEMessagingInterface*)nvse->QueryInterface(kInterface_Messaging))->RegisterListener(nvse->GetPluginHandle(), "NVSE", MessageHandler);


		// Fix for broken reflection toggles
		ReplaceCall(0x4E2B8D, (UInt32)TESWater::ReflectionFix_Hook);
		ReplaceCall(0x4E28A9, (UInt32)TESWater::ReflectionFix_Hook2);

		// Cubemaps
		CubemapRenderer::bEnabled = ini.GetBoolValue("Main", "bEnable", 1);
		if (CubemapRenderer::bEnabled) {
			CubemapRenderer::bOverride = ini.GetBoolValue("Quality", "bOverride", 1);

			CubemapRenderer::bHighQuality = ini.GetBoolValue("Quality", "bHighQuality", 0);
			CubemapRenderer::bLowQuality = ini.GetBoolValue("Quality", "bLowQuality", 0);

			if (CubemapRenderer::bLowQuality && CubemapRenderer::bHighQuality) {
				CubemapRenderer::bLowQuality = false;
				CubemapRenderer::bHighQuality = false;
				_MESSAGE("Both bLowQuality and bHighQuality are set to true. Disabling both.");
			}

			CubemapRenderer::bRenderObjectLOD = ini.GetBoolValue("Quality", "bRenderObjectLOD", 1);
			CubemapRenderer::bRenderLandLOD = ini.GetBoolValue("Quality", "bRenderLandLOD", 1);
			CubemapRenderer::bOverrideBrightness = ini.GetBoolValue("Quality", "bOverrideBrightness", 0);
			CubemapRenderer::fInteriorBrightnessMult = ini.GetDoubleValue("Quality", "fInteriorBrightnessMult", 0.7);
			CubemapRenderer::fExteriorBrightnessMult = ini.GetDoubleValue("Quality", "fExteriorBrightnessMult", 0.8);
			CubemapRenderer::bScreenSpaceInterior = ini.GetBoolValue("Quality", "bScreenSpaceInterior", 1);
			CubemapRenderer::uiScreenSpaceCubemapSize = ini.GetLongValue("Quality", "uiScreenSpaceCubemapSize", 128);
			CubemapRenderer::uiScreenSpaceBlurRadius = ini.GetLongValue("Quality", "uiScreenSpaceBlurRadius", 10);
			CubemapRenderer::bUseAmbient = ini.GetLongValue("Quality", "bUseAmbient", 1);


			// Player settings
			CubemapRenderer::uiPlayerUpdateRate = ini.GetLongValue("Player", "uiPlayerUpdateRate", 1);
			CubemapRenderer::fPlayerViewDistance = ini.GetDoubleValue("Player", "fPlayerViewDistance", 6500.0);

			// World settings
			CubemapRenderer::uiWorldUpdateRate = ini.GetLongValue("World", "uiWorldUpdateRate", 3);
			CubemapRenderer::fWorldViewDistance = ini.GetDoubleValue("World", "fWorldViewDistance", 200000.0);
			CubemapRenderer::bNoWorldInInteriors = ini.GetBoolValue("World", "bNoWorldInInteriors", 0);
			CubemapRenderer::bNoWorldInExteriors = ini.GetBoolValue("World", "bNoWorldInExteriors", 0);


			CubemapRenderer::InitHooks();
		}
	}
	return true;
}