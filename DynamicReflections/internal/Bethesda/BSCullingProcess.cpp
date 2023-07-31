#include "BSCullingProcess.hpp"
#include "NiMemory.hpp"

BSCullingProcess* BSCullingProcess::Create(BSCullingProcess* apProc, NiVisibleArray* pkVisibleSet) {
	ThisStdCall(0x4A0EB0, apProc, pkVisibleSet);
	return apProc;
}
void BSCullingProcess::SetCullMode(BSCPCullingType aeType) {
	kCullMode = aeType;
}

void BSCullingProcess::PushCullMode(BSCPCullingType aeType) {
	eTypeStack[uiStackIndex++] = kCullMode;
	kCullMode = aeType;
}

void BSCullingProcess::PopCullMode() {
	kCullMode = eTypeStack[--uiStackIndex];
}

void BSCullingProcess::SetAccumulator(BSShaderAccumulator* pkAccumulator) {
	spAccumulator = pkAccumulator;
};