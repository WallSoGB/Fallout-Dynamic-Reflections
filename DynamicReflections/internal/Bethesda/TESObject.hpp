#pragma once

#include "TESForm.hpp"

class NiNode;
class TESObjectREFR;
class TESBoundObject;
class TESWaterForm;

class TESObject : public TESForm {
public:
	TESObject();
	~TESObject();

	virtual UInt32			Unk_4E();
	virtual bool			Unk_4F();
	virtual TESWaterForm*	GetWaterType();
	virtual bool			Unk_51();
	virtual void			Unk_52(void* arg);
	virtual NiNode*			Clone3D(TESObjectREFR* apRequester, bool aDeepCopy);
	virtual void			UnClone3D(TESObjectREFR* apRequester);
	virtual bool			IsMarker();
	virtual bool			IsOcclusionMarker();
	virtual void			Unk_57();
	virtual bool			ReplaceModel();
	virtual bool			Unk_59(void* arg);
	virtual void			Unk_5A(void* arg0, void* arg1);
	virtual UInt32			Unk_5B();
	virtual UInt32			Unk_5C();
	virtual NiNode*			LoadGraphics(TESObjectREFR* apRef);

	struct BoundObjectListHead
	{
		UInt32 boundObjectCount;
		TESBoundObject* first;
		TESBoundObject* last;
		UInt32 unkC;
	};

	BoundObjectListHead* head;		// 018
	TESBoundObject* prev;		// 01C
	TESBoundObject* next;		// 020
};

ASSERT_SIZE(TESObject, 0x24)