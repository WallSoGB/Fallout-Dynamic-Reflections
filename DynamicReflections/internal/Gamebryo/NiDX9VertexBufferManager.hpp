#pragma once

#include "NiRefObject.hpp"
#include <d3d9.h>
#include "NiCriticalSection.hpp"

class NiDX9VertexBufferManager : public NiRefObject {
public:
	LPDIRECT3DDEVICE9 m_pkD3DDevice9;
	void* m_kSystemMemResources[8];
	BYTE a[14];
	UInt32 m_uiFrameID;
	void* m_pvTempBuffer;
	UInt32 m_uiTempBufferSize;
	void* m_pvLockedBuffer;
	UInt32 m_uiLockedBufferSize;
	BYTE c[48];
	NiCriticalSection m_kVBCriticalSection;
	void* m_kManagedResources[8];
	void* m_kDefaultResources[7];
};