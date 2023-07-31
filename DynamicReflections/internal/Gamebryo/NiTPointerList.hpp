#pragma once

#include "NiTPointerListBase.hpp"

template <class T_Data>
class NiTPointerList : public NiTPointerListBase <T_Data> {
public:
	NiTPointerList();
	~NiTPointerList();
};

ASSERT_SIZE(NiTPointerList<void*>, 0xC);