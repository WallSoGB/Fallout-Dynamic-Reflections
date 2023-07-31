#pragma once

#include "NiObject.hpp"
#include "NiUpdateData.hpp"

class NiNode;
class NiObjectNET;

class NiTimeController : public NiObject {
public:

	virtual void Unk_23(void);
	virtual void Unk_24(void);
	virtual void Update(NiUpdateData* apUpdateData);
	virtual void SetTarget(NiNode*);
	virtual void Unk_27(void);
	virtual bool IsVertexController();
	virtual float ComputeScaledTime(float fTime);
	virtual void OnPreDisplay(void);
	virtual void GetNext(void);
	virtual void Unk_2C(void);

	enum AnimType
	{
		APP_TIME,
		APP_INIT
	};

	enum CycleType
	{
		LOOP,
		REVERSE,
		CLAMP,

		MAX_CYCLE_TYPES
	};

	UInt16 m_usflags;
	float m_fFrequency;
	float m_fPhase;
	float m_fLoKeyTime;
	float m_fHiKeyTime;
	float m_fStartTime;
	float m_fLastTime;
	float m_fWeightedLastTime;
	float m_fScaledTime;
	NiObjectNET* m_pkTarget;
	NiTimeController* m_spNext;
};