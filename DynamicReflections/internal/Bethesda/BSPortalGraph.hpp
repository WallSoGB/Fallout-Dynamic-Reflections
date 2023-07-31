#pragma once

#include "NiTPointerList.hpp"
#include "NiAVObject.hpp"
#include "BSSimpleArray.hpp"
#include "BSOcclusionPlane.hpp"

class NiNode;
class ShadowSceneLight;
class BSMultiBoundRoom;
class BSPortal;

NiSmartPointer(BSPortalGraph);

class BSPortalGraph : public NiRefObject {
public:
	BSPortalGraph();
	~BSPortalGraph();

	NiTPointerList<BSOcclusionPlane*>		kOccludersList;
	NiTPointerList<BSPortal*>				kPortalList;
	NiTPointerList<BSMultiBoundRoom*>		kMultiBoundRoomList;
	NiPointer<NiObject>						unk02C;
	NiTListBase<UInt32>						kMultiBoundRoomAccumList;
	NiTObjectArray<NiPointer<NiAVObject>>	kAlwaysRenderChildren;
	NiPointer<NiNode>						spPortalNodeRoot;
	NiTPointerList<ShadowSceneLight>		kAttachAlwaysRenderQueue;
	NiTPointerList<ShadowSceneLight>		kDetachAlwaysRenderQueue;
	BSSimpleArray<NiPointer<NiNode>>		kUnboundNodes;
};

ASSERT_SIZE(BSPortalGraph, 0x78);