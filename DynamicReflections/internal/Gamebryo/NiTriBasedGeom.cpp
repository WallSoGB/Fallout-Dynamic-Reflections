#include "NiTriBasedGeom.hpp"

NiTriBasedGeomData* NiTriBasedGeom::GetModelData() {
	if (!m_spModelData) {
		return nullptr;
	}
	return (NiTriBasedGeomData*)m_spModelData.m_pObject;
}