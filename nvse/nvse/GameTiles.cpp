#include "nvse/GameTiles.h"
#include "nvse/Utilities.h"
#include "nvse/GameAPI.h"
#include <string>

typedef NiTMapBase <const char *, int>	TraitNameMap;
TraitNameMap	* g_traitNameMap = (TraitNameMap *)0x011F32F4;

const _TraitNameToID TraitNameToID = (_TraitNameToID)0x00A01860;

UInt32 Tile::TraitNameToID(const char * traitName)
{
	return ::TraitNameToID(traitName);
}

__declspec(naked) Tile::Value *Tile::GetValue(UInt32 typeID)
{
	__asm
	{
		push	ebx
		push	esi
		push	edi
		mov		ebx, [ecx+0x14]
		xor		esi, esi
		mov		edi, [ecx+0x18]
		mov		edx, [esp+0x10]
	iterHead:
		cmp		esi, edi
		jz		iterEnd
		lea		ecx, [esi+edi]
		shr		ecx, 1
		mov		eax, [ebx+ecx*4]
		cmp		[eax], edx
		jz		done
		jb		isLT
		mov		edi, ecx
		jmp		iterHead
	isLT:
		lea		esi, [ecx+1]
		jmp		iterHead
	iterEnd:
		xor		eax, eax
	done:
		pop		edi
		pop		esi
		pop		ebx
		retn	4
	}
}

Tile::Value * Tile::GetValueName(const char * valueName)
{
	return GetValue(TraitNameToID(valueName));
}

Tile * Tile::GetChild(const char * childName)
{
	int childIndex = 0;
	char *colon = strchr(const_cast<char*>(childName), ':');
	if (colon)
	{
		if (colon == childName) return NULL;
		*colon = 0;
		childIndex = atoi(colon + 1);
	}
	Tile *result = NULL;
	for(tList<ChildNode>::Iterator iter = childList.Begin(); !iter.End(); ++iter)
	{
		if (*iter && iter->child && ((*childName == '*') || !StrCompare(iter->child->name.pString, childName)) && !childIndex--)
		{
			result = iter->child;
			break;
		}
	}
	if (colon) *colon = ':';
	return result;
}

Tile *Tile::GetChildAlt(const char *childName)
{
	int childIndex = 0;
	char *colon = strchr(const_cast<char*>(childName), ':');
	if (colon)
	{
		if (colon == childName) return NULL;
		*colon = 0;
		childIndex = atoi(colon + 1);
	}
	Tile *result = NULL;
	bool wildcard = *childName == '*';
	for (auto node = ((DList<Tile>*)&childList)->Head(); node; node = node->m_pkNext)
	{
		if (node->m_pkHead && (wildcard || !StrCompare(node->m_pkHead->name.pString, childName)) && !childIndex--)
		{
			result = node->m_pkHead;
			break;
		}
	}
	if (colon) *colon = ':';
	return result;
}

Tile::Value *Tile::GetComponentValueAlt(const char *componentPath)
{
	Tile *parentTile = this;
	char *slashPos;
	while (slashPos = SlashPos(componentPath))
	{
		*slashPos = 0;
		parentTile = parentTile->GetChildAlt(componentPath);
		if (!parentTile) return NULL;
		componentPath = slashPos + 1;
	}
	return *componentPath ? parentTile->GetValueName(componentPath) : NULL;
}

// Find a tile or tile value by component path.
// Returns NULL if component path not found.
// Returns Tile* and clears "trait" if component was a tile.
// Returns Tile* and sets "trait" if component was a tile value.
Tile * Tile::GetComponent(const char * componentPath, const char **trait)
{
	Tile *parentTile = this;
	char *slashPos;
	while (slashPos = SlashPos(componentPath))
	{
		*slashPos = 0;
		parentTile = parentTile->GetChild(componentPath);
		if (!parentTile) return NULL;
		componentPath = slashPos + 1;
	}
	if (*componentPath)
	{
		Tile *result = parentTile->GetChild(componentPath);
		if (result) return result;
		*trait = componentPath;
	}
	return parentTile;
}

Tile::Value * Tile::GetComponentValue(const char * componentPath)
{
	const char *trait = NULL;
	Tile *tile = GetComponent(componentPath, &trait);
	return (tile && trait) ? tile->GetValueName(trait) : NULL;
}

Tile * Tile::GetComponentTile(const char * componentPath)
{
	const char *trait = NULL;
	Tile *tile = GetComponent(componentPath, &trait);
	return (tile && !trait) ? tile : NULL;
}

char *Tile::GetComponentFullName(char *resStr)
{
	if (*(UInt32*)this == 0x106ED44)
		return (char*)memcpy(resStr, name.pString, name.usLen) + name.usLen;
	char *fullName = parent->GetComponentFullName(resStr);
	*fullName++ = '/';
	fullName = (char*)memcpy(fullName, name.pString, name.usLen) + name.usLen;
	DListNode<Tile> *node = ((DList<Tile>*)&parent->childList)->Tail();
	while (node->m_pkHead != this)
		node = node->m_pkPrev;
	int index = 0;
	while ((node = node->m_pkPrev) && !strcmp(name.pString, node->m_pkHead->name.pString))
		index++;
	if (index)
	{
		*fullName++ = ':';
		fullName = IntToStr(fullName, index);
	}
	return fullName;
}

void Tile::Dump(void)
{
	_MESSAGE("%s", name.pString);
	gLog.Indent();

	_MESSAGE("values:");

	gLog.Indent();
	
	for(UInt32 i = 0; i < values.GetSize(); i++)
	{
		Value		* val = values[i];
		const char	* traitName = TraitIDToName(val->id);
		char		traitNameIDBuf[16];

		if(!traitName)
		{
			sprintf_s(traitNameIDBuf, "%08X", val->id);
			traitName = traitNameIDBuf;
		}

		if(val->str)
			_MESSAGE("%s: %s", traitName, val->str);
		else if(val->action)
			_MESSAGE("%s: action %08X", traitName, val->action);
		else
			_MESSAGE("%s: %f", traitName, val->num);
	}

	gLog.Outdent();

	for(tList <ChildNode>::Iterator iter = childList.Begin(); !iter.End(); ++iter)
	{
		ChildNode	* node = iter.Get();
		if(node)
		{
			Tile	* child = node->child;
			if(child)
			{
				child->Dump();
			}
		}
	}

	gLog.Outdent();
}

void Debug_DumpTraits(void)
{
	for(UInt32 i = 0; i < g_traitNameMap->m_uiHashSize; i++)
	{
		for(TraitNameMap::Entry * bucket = g_traitNameMap->m_ppkHashTable[i]; bucket; bucket = bucket->m_pkNext)
		{
			_MESSAGE("%s,%08X,%d", bucket->m_key, bucket->m_val, bucket->m_val);
		}
	}
}

// not a one-way mapping, so we just return the first
// also this is slow and sucks
const char * TraitIDToName(int id)
{
	for(UInt32 i = 0; i < g_traitNameMap->m_uiHashSize; i++)
		for(TraitNameMap::Entry * bucket = g_traitNameMap->m_ppkHashTable[i]; bucket; bucket = bucket->m_pkNext)
			if(bucket->m_val == id)
				return bucket->m_key;

	return NULL;
}

void Debug_DumpTileImages(void) {};


std::string Tile::GetQualifiedName()
{
	std::string qualifiedName;
	//if (parent && !parent->GetFloatValue(kTileValue_class, &parentClass))	// i.e., parent is not a menu
	if (parent)
		qualifiedName = parent->GetQualifiedName() + "\\";

	qualifiedName += name.pString;

	return qualifiedName;
}