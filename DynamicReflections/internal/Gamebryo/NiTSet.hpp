#pragma once
template <class T_Data> class NiTSet {
public:
	NiTSet();
	~NiTSet();

	T_Data* m_pBase;
	UInt32 m_uiAlloced;
	UInt32 m_uiUsed;
};

template <class T_Data> class NiTObjectSet : public NiTSet<T_Data> {};

template <class T_Data> class NiTPrimitiveSet : public NiTSet<T_Data> {};

typedef NiTPrimitiveSet<UInt32> NiUnsignedIntSet;
typedef NiTPrimitiveSet<UInt16> NiUnsignedShortSet;
typedef NiTPrimitiveSet<float> NiFloatSet;