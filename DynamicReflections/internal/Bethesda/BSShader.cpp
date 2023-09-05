#include "BSShader.hpp"
#include "NiD3DPixelShader.hpp"
#include "BSFile.hpp"
#include "BSShaderManager.hpp"
#include <format>

// 0xBE1750
NiD3DPixelShader* __fastcall BSShader::CreatePixelShader(BSShader* apThis, void*, const char* apPath, D3DXMACRO* apMacro, const char* apShaderVersion, const char* apFilename) {
	LPDIRECT3DPIXELSHADER9 pShader = nullptr;
	DWORD* pShaderData = nullptr;
	bool bFreeMem = false;

	if (!pShaderData) {
		std::string sDataPath = std::format("Data\\Shaders\\Loose\\{}", apFilename);
		BSFile* pArchiveFile = CdeclCall<BSFile*>(0xAFDF20, sDataPath.c_str(), 0, 0x4000, 32);
		if (pArchiveFile && pArchiveFile->m_bGood) {
			_MESSAGE("Loaded %s", sDataPath.c_str());
			UInt32 uiSize = 0;

			uiSize = pArchiveFile->GetSize();
			pShaderData = static_cast<DWORD*>(MemoryManager::Allocate(uiSize));
			bFreeMem = true;

			pArchiveFile->ReadBuffer(pShaderData, uiSize);
		}
	}

	BSShaderManager::ShaderPackage* pShaderPkg = BSShaderManager::ShaderPackage::GetInstance();
	if (!pShaderData && pShaderPkg) {
		BSShaderManager::ShaderPackage::RawShader* pRaw = pShaderPkg->GetShader(apFilename);
		pShaderData = &pRaw->shader;
	}

	NiDX9Renderer* pRenderer = BSShaderManager::GetRenderer();
	NiD3DPixelShader* pPixelShader = nullptr;
	if (SUCCEEDED(pRenderer->GetD3DDevice()->CreatePixelShader(pShaderData, &pShader))) {
		pPixelShader = NiD3DPixelShader::Create(pRenderer);
		pPixelShader->SetShaderHandle(pShader);
	}

	if (bFreeMem)
		MemoryManager::Deallocate(pShaderData);

	return pPixelShader;
}