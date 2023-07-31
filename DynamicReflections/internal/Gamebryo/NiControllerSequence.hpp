#pragma once

#include "NiInterpolator.hpp"
#include "NiTimeController.hpp"
#include "NiFixedString.hpp"

class NiTextKeyExtraData;
class NiControllerManager;
class NiStringPalette;
class NiBlendInterpolator;
class NiInterpController;

NiSmartPointer(NiControllerSequence);

class NiControllerSequence : public NiObject {
public:
	NiControllerSequence();
	~NiControllerSequence();

	enum
	{
		kState_Inactive = 0,
		kState_Animating,
		kState_EaseIn,
		kState_EaseOut,
		kState_TransSource,
		kState_TransDest,
		kState_MorphSource
	};

	// 10
	struct InterpArrayItem
	{
		NiInterpolatorPtr m_spInterpolator;
		NiInterpController* m_spInterpCtlr;
		NiBlendInterpolator* m_pkBlendInterp;
		UInt8 m_ucBlendIdx;
	};

	// 10
	struct IDTag
	{
		NiFixedString m_kAVObjectName;
		NiFixedString m_kPropertyType;
		NiFixedString m_kCtlrType;
		NiFixedString m_kCtlrID;
		NiFixedString m_kInterpolatorID;
	};

	NiFixedString m_kName;
	UInt32 m_uiArraySize;
	UInt32 m_uiArrayGrowBy;
	InterpArrayItem* m_pkInterpArray;
	IDTag* m_pkIDTagArray;
	float m_fSeqWeight;
	NiTextKeyExtraData* m_spTextKeys;
	NiTimeController::CycleType m_eCycleType;
	float m_fFrequency;
	float m_fBeginKeyTime;
	float m_fEndKeyTime;
	float m_fLastTime;
	float m_fWeightedLastTime;
	float m_fLastScaledTime;
	NiControllerManager* m_pkOwner;
	UInt32 m_eState;
	float m_fOffset;
	float m_fStartTime;
	float m_fEndTime;
	float m_fDestFrame;
	NiControllerSequence* m_pkPartnerSequence;
	NiFixedString m_kAccumRootName;
	UInt32 unk60[5];
};

ASSERT_SIZE(NiControllerSequence, 0x74);