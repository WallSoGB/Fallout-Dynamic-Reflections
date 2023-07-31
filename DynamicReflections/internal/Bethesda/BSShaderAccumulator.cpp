#include "BSShaderAccumulator.hpp"
#include "MemoryManager.hpp"

BSShaderAccumulator* BSShaderAccumulator::Create(BATCHRENDERER_CREATION_MODE aeBatchRendererCreationType, UInt32 batchRendererCount, RenderPassTypes maxPassCount) {
	BSShaderAccumulator* pAccumulator = (BSShaderAccumulator*)NiNew(sizeof(BSShaderAccumulator));
	if (pAccumulator) {
		ThisStdCall(0xB660D0, pAccumulator, aeBatchRendererCreationType, batchRendererCount, maxPassCount);
		return pAccumulator;
	}
	return nullptr;
}