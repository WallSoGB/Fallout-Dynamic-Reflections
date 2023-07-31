#pragma once

#include "NiFile.hpp"
#include "BSString.hpp"

class BSFile : public NiFile {
public:
	BSFile();
	~BSFile();

	virtual bool	Open(int, bool abTextMode);
	virtual bool	OpenByFilePointer(void* apFile);
	virtual UInt32	GetSize();
	virtual UInt32	ReadString(BSStringT* arString, UInt32 auiMaxLength);	// 2C
	virtual UInt32	ReadStringAlt(BSStringT* arString, UInt32 auiMaxLength);
	virtual UInt32	GetLine(void* pBuffer, UInt32 uiMaxBytes, UInt8 usMark);
	virtual UInt32	WriteString(BSStringT* arString, bool abBinary);
	virtual UInt32	WriteStringAlt(BSStringT* arString, bool abBinary);
	virtual bool	IsReadable();
	virtual UInt32	DoRead(void* apBuffer, UInt32 auiBytes);
	virtual UInt32	DoWrite(void* apBuffer, UInt32 auiBytes);

	bool bUseAuxBuffer;
	void* m_pAuxBuffer;
	SInt32 iAuxTrueFilePos;
	DWORD dword3C;
	DWORD dword40;
	char pFileName[260];
	UInt32 uiResult;
	UInt32 uiIOSize;
	UInt32 uiTrueFilePos;
	UInt32 uiFileSize;
};

ASSERT_SIZE(BSFile, 0x158);