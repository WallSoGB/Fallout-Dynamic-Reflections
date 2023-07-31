#pragma once

#include "DList.hpp"
#include "BSRenderPass.hpp"

class PersistentPassList {
public:
	virtual void Destroy(bool bDoFree);

	DListNode<BSRenderPass>* m_pPass[3];
	UInt32 m_uiCount;
};
