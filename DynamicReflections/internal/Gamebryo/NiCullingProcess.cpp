#include "NiCullingProcess.hpp"

NiCullingProcess* NiCullingProcess::Create(NiCullingProcess* apThis, NiVisibleArray* pkVisibleSet) {
	ThisStdCall<NiCullingProcess*>(0xA69400, apThis, pkVisibleSet);
	return apThis;
}

void NiCullingProcess::SetCamera(const NiCamera* apCamera) {
	m_pkCamera = (NiCamera*)apCamera;
}

// 0xA694A0
void NiCullingProcess::SetFrustum(const NiFrustum* kFrustum) {
	if (m_pkCamera) {
		m_kFrustum = *kFrustum;
		m_kPlanes.Set(&m_kFrustum, &m_pkCamera->m_kWorld);
		m_kPlanes.m_uiActivePlanes = 63;
	}
};