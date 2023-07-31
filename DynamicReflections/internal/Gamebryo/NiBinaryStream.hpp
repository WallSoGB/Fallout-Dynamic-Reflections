#pragma once

class NiBinaryStream;
typedef UInt32(__cdecl* NIBINARYSTREAM_READFN)(NiBinaryStream* pkThis, void* pvBuffer, UInt32 uiBytes, UInt32* puiComponentSizes, UInt32 uiNumComponents);
typedef UInt32(__cdecl* NIBINARYSTREAM_WRITEFN)(NiBinaryStream* pkThis, const void* pvBuffer, UInt32 uiBytes, UInt32* puiComponentSizes, UInt32 uiNumComponents);

class NiBinaryStream {
public:
	NiBinaryStream();
	~NiBinaryStream();

	virtual void Destroy(bool);
	virtual bool Bool();
	virtual void Seek(int);
	virtual UInt32 GetPosition();
	virtual void SetEndianSwap(bool);


	UInt32 m_uiAbsoluteCurrentPos;
	NIBINARYSTREAM_READFN m_pfnRead;
	NIBINARYSTREAM_WRITEFN m_pfnWrite;
};

ASSERT_SIZE(NiBinaryStream, 0x10);