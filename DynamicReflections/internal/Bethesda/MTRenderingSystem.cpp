#include "MTRenderingSystem.hpp"
#include "BSCullingProcess.hpp"
#include "BSShaderUtil.hpp"

void MTRenderManager::AddTask(const NiCamera* apCamera, BSCompoundFrustum* apFrustum, NiNode* apNode, void* apGeometryList1, void* apGeometryList2, BSShaderAccumulator* apShaderAccum, BSCullingProcess* apCuller, UInt32 aeCullMode) {
	bool bDestroy = false;
	if (!apCuller) {
		STACK_ALLOCATE(BSCullingProcess, CullingProc);
		apCuller = BSCullingProcess::Create(pCullingProc, 0);
		apCuller->m_pkCamera = (NiCamera*)apCamera;
		if (apFrustum)
			apCuller->pCompoundFrustum = apFrustum;
		else
			apCuller->SetFrustum(&apCamera->m_kViewFrustum);
		apCuller->kCullMode = (BSCullingProcess::BSCPCullingType)aeCullMode;
		bDestroy = true;
	}

	if (!apCuller->spAccumulator.m_pObject) {
		if (apShaderAccum) {
			apCuller->spAccumulator.m_pObject = apShaderAccum;
			apShaderAccum->IncRefCount();
		}
		else {
			apCuller->spAccumulator = BSShaderAccumulator::Create(BSShaderAccumulator::BRCM_NORMAL, 1, BSSM_FINAL_PASS);
		}
	}
	if (apNode) {
		BSShaderUtil::AccumulateGeometry(apCamera, apNode, apCuller);
	}

	if (apGeometryList1) {
		BSShaderUtil::AccumulateGeometryList(apCamera, apGeometryList1, apCuller);
	}

	if (apGeometryList2) {
		BSShaderUtil::AccumulateGeometryList(apCamera, apGeometryList2, apCuller);
	}

	if (bDestroy) {
		apCuller->Destroy(false);
	}
}