#pragma once

#include "NiTMapBase.hpp"

template <class T_Key, class T_Data> class BSMap : public NiTMapBase<T_Key, T_Data> {
public:
	BSMap();
	~BSMap();
};