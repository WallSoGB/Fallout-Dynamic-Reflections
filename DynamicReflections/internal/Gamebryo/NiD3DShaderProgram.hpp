#pragma once

#include "NiGPUProgram.hpp"
#include "Defines.hpp"

class NiD3DShaderProgramCreator;
class NiShaderConstantMapEntry;

class NiD3DShaderProgram : public NiGPUProgram {
public:

	virtual NiRTTI* GetRTTI(void);
	virtual void Unk8(void);
	virtual void UnkC(void);
	virtual void Unk10(void);
	virtual void Unk14(void);
	virtual void Unk18(void);
	virtual void Unk1C(void);
	virtual void Unk20(void);
	virtual void Unk24(void);
	virtual void Unk28(void);
	virtual void Unk2C(void);
	virtual void Unk30(void);
	virtual void Unk34(void);
	virtual void Unk38(void);
	virtual void Unk3C(void);
	virtual void Unk40(void);
	virtual UInt32 GetVariableCount(void);
	virtual const char* GetVariableName(void);
	virtual const char* GetName(void);
	virtual const char* SetName(const char* pszName);
	virtual char* GetShaderProgramName(void);
	virtual void SetShaderProgramName(const char* pszName);
	virtual UInt32 GetCodeSize(void);
	virtual void* GetCode(void);
	virtual void SetCode(UInt32 uiSize, void* pvCode);
	virtual NiD3DShaderProgramCreator* GetCreator(void);
	virtual void SetCreator(NiD3DShaderProgramCreator* pkCreator);
	virtual void SetShaderConstant(NiShaderConstantMapEntry*, const void*, UInt32);
	virtual bool SetShaderConstantArray(NiShaderConstantMapEntry* pkEntry, const void* pvDataSource, UInt32 uiNumEntries, UInt32 uiRegistersPerEntry, UInt16 pusReorderArray);

	char* m_pszName;
	char* m_pszShaderProgramName;
	UInt32 m_uiCodeSize;
	void* m_pvCode;
	NiD3DShaderProgramCreator* m_pkCreator;
	LPDIRECT3DDEVICE9 m_pkD3DDevice;
	NiD3DRenderer* m_pkD3DRenderer;
	NiD3DRenderState* m_pkD3DRenderState;
};

ASSERT_SIZE(NiD3DShaderProgram, 0x2C);