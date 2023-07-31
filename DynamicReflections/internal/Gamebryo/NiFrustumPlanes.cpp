#include "NiFrustumPlanes.hpp"
#include "NiCamera.hpp"

void NiFrustumPlanes::Set(NiFrustum* kFrust, NiTransform* kXform) {
	ThisStdCall(0xA74E10, this, kFrust, kXform);
}

void NiFrustumPlanes::Set(NiCamera* apCamera) {
	Set(&apCamera->m_kViewFrustum, &apCamera->m_kWorld);
}

const NiPlane& NiFrustumPlanes::GetPlane(UInt32 ePlane) const {
	return m_akCullingPlanes[ePlane];
}

bool NiFrustumPlanes::IsPlaneActive(UInt32 ePlane) const {
	return (m_uiActivePlanes & (1 << ePlane)) ? true : false;
}

bool NiFrustumPlanes::IsAnyPlaneActive() const {
	return  m_uiActivePlanes ? true : false;
}

void NiFrustumPlanes::EnablePlane(UInt32 ePlane) {
	m_uiActivePlanes = m_uiActivePlanes | (1 << ePlane);
}

void NiFrustumPlanes::DisablePlane(UInt32 ePlane) {
	m_uiActivePlanes = m_uiActivePlanes & ~(1 << ePlane);
}

void NiFrustumPlanes::SetActivePlaneState(UInt32 uiState) {
	m_uiActivePlanes = uiState;
}
