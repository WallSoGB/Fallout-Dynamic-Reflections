#pragma once

#include "BSMultiBoundShape.hpp"
#include "NiPoint3.hpp"
#include "NiFrustumPlanes.hpp"

NiSmartPointer(BSMultiBoundAABB);

class BSMultiBound;

class BSMultiBoundAABB : public BSMultiBoundShape {
public:
	BSMultiBoundAABB();
	~BSMultiBoundAABB();

	virtual int QType();
	virtual void GetRadius();
	virtual int CheckBSBound(BSMultiBound* aTargetBound);
	virtual int CheckBound(NiBound* aTargetBound);
	virtual bool WithinFrustum(NiFrustumPlanes* pkPlanes);
	virtual bool CompletelyWithinFrustum(NiFrustumPlanes* FrustumPlanes);
	virtual void GetNiBound(NiBound* pBound);
	virtual void Func002A();
	virtual void kSizeOfFormInfo();
	virtual void Func002C();
	virtual bool GetPointWithin(NiPoint3* kpoint);
	virtual void SetCenter(NiPoint3*);

	NiPoint3 Center;
	NiPoint3 HalfExtents;

	CREATE_OBJECT(BSMultiBoundAABB, 0xC381A0);
};

ASSERT_SIZE(BSMultiBoundAABB, 0x24)