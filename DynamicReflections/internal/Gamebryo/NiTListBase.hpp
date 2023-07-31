#pragma once

#include "NiMemObject.hpp"

typedef void* NiTListIterator;

template <class T_Data>
class NiTListItem : public NiMemObject {
public:
	NiTListItem* m_pkNext;
	NiTListItem* m_pkPrev;
	T_Data m_element;
};

template <class T_Data>
class NiTListBase : public NiMemObject {
public:
	NiTListBase() : m_pkHead(0), m_pkTail(0), m_uiCount(0) { };
	~NiTListBase() {};

	NiTListItem<T_Data>* m_pkHead;              // points to head of list
	NiTListItem<T_Data>* m_pkTail;              // points to tail of list
	UInt32	m_uiCount;	// 00C


	__forceinline NiTListItem<T_Data>* GetHeadPos() const { return m_pkHead; }
	__forceinline NiTListItem<T_Data>* GetTailPos() const { return m_pkTail; }
	__forceinline NiTListItem<T_Data>* GetNextPos(NiTListIterator kPos) const { return kPos ? ((NiTListItem<T_Data>*) kPos)->m_pkNext : 0; }
	__forceinline NiTListItem<T_Data>* GetPrevPos(NiTListIterator kPos) const { return kPos ? ((NiTListItem<T_Data>*) kPos)->m_pkPrev : 0; }
	__forceinline T_Data& Get(NiTListIterator kPos) const { return ((NiTListItem<T_Data>*) kPos)->m_element; }
	__forceinline bool IsEmpty() const { return m_uiCount ? false : true; }

	void Deallocate(NiTListItem<T_Data>* apItem) { ThisStdCall(0x45CEE0, this, apItem); }

	void DeleteItem(NiTListItem<T_Data>* apItem) {
		apItem->m_element = nullptr;
		Deallocate(apItem);
	}

	void RemoveAll() {
		NiTListItem<T_Data>* pkCurr = m_pkHead;
		while (pkCurr) {
			NiTListItem<T_Data>* pkDel = pkCurr;
			pkCurr = pkCurr->m_pkNext;
			DeleteItem(pkDel);
		}

		m_uiCount = 0;
		m_pkHead = nullptr;
		m_pkTail = nullptr;
	}

	static __forceinline NiTListItem<T_Data>* NewItem() { return CdeclCall<NiTListItem<T_Data>*>(0x43A010); }

	__forceinline const T_Data& GetNext(NiTListIterator& kPos)
	{
		const T_Data& element = static_cast<NiTListItem<T_Data>*>(kPos)->m_element;

		kPos = static_cast<NiTListItem<T_Data>*>(kPos)->m_pkNext;
		return element;
	}

	__forceinline void AddNodeHead(NiTListItem<T_Data>* pkNode) { 
		pkNode->m_pkPrev = 0;
		pkNode->m_pkNext = m_pkHead;

		if (m_pkHead)
			m_pkHead->m_pkPrev = pkNode;
		else
			m_pkTail = pkNode;

		m_pkHead = pkNode;
		m_uiCount++;
	};
};