#pragma once

#include "TESForm.hpp"
#include "TESChildCell.hpp"
#include "NiRefObject.hpp"
#include "BSSimpleArray.hpp"
#include "NiPoint3.hpp"
#include "NiTMap.hpp"

struct NavMeshInfo;
struct ObstacleUndoData;
struct NavMeshTriangleDoorPortal;
struct NavMeshClosedDoorInfo;
struct NavMeshStaticAvoidNode;

struct NavMeshTriangle {
	SInt16 verticesIndex[3];
	SInt16 sides[3];
	UInt32 flags;
};

struct EdgeExtraInfo {
	struct Connection
	{
		NavMeshInfo* navMeshInfo;
		SInt16 triangle;
	};

	UInt32 unk000;
	EdgeExtraInfo::Connection connectTo;
};

class NavMesh : public TESForm {
public:
	TESChildCell childCell;
	NiRefObject refObject;
	TESObjectCELL* parentCell;
	BSSimpleArray<NiPoint3*> vertexArr;
	BSSimpleArray<NavMeshTriangle*> triangleArr;
	BSSimpleArray<EdgeExtraInfo*> edgeInfoArr;
	BSSimpleArray<NavMeshTriangleDoorPortal*> doorPortalArr;
	BSSimpleArray<NavMeshClosedDoorInfo*> closedDorrArr;
	BSSimpleArray<UInt16> unk078Arr;
	NiTMap<UInt32, UInt32> povDataMap;
	BSSimpleArray<UInt16> unk098Arr;
	UInt32 unk0A8;
	float unk0AC[8];
	BSSimpleArray<UInt16>* arrPtr0CC;
	BSSimpleArray<ObstacleUndoData*> obstacleUndoArr;
	NiTMap<UInt32, UInt32>* obstacleDataMap;
	BSSimpleArray<UInt16> unk0E4Arr;
	BSSimpleArray<NavMeshStaticAvoidNode*> avoidNodeArr;
	UInt32* ptr104;
};

ASSERT_SIZE(NavMesh, 0x108);