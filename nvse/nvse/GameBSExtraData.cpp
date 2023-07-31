#include "GameBSExtraData.h"
#include "GameAPI.h"
#include "GameExtraData.h"

#if RUNTIME
static const UInt32 s_ExtraDataListVtbl							= 0x010143E8;	//	0x0100e3a8;
#endif

bool BaseExtraList::HasType(UInt32 type) const
{
	return (m_presenceBitfield[type >> 3] & (1 << (type & 7))) != 0;
}

void BaseExtraList::MarkType(UInt32 type, bool bCleared)
{
	UInt8 bitMask = 1 << (type & 7);
	UInt8 &flag = m_presenceBitfield[type >> 3];
	if (bCleared) flag &= ~bitMask;
	else flag |= bitMask;
}

ExtraDataList* ExtraDataList::Create(BSExtraData* xBSData)
{
	ExtraDataList* xData = MemoryManager::Allocate<ExtraDataList>();
	memset(xData, 0, sizeof(ExtraDataList));
	((UInt32*)xData)[0] = s_ExtraDataListVtbl;
	if (xBSData)
		xData->Add(xBSData);
	return xData;
}

bool BaseExtraList::IsWorn()
{
	return HasType(kExtraData_Worn);
}