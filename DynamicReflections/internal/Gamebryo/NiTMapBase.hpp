#pragma once

#include "NiMemObject.hpp"

#if RUNTIME

const UInt32 _NiTMap_Lookup = 0x00853130;

#endif

typedef void* NiTMapIterator;

template <class T_Key, class T_Data> class NiTMapItem {
public:
	NiTMapItem* m_pkNext;	// 000
	T_Key	m_key;	// 004
	T_Data	m_val;	// 008
};

template <class T_Key, class T_Data> class NiTMapBase : public NiMemObject {
public:
	typedef NiTMapItem<T_Key, T_Data> Entry;

	NiTMapBase(UInt32 uiHashSize = 37) {};
	~NiTMapBase() {};

	virtual void						Destroy(bool doFree);								// 000
	virtual UInt32						KeyToHashIndex(T_Key key);								// 001
	virtual bool						IsKeysEqual(T_Key key1, T_Key key2);					// 002
	virtual void						SetValue(NiTMapItem<T_Key, T_Data>* pkItem, T_Key key, T_Data data);	// 003
	virtual	void						ClearValue(NiTMapItem<T_Key, T_Data>* pkItem);							// 004
	virtual	NiTMapItem<T_Key, T_Data>*  NewItem(void);															// 005
	virtual	void						DeleteItem(NiTMapItem<T_Key, T_Data>* pkItem);							// 006

	UInt32 m_uiHashSize;
	NiTMapItem<T_Key, T_Data>** m_ppkHashTable;
	UInt32 m_uiCount;

	__forceinline bool GetAt(T_Key key, T_Data& dataOut) {
		UInt32 hashIndex = KeyToHashIndex(key);
		NiTMapItem<T_Key, T_Data>* item = m_ppkHashTable[hashIndex];
		while (item)
		{
			if (IsKeysEqual(item->m_key, key))
			{
				dataOut = item->m_val;
				return true;
			}
			item = item->m_pkNext;
		}
		return false;
	}

	__forceinline void SetAt(T_Key key, T_Data data) {
		UInt32 hashIndex = KeyToHashIndex(key);
		NiTMapItem<T_Key, T_Data>* item = m_ppkHashTable[hashIndex];
		while (item)
		{
			if (IsKeysEqual(item->m_key, key))
			{
				item->m_val = data;
				return;
			}
			item = item->m_pkNext;
		}
		NiTMapItem<T_Key, T_Data>* nuEntry = NewItem();
		SetValue(nuEntry, key, data);
		nuEntry->m_pkNext = m_ppkHashTable[hashIndex];
		m_ppkHashTable[hashIndex] = nuEntry;
		m_uiCount++;
	}

	__forceinline T_Data* Lookup(T_Key key) {
		T_Data* dataOut = nullptr;
		GetAt(key, *dataOut);
		return dataOut;
	}

	__forceinline bool Insert(NiTMapItem<T_Key, T_Data>* nuEntry)
	{
		// game code does not appear to care about ordering of entries in buckets
		UInt32 bucket = nuEntry->m_key % m_uiHashSize;
		NiTMapItem<T_Key, T_Data>* prev = NULL;
		for (NiTMapItem<T_Key, T_Data>* cur = m_ppkHashTable[bucket]; cur; cur = cur->m_pkNext) {
			if (cur->m_key == nuEntry->m_key) {
				return false;
			}
			else if (!cur->m_pkNext) {
				prev = cur;
				break;
			}
		}

		if (prev) {
			prev->m_pkNext = nuEntry;
		}
		else {
			m_ppkHashTable[bucket] = nuEntry;
		}

		m_uiHashSize++;
		return true;
	}

	__forceinline void RemoveAll()
	{
		for (UInt32 i = 0; i < m_uiHashSize; i++)
		{
			while (m_ppkHashTable[i])
			{
				NiTMapItem<T_Key, T_Data>* item = m_ppkHashTable[i];
				m_ppkHashTable[i] = m_ppkHashTable[i]->m_pkNext;
				ClearValue(item);
				DeleteItem(item);
			}
		}

		m_uiCount = 0;
	}

	__forceinline NiTMapIterator GetFirstPos() const
	{
		for (UInt32 i = 0; i < m_uiHashSize; i++)
		{
			if (m_ppkHashTable[i])
				return m_ppkHashTable[i];
		}
		return 0;
	}

	__forceinline void GetNext(NiTMapIterator& pos, T_Key& key, T_Data& val)
	{
		NiTMapItem<T_Key, T_Data>* item = (NiTMapItem<T_Key, T_Data>*) pos;

		key = item->m_key;
		val = item->m_val;

		if (item->m_pkNext)
		{
			pos = item->m_pkNext;
			return;
		}

		UInt32 i = KeyToHashIndex(item->m_key);
		for (++i; i < m_uiHashSize; i++)
		{
			item = m_ppkHashTable[i];
			if (item)
			{
				pos = item;
				return;
			}
		}

		pos = 0;
	}

	//#if RUNTIME
	//	//DEFINE_MEMBER_FN_LONG(NiTMapBase, Lookup, bool, _NiTMap_Lookup, T_Key key, T_Data* dataOut);
	//#endif
};