#pragma once

#include "NiMemObject.hpp"
#include "NiMemory.hpp"
#include "MemoryManager.hpp"

template <class T_Data> 
class NiTArray : public NiMemObject {
public:
	NiTArray(UInt32 uiMaxSize = 0, UInt32 uiGrowBy = 1) {
		m_usMaxSize = (UInt16)uiMaxSize;
		m_usGrowBy = (UInt16)uiGrowBy;
		m_usSize = 0;
		m_usESize = 0;

		if (m_usMaxSize > 0)
			m_pBase = (T_Data*)NiAlloc(4 * m_usMaxSize);
		else
			m_pBase = 0;
	}

	~NiTArray(void) {
		NiFree(m_pBase);
	};

	virtual void Destroy(bool doFree) {
		this->~NiTArray();
		if (doFree)
			MemoryManager::Deallocate(this);
	};

	T_Data* m_pBase;					 // pointer to the array storage
	UInt16 m_usMaxSize;  // number of slots in array
	UInt16 m_usSize;     // first available empty slot in array
	UInt16 m_usESize;    // number of filled slots
	UInt16 m_usGrowBy;   // number of slots to grow array when full

	T_Data operator[](UInt32 idx) {
		if (idx < m_usSize)
			return m_pBase[idx];
		return NULL;
	}

	T_Data Get(UInt32 idx) { return (*this)[idx]; }

	inline UInt16 GetEffectiveSize() const { return m_usESize; }
	inline UInt16 GetSize() const { return m_usSize; }

	void SetSize(UInt32 uiMaxSize) {
		if (uiMaxSize == m_usMaxSize)
			return;

		UInt16 i;
		if (uiMaxSize < m_usSize) {
			for (i = (UInt16)uiMaxSize; i < m_usSize; i++) {
				if (m_pBase[i] != T_Data(0)) {
					m_pBase[i] = T_Data(0);
					m_usESize--;
				}
			}
			m_usSize = uiMaxSize;
		}

		T_Data* pSaveBase = m_pBase;
		m_usMaxSize = uiMaxSize;
		if (uiMaxSize > 0) {
			m_pBase = (T_Data*)MemoryManager::Allocate(uiMaxSize >> 30 != 0 ? -1 : 4 * uiMaxSize);
			for (i = 0; i < m_usSize; i++) {
				m_pBase[i] = pSaveBase[i];
			}
			for (i = m_usSize; i < m_usMaxSize; i++) {
				m_pBase[i] = T_Data(0);
			}
		}
		else {
			m_pBase = 0;
		}
		MemoryManager::Deallocate(pSaveBase);
	}

	void SetAt(UInt32 uiIndex, const T_Data& element) {
		if (uiIndex >= m_usSize) {
			m_usSize = uiIndex + 1;
			if (element != T_Data(0))
				m_usESize++;
		}
		else {
			if (element != T_Data(0)) {
				if (m_pBase[uiIndex] == T_Data(0))
					m_usESize++;
			}
			else if (m_pBase[uiIndex] != T_Data(0))
					m_usESize--;
		}

		m_pBase[uiIndex] = element;
	}

	UInt32 SetAtGrow(UInt32 uiIndex, const T_Data& element) {
		if (uiIndex >= m_usMaxSize) {
			SetSize(uiIndex + m_usGrowBy);
		}

		SetAt(uiIndex, element);
		return uiIndex;
	}

	UInt32 Add(const T_Data& element) {
		return SetAtGrow(m_usSize, element);
	}

	UInt32 AddFirstEmpty(const T_Data& element) {
		if (element == T_Data(0))
			return 0xffffffff;

		for (UInt16 i = 0; i < m_usSize; i++) {
			if (m_pBase[i] == T_Data(0)) {
				// empty slot - add here
				m_pBase[i] = element;
				m_usESize++;
				return i;
			}
		}

		// no empty slots - add at end
		return SetAtGrow(m_usSize, element);
	}

	T_Data RemoveAt(UInt32 uiIndex) {
		if (uiIndex >= m_usSize)
			return T_Data(0);

		T_Data element = m_pBase[uiIndex];
		m_pBase[uiIndex] = T_Data(0);

		if (element != T_Data(0))
			m_usESize--;

		if (uiIndex == (UInt16)(m_usSize - 1))
			m_usSize--;

		return element;
	}

	T_Data& GetAt(UInt32 uiIndex) {
		return m_pBase[uiIndex];
	}

	T_Data RemoveAtAndFill(UInt32 uiIndex)
	{
		if (uiIndex >= m_usSize)
			return T_Data(0);

		m_usSize--;
		T_Data element = m_pBase[uiIndex];

		m_pBase[uiIndex] = m_pBase[m_usSize];
		m_pBase[m_usSize] = T_Data(0);

		if (element != T_Data(0))
			m_usESize--;

		return element;
	}

	T_Data RemoveEnd() {
		if (m_usSize == 0)
			return T_Data(0);

		m_usSize--;
		T_Data element = m_pBase[m_usSize];
		m_pBase[m_usSize] = T_Data(0);

		if (element != T_Data(0))
			m_usESize--;

		return element;
	}

	void RemoveAll() {
		for (UInt16 i = 0; i < m_usSize; i++)
			m_pBase[i] = T_Data(0);

		m_usSize = 0;
		m_usESize = 0;
	}

	UInt32 Remove(const T_Data& element) {
		if (element != T_Data(0)) {
			for (UInt16 i = 0; i < m_usSize; i++) {
				if (m_pBase[i] == element) {
					m_pBase[i] = T_Data(0);

					m_usESize--;
					if (i == m_usSize - 1)
						m_usSize--;

					return i;
				}
			}
		}

		return (UInt32)~0;
	}

	void Compact() {
		if (m_usESize == m_usSize)
			return;

		// move elements to contiguous memory at beginning of array
		if (m_usESize) {
			for (UInt16 i = 0, j = 0; i < m_usSize; i++) {
				if (m_pBase[i] != T_Data(0)) {
					if (m_pBase[j] != m_pBase[i])
						m_pBase[j] = m_pBase[i];
					j++;
				}
			}
		}

		// downsize storage
		T_Data* pSaveBase = m_pBase;
		m_usSize = m_usESize;
		m_usMaxSize = m_usSize;
		if (m_usMaxSize > 0) {
			m_pBase = NiAlloc(4* m_usMaxSize);

			// copy old array to new array
			for (unsigned short i = 0; i < m_usSize; i++)
				m_pBase[i] = pSaveBase[i];
		}
		else
			m_pBase = 0;

		// delete old array
		NiFree(pSaveBase);
	}
};

template <class T_Data> 
class NiTObjectArray : public NiTArray<T_Data> {
};

template <class T_Data> 
class NiTPrimitiveArray : public NiTArray<T_Data> {
};