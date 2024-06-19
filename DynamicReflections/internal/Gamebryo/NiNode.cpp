#include "NiNode.hpp"

NiAVObject* NiNode::GetAt(UInt32 i) {
	return m_kChildren.GetSize() <= i ? nullptr : m_kChildren.GetAt(i).m_pObject;
}

UInt32 NiNode::GetArrayCount() const {
	return m_kChildren.GetSize();
}

UInt32 NiNode::GetChildCount() const {
	return m_kChildren.GetEffectiveSize();
}