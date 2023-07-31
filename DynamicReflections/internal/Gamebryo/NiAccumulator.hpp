#pragma once

#include "NiCamera.hpp"

class NiGeometry;

NiSmartPointer(NiAccumulator);

class NiAccumulator : public NiObject {
public:
	NiAccumulator();
	~NiAccumulator();
	virtual void StartAccumulating(const NiCamera* pkCamera);

	virtual void FinishAccumulating();
	virtual void RegisterObjectArray(void* kArray);
	virtual void RegisterObject(NiGeometry* apGeometry);
	virtual void Unk_27();
	virtual void Unk_28();

	NiCamera* m_pkCamera;
};

ASSERT_SIZE(NiAccumulator, 0xC);