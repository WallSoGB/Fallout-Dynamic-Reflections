#pragma once

#include "NiAVObject.hpp"
#include "NiTArray.hpp"

NiSmartPointer(NiNode);

class NiNode : public NiAVObject {
public:
	NiNode();
	~NiNode();

	virtual void			AttachChild(NiAVObject* pkChild, bool bFirstAvail);
	virtual void			InsertChildAt(UInt32 i, NiAVObject* pkChild);
	virtual void			DetachChild(NiAVObject* pkChild, NiAVObjectPtr* aspAVObject);
	virtual void			DetachChild(NiAVObject* pkChild);
	virtual void			DetachChildAt(UInt32 i, NiAVObjectPtr* aspAVObject);
	virtual NiAVObject*		DetachChildAt(UInt32 i);
	virtual void			SetAt(UInt32 i, NiAVObject* pkChild, NiAVObjectPtr* aspAVObject);
	virtual void			SetAt(UInt32 i, NiAVObject* pkChild);
	virtual void			UpdateUpwardPass();

	NiTObjectArray<NiAVObjectPtr> m_kChildren;

	CREATE_OBJECT(NiNode, 0xA5F030);

	NiAVObject* GetAt(UInt32 i);
	UInt32 GetArrayCount() const;
	UInt32 GetChildCount() const;
};

ASSERT_SIZE(NiNode, 0xAC);