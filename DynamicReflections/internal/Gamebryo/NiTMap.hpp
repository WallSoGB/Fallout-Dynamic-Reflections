#pragma once

#include "NiTMapBase.hpp"

template <class T_Key, class T_Data> class NiTMap : public NiTMapBase<T_Key, T_Data> {
public:
	NiTMap();
	~NiTMap();
};