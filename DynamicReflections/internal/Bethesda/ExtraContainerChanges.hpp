#pragma once

#include "BSExtraData.hpp"
#include "ExtraDataList.hpp"
#include "tList.hpp"
#include "TESForm.hpp"

class TESObjectREFR;

class ExtraContainerChanges : public BSExtraData {
public:
	ExtraContainerChanges();
	virtual ~ExtraContainerChanges();

	class ExtendDataList : public tList<ExtraDataList>
	{
	public:
		SInt32 AddAt(ExtraDataList* item, SInt32 index);
		void RemoveAll() const;
		ExtraDataList* RemoveNth(SInt32 n);
	};

	struct EntryData
	{
		ExtendDataList* extendData;	// 00
		SInt32			countDelta;		// 04
		TESForm* type;			// 08

		void Cleanup();
		static EntryData* Create(UInt32 refID = 0, UInt32 count = 1, ExtraContainerChanges::ExtendDataList* pExtendDataList = NULL);
		static EntryData* Create(TESForm* pForm, UInt32 count = 1, ExtraContainerChanges::ExtendDataList* pExtendDataList = NULL);
		ExtendDataList* Add(ExtraDataList* newList);
		bool Remove(ExtraDataList* toRemove, bool bFree = false);

		bool HasExtraLeveledItem()
		{
			if (!extendData) return false;
			for (auto iter = extendData->Begin(); !iter.End(); ++iter)
				if (iter->HasType(kExtraData_LeveledItem)) return true;
			return false;
		}
	};

	struct EntryDataList : tList<EntryData>
	{
		EntryData* FindForItem(TESForm* item)
		{
			for (auto iter = Begin(); !iter.End(); ++iter)
				if (iter->type == item) return iter.Get();
			return NULL;
		}
	};

	typedef std::vector<EntryData*> DataArray;
	typedef std::vector<ExtendDataList*> ExtendDataArray;

	struct Data
	{
		EntryDataList* objList;	// 000
		TESObjectREFR* owner;	// 004
		float			unk2;		// 008	OnEquip: at the begining, stored into unk3 and forced to -1.0 before checking owner
		float			unk3;		// 00C
		UInt8			byte10;		// 010	referenced in relation to scripts in container
		UInt8			pad[3];

		static Data* Create(TESObjectREFR* owner);
	};

	Data* data;	// 00C

	EntryData* GetByType(TESForm* type);

	void DebugDump();
	void Cleanup();	// clean up unneeded extra data from each EntryData
	ExtendDataList* Add(TESForm* form, ExtraDataList* dataList = NULL);
	bool Remove(TESForm* form, ExtraDataList* dataList = NULL, bool bFree = false);
	ExtraDataList* SetEquipped(TESForm* obj, bool bEquipped, bool bForce = false);

	// get EntryData and ExtendData for all equipped objects, return num objects equipped
	UInt32 GetAllEquipped(DataArray& outEntryData, ExtendDataArray& outExtendData);

	static ExtraContainerChanges* Create();
	static ExtraContainerChanges* Create(TESObjectREFR* thisObj, UInt32 refID = 0, UInt32 count = 1,
		ExtraContainerChanges::ExtendDataList* pExtendDataList = NULL);
	static ExtraContainerChanges* GetForRef(TESObjectREFR* refr);

	// find the equipped item whose form matches the passed matcher
	struct FoundEquipData {
		TESForm* pForm;
		ExtraDataList* pExtraData;
	};
	FoundEquipData FindEquipped(FormMatcher& matcher) const;

	EntryDataList* GetEntryDataList() const {
		return data ? data->objList : NULL;
	}
};

typedef ExtraContainerChanges::DataArray ExtraContainerDataArray;
typedef ExtraContainerChanges::ExtendDataArray ExtraContainerExtendDataArray;
typedef ExtraContainerChanges::FoundEquipData EquipData;

extern ExtraContainerChanges::ExtendDataList* ExtraContainerChangesExtendDataListCreate(ExtraDataList* pExtraDataList = NULL);
extern void ExtraContainerChangesExtendDataListFree(ExtraContainerChanges::ExtendDataList* xData, bool bFreeList = false);
extern bool ExtraContainerChangesExtendDataListAdd(ExtraContainerChanges::ExtendDataList* xData, ExtraDataList* xList);
extern bool ExtraContainerChangesExtendDataListRemove(ExtraContainerChanges::ExtendDataList* xData, ExtraDataList* xList, bool bFreeList = false);

extern void ExtraContainerChangesEntryDataFree(ExtraContainerChanges::EntryData* xData, bool bFreeList = false);

extern ExtraContainerChanges::EntryDataList* ExtraContainerChangesEntryDataListCreate(UInt32 refID = 0, UInt32 count = 1, ExtraContainerChanges::ExtendDataList* pExtendDataList = NULL);
extern void ExtraContainerChangesEntryDataListFree(ExtraContainerChanges::EntryDataList* xData, bool bFreeList = false);

extern void ExtraContainerChangesFree(ExtraContainerChanges* xData, bool bFreeList = false);

#define GetByTypeCast(xDataList, Type) DYNAMIC_CAST(xDataList.GetByType(kExtraData_ ## Type), BSExtraData, Extra ## Type)
extern char* GetExtraDataValue(BSExtraData* traverse);
extern const char* GetExtraDataName(UInt8 ExtraDataType);

SInt32 GetCountForExtraDataList(ExtraDataList* list);

struct InventoryItemData {
	SInt32								count;
	ExtraContainerChanges::EntryData* entry;

	InventoryItemData(SInt32 _count, ExtraContainerChanges::EntryData* _entry) : count(_count), entry(_entry) {}
};

typedef UnorderedMap<TESForm*, InventoryItemData> InventoryItemsMap;

// Finds an ExtraDataList in an ExtendDataList
class ExtraDataListInExtendDataListMatcher {
	ExtraDataList* m_toMatch;
public:
	ExtraDataListInExtendDataListMatcher(ExtraDataList* match) : m_toMatch(match) { }

	bool Accept(ExtraDataList* match)
	{
		return (m_toMatch == match);
	}
};

// Finds an ExtraDataList in an ExtendDataList embedded in one of the EntryData from an EntryDataList
class ExtraDataListInEntryDataListMatcher {
	ExtraDataList* m_toMatch;
public:
	ExtraDataListInEntryDataListMatcher(ExtraDataList* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		if (match && match->extendData)
			return match->extendData->GetIndexOf(ExtraDataListInExtendDataListMatcher(m_toMatch)) >= 0;
		else
			return false;
	}
};

// Finds an ExtendDataList in an EntryDataList
class ExtendDataListInEntryDataListMatcher {
	ExtraContainerChanges::ExtendDataList* m_toMatch;
public:
	ExtendDataListInEntryDataListMatcher(ExtraContainerChanges::ExtendDataList* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		if (match && match->extendData)
			return (match->extendData == m_toMatch);
		else
			return false;
	}
};

// Finds an EntryData in an EntryDataList
class EntryDataInEntryDataListMatcher {
	ExtraContainerChanges::EntryData* m_toMatch;
public:
	EntryDataInEntryDataListMatcher(ExtraContainerChanges::EntryData* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (m_toMatch == match);
	}
};

// Finds an Item (type) in an EntryDataList
class ItemInEntryDataListMatcher {
	TESForm* m_toMatch;
public:
	ItemInEntryDataListMatcher(TESForm* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (match && m_toMatch == match->type);
	}
};

// Finds an Item from its base form in an EntryDataList
class BaseInEntryDataLastMatcher {
	TESForm* m_toMatch;
public:
	BaseInEntryDataLastMatcher(TESForm* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (match && match->type && m_toMatch == match->type->TryGetREFRParent());
	}
};

// Finds an item by refID in an EntryDataList
class RefIDInEntryDataListMatcher {
	UInt32 m_toMatch;
public:
	RefIDInEntryDataListMatcher(UInt32 match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (match && match->type && m_toMatch == match->type->refID);
	}
};

// Finds an item by the refID of its base form in an EntryDataList
class BaseIDInEntryDataListMatcher {
	UInt32 m_toMatch;
public:
	BaseIDInEntryDataListMatcher(UInt32 match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (match && match->type && match->type->TryGetREFRParent() && m_toMatch == match->type->TryGetREFRParent()->refID);
	}
};