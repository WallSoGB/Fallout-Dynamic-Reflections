#pragma once

#include "NiTListBase.hpp"

template <class T_Data>
class NiTPointerListBase : public NiTListBase <T_Data> {
public:
	~NiTPointerListBase() { ThisStdCall(0x4ED900, this); };

	void AddHead(const T_Data& element) {
		NiTListItem<T_Data>* pkNode = NiTListBase<T_Data>::NewItem();

		pkNode->m_element = element;

		this->AddNodeHead(pkNode);
	}
};