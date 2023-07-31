#include "GameData.h"

#if RUNTIME
DataHandler* DataHandler::Get()
{
	DataHandler** g_dataHandler = (DataHandler**)0x011C3F2C;
	return *g_dataHandler;
}
#else

DataHandler* DataHandler::Get()
{
	DataHandler** g_dataHandler = (DataHandler**)0xED3B0C;
	return *g_dataHandler;
}

#endif

class LoadedModFinder
{
	const char * m_stringToFind;

public:
	LoadedModFinder(const char * str) : m_stringToFind(str) { }

	bool Accept(TESFile* modInfo)
	{
		return !StrCompare(modInfo->m_Filename, m_stringToFind);
	}
};

const TESFile * DataHandler::LookupModByName(const char * modName)
{
	return modList.modInfoList.Find(LoadedModFinder(modName));
}

const TESFile ** DataHandler::GetActiveModList()
{
	static const TESFile* activeModList[0x100] = { 0 };

	if (!(*activeModList))
	{
		UInt16 index = 0;
		for (index = 0  ; index < DataHandler::Get()->modList.modInfoList.Count() ; index++)
		{
			TESFile* entry = DataHandler::Get()->modList.modInfoList.GetNthItem(index);
			if (entry->IsLoaded())
				activeModList[index] = entry;
		}
	}

	return activeModList;
}

UInt8 DataHandler::GetModIndex(const char* modName)
{
	return modList.modInfoList.GetIndexOf(LoadedModFinder(modName));
}

const char* DataHandler::GetNthModName(UInt32 modIndex)
{
	const TESFile** activeModList = GetActiveModList();
	if (modIndex < GetActiveModCount() && activeModList[modIndex])
		return activeModList[modIndex]->m_Filename;
	else
		return "";
}

void DataHandler::DisableAssignFormIDs(bool shouldAsssign)
{
	ThisStdCall(0x464D30, this, shouldAsssign);
}

struct IsModLoaded
{
	bool Accept(TESFile* pModInfo) const {
		return pModInfo->IsLoaded();
	}
};

UInt8 DataHandler::GetActiveModCount() const
{
	UInt32 count = modList.modInfoList.CountIf(IsModLoaded());
	return count;
}