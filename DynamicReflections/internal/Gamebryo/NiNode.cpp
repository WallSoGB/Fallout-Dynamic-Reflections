#include "NiNode.hpp"

NiAVObject* NiNode::GetAt(UInt32 i) {
	return m_kChildren.GetSize() <= i ? nullptr : m_kChildren.GetAt(i).m_pObject;
}