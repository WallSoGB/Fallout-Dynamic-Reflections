#pragma once

#include "NiTexture.hpp"
#include "NiPersistentSrcTextureRendererData.hpp"
#include "NiPixelData.hpp"
#include "NiFile.hpp"

NiSmartPointer(NiSourceTexture);

class NiSourceTexture : public NiTexture {
public:
	NiSourceTexture();
	~NiSourceTexture();

	virtual void LoadPixelDataFromFile();
	virtual void DestroyAppPixelData();
	virtual bool CreateRendererData();

	NiFixedString m_kFilename;
	NiFixedString m_kPlatformFilename;
	NiPersistentSrcTextureRendererDataPtr m_spPersistentSrcRendererData;
	NiPixelDataPtr m_spSrcPixelData;
	bool m_bStatic;
	bool m_bLoadDirectToRendererHint;
	bool m_bSrcRendererDataIsPersistent;
	bool unk43;
	NiFile* m_pFile;

	CREATE_OBJECT(NiSourceTexture, 0xA60070)
};

ASSERT_SIZE(NiSourceTexture, 0x48);