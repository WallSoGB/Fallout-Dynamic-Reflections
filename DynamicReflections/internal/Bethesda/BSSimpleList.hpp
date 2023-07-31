#pragma once

#include "MemoryManager.hpp"

template <class T_Data>
class BSSimpleList {
public:
	BSSimpleList() : m_item(0), m_pkNext(0) { }
	~BSSimpleList() { 
		while (m_pkNext) {
			auto v2 = m_pkNext->m_pkNext;
			m_pkNext->m_pkNext = nullptr;
			if (m_pkNext)
				m_pkNext->Destroy(true);
			m_pkNext = v2;
		}
		m_item = 0;
	}

	T_Data m_item;
	BSSimpleList<T_Data>* m_pkNext;

	void Destroy(bool bFree) {
		this->~BSSimpleList();
		if (bFree)
			MemoryManager::Deallocate(this);
	}

	__forceinline T_Data GetItem() const { return m_item; }

	__forceinline BSSimpleList<T_Data>* GetNext() const { return m_pkNext; }

	bool IsEmpty() { return !m_pkNext && !m_item; }

	__forceinline void IsInList(T_Data** item) {
		BSSimpleList<T_Data>* iter = this;
		while (iter && m_item != *item)
			iter = iter->GetNext();
		return iter != 0;
	}

	__forceinline UInt32 ItemsInList() {
		UInt32 uiCount = 0;
		BSSimpleList<T_Data>* iter = this;
		while (iter) {
			if (iter->m_item)
				++uiCount;

			iter = iter->GetNext();
		}
		return uiCount;
	}

};

ASSERT_SIZE(BSSimpleList<UInt32>, 0x8);