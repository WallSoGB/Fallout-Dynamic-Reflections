#pragma once

#include "NiRefObject.hpp"
#include "NiRTTI.hpp"
#include "NiTArray.hpp"

class bhkBlendCollisionObject;
class bhkCollisionObject;
class bhkLimitedHingeConstraint;
class bhkRigidBody;
class BSFadeNode;
class BSMultiBoundNode;
class BSResizableTriShape;
class BSSegmentedTriShape;
class NiCloningProcess;
class NiGeometryData;
class NiLines;
class NiNode;
class NiParticles;
class NiStream;
class NiTriBasedGeom;
class NiTriShape;
class NiTriStrips;
class NiBound;

NiSmartPointer(NiObject);
NiRTTIAddress(NiObject, 0x11F4418);

class NiObject : public NiRefObject {
public:
	NiObject();
	~NiObject();

	virtual const NiRTTI*				GetRTTI();
	virtual NiNode*						IsNiNode();
	virtual BSFadeNode*					IsFadeNode();
	virtual BSMultiBoundNode*			IsMultiBoundNode();
	virtual NiGeometryData*				IsGeometry();
	virtual NiTriBasedGeom*				IsTriBasedGeometry();
	virtual NiTriStrips*				IsTriStrips();
	virtual NiTriShape*					IsTriShape();
	virtual BSSegmentedTriShape*		IsSegmentedTriShape();
	virtual BSResizableTriShape*		IsResizableTriShape();
	virtual NiParticles*				IsParticlesGeom();
	virtual NiLines*					IsLinesGeom();
	virtual bhkCollisionObject*			IsBhkNiCollisionObject();
	virtual bhkBlendCollisionObject*	IsBhkBlendCollisionObject();
	virtual bhkRigidBody*				IsBhkRigidBody();
	virtual bhkLimitedHingeConstraint*	IsBhkLimitedHingeConstraint();
	virtual NiObject*					CreateClone(NiCloningProcess* kCloning);
	virtual void						LoadBinary(NiStream* kStream);
	virtual void						LinkObject(NiStream* kStream);
	virtual void						RegisterStreamables(NiStream* kStream);
	virtual void						SaveBinary(NiStream* kStream);
	virtual bool						IsEqual(NiObject* pkObject);
	virtual void						GetViewerStrings(NiTArray<char*>* pkStrings);
	virtual void						AddViewerStrings(NiTArray<char*>* pkStrings);
	virtual void						ProcessClone(NiCloningProcess* kCloning);
	virtual void						PostLinkObject(NiStream* kStream);
	virtual bool						StreamCanSkip();
	virtual const NiRTTI*				GetStreamableRTTI();
	virtual void						SetBound(NiBound* pNewBound);
	virtual void						GetBlockAllocationSize();
	virtual UInt32*						GetGroup();
	virtual void						SetGroup(void* pkGroup);
	virtual void						Unk_36();

	NiObject* Clone() { return ThisStdCall<NiObject*>(0xA5D680, this); }

	bool IsExactKindOf(const NiRTTI* pkRTTI) {
		return GetRTTI() == pkRTTI;
	}

	static bool IsExactKindOf(const NiRTTI* pkRTTI, NiObject* pkObject) {
		if (!pkObject)
			return false;
		return pkObject->IsExactKindOf(pkRTTI);
	}
};

ASSERT_SIZE(NiObject, 0x8);