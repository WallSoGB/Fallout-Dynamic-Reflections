#pragma once

#include "NiObject.hpp"

class NiAVObject;

NiSmartPointer(NiCollisionObject);

class NiCollisionObject : public NiObject {
public:
	NiCollisionObject();
	~NiCollisionObject();

	virtual void		SetSceneGraphObject(NiAVObject* pkSceneObject);
	virtual void		UpdateWorldData();
	virtual void		Unk_25();
	virtual void		Initialize(void* pkData);
	virtual void		Convert(UInt32 uiVersion, void* pkData);
	virtual void		Unk_28();

	NiAVObject* m_pkSceneObject;
};

ASSERT_SIZE(NiCollisionObject, 0xC);