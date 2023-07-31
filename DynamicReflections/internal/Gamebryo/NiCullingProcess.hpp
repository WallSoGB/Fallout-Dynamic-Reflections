#pragma once

#include "NiRTTI.hpp"
#include "NiAVObject.hpp"
#include "NiGeometry.hpp"
#include "NiCamera.hpp"
#include "NiVisibleArray.hpp"
#include "NiFrustumPlanes.hpp"

NiSmartPointer(NiCullingProcess);

class NiCullingProcess {
public:
	NiCullingProcess() {};
	~NiCullingProcess() { ThisStdCall(0xA693E0, this); };

	virtual NiRTTI* GetRTTI();
	virtual void Unk_01();
	virtual void Unk_02();
	virtual void Unk_03();
	virtual void Unk_04();
	virtual void Unk_05();
	virtual void Unk_06();
	virtual void Unk_07();
	virtual void Unk_08();
	virtual void Unk_09();
	virtual void Unk_0A();
	virtual void Unk_0B();
	virtual void Unk_0C();
	virtual void Unk_0D();
	virtual void Unk_0E();
	virtual void Unk_0F();
	virtual void Destroy(bool);
	virtual void Process(NiAVObject* pkObject);
	virtual void ProcessAlt(const NiCamera* pkCamera, NiAVObject* pkScene, NiVisibleArray* pkVisibleSet);
	virtual void AppendVirtual(NiGeometry*);

	bool m_bUseVirtualAppend;
	NiVisibleArray* m_pkVisibleSet;
	NiCamera* m_pkCamera;
	NiFrustum m_kFrustum;
	NiFrustumPlanes m_kPlanes;

	static NiCullingProcess* Create(NiCullingProcess* apThis, NiVisibleArray* pkVisibleSet = 0);

	void SetCamera(const NiCamera* apCamera);
	void SetFrustum(const NiFrustum* kFrustum);

	void DoCulling(NiAVObject* pkObject);
};

ASSERT_SIZE(NiCullingProcess, 0x90);