#pragma once

#include "TESForm.hpp"

class BGSListForm : public TESForm {
public:
	BGSListForm();
	~BGSListForm();

	tList<TESForm> list;			// 018

	UInt32	numAddedObjects;	// number of objects added via script - assumed to be at the start of the list

	UInt32 Count() const {
		return list.Count();
	}

	TESForm* GetNthForm(SInt32 n) const {
		return list.GetNthItem(n);
	}

	SInt32 AddAt(TESForm* pForm, SInt32 n, bool const checkDupes = false) {
		if (checkDupes) {
			if (GetIndexOf(pForm) != eListInvalid)
				return eListInvalid;
		}
		auto const result = list.AddAt(pForm, n);
		if (result >= 0 && IsAddedObject(n))
			numAddedObjects++;

		return result;
	}

	SInt32 GetIndexOf(TESForm* pForm);

	TESForm* RemoveNthForm(SInt32 n) {
		TESForm* form = list.RemoveNth(n);

		if (form && IsAddedObject(n))
		{
			if (numAddedObjects == 0)
			{
				_MESSAGE("BGSListForm::RemoveNthForm: numAddedObjects = 0");
			}
			else
			{
				numAddedObjects--;
			}
		}

		return form;
	}

	TESForm* ReplaceNthForm(SInt32 n, TESForm* pReplaceWith) {
		return list.ReplaceNth(n, pReplaceWith);
	}

	SInt32 RemoveForm(TESForm* pForm);
	SInt32 ReplaceForm(TESForm* pForm, TESForm* pReplaceWith);

	bool IsAddedObject(SInt32 idx)
	{
		return (idx >= 0) && (idx < numAddedObjects);
	}

#if RUNTIME
	[[nodiscard]] static game_unique_ptr<BGSListForm> MakeUnique();
#endif
};

ASSERT_SIZE(BGSListForm, 0x024);