#pragma once

#include "NiExtraData.hpp"
#include "NiObject.hpp"

class NiTimeController;

#if RUNTIME
const UInt32 kNiObjectNET_GetExtraData = 0x006FF9C0;
#endif

class NiObjectNET : public NiObject {
public:
	NiObjectNET();
	~NiObjectNET();

	enum CopyType
	{
		COPY_NONE = 0x0,
		COPY_EXACT = 0x1,
		COPY_UNIQUE = 0x2,
	};

	NiFixedString m_kName;
	NiTimeController* m_spControllers;
	NiExtraData** m_ppkExtra;
	UInt16 m_usExtraDataSize;
	UInt16 m_usMaxSize;

	const char* GetName() const { return m_kName.m_kHandle; };
	void SetName(const char* newName) { m_kName = newName; };

	NiTimeController* GetController(const NiRTTI* apRTTI);

#if RUNTIME
	MEMBER_FN_PREFIX(NiObjectNET);
	DEFINE_MEMBER_FN(GetExtraData, NiExtraData*, kNiObjectNET_GetExtraData, const char* name);
#endif
};

ASSERT_SIZE(NiObjectNET, 0x18);