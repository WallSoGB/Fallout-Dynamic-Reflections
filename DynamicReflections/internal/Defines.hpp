#pragma once
#include <d3d9.h>
#include <d3dx9math.h>

#include <NiUpdateData.hpp>

class NiDX9Renderer;
class PlayerCharacter;

typedef NiDX9Renderer NiD3DRenderer;

typedef struct _D3DVECTOR4 {
	float x;
	float y;
	float z;
	float w;
} D3DVECTOR4;
#define D3DVECTOR4_DEFINED

// Align D3DXMATRIX
typedef __declspec(align(16)) D3DXMATRIX    D3DXALIGNEDMATRIX;

#define g_thePlayer *(PlayerCharacter**)0x011DEA3C


enum NiShaderError {
	NISHADERERR_OK = 0x0,
	NISHADERERR_UNKNOWN = 0x1,
	NISHADERERR_SHADERNOTFOUND = 0x100,
	NISHADERERR_ENTRYNOTFOUND = 0x10,
	NISHADERERR_DUPLICATEENTRYKEY = 0x20,
	NISHADERERR_ENTRYNOTADDED = 0x30,
	NISHADERERR_INVALIDMAPPING = 0x40,
	NISHADERERR_SETCONSTANTFAILED = 0x50,
	NISHADERERR_DYNEFFECTNOTFOUND = 0x60,
};

static void SetThreadName(HANDLE apThread, const char* apName) {
	wchar_t wideName[1024];
	MultiByteToWideChar(CP_UTF8, 0, apName, -1, wideName, 1024);

	// Append "[FNV]" to the beginning of the thread name
	wchar_t newWideName[1024];
	wcsncpy_s(newWideName, L"[FNV] ", _TRUNCATE);
	wcsncat_s(newWideName, wideName, 1024 - wcslen(newWideName) - 1);
	_MESSAGE("Creating thread %s", apName);
	SetThreadDescription(apThread, (PCWSTR)newWideName);
}

static float Lerp(float start_value, float end_value, float pct)
{
	return (start_value + (end_value - start_value) * pct);
}

static NiUpdateData g_defaultUpdateData = NiUpdateData();

static bool bIgnoreMultiBounds = false;

#define STACK_ALLOCATE(class_name, pointer_name) \
    char pointer_name[sizeof(class_name)]; \
    class_name* p##pointer_name = (class_name*)pointer_name;

#define DEBUG_MESSAGES false