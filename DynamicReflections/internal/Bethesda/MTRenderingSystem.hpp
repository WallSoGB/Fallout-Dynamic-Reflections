#pragma once
#include "NiCamera.hpp"
#include "BSCompoundFrustum.hpp"
#include "BSShaderAccumulator.hpp"
#include "BSCullingProcess.hpp"
#include "NiTPointerListBase.hpp"

class BSRenderingTaskThread;

class MTRenderManager {
public:

	static MTRenderManager* GetSingleton() {
		return *(MTRenderManager**)0x4EA970;
	}

	static void AddTask(const NiCamera* apCamera, 
		BSCompoundFrustum* apFrustum, NiNode* apNode, 
		void* apGeometryList1, void* apGeometryList2,
		BSShaderAccumulator* apShaderAccum, BSCullingProcess* apCuller, UInt32 aeCullMode);
};