#pragma once

#include "GameTypes.h"
#include "NiTypes.h"
//#include "NiNodes.h"

/*******************************************************
*
* BSTask
*	IOTask
*		QueuedFile
*			QueuedFileEntry
*				QueuedModel
*					QueuedDistantLOD
*					QueuedTreeModel
*				QueuedTexture
*					QueuedTreeBillboard
*				QueuedKF
*					QueuedAnimIdle
*				DistantLODLoaderTask
*				TerrainLODQuadLoadTask
*				SkyTask
*				LipTask
*				GrassLoadTask
*			QueuedReference
*				QueuedTree
*				QueuedActor
*					QueuedCharacter
*						QueuedPlayer
*					QueuedCreature
*			QueuedHead
*			QueuedHelmet
*			QueuedMagicItem
*		AttachDistant3DTask
*		ExteriorCellLoaderTask
*
* NiTArray< NiPointer<QueuedFile> >
*	QueuedChildren
*
*********************************************************/

class TESObjectREFR;
class TESModel;
class QueuedCharacter;
class TESNPC;
class BSFaceGenNiNode;
class BackgroundCloneThread;
class TESAnimGroup;
class BSFaceGenModel;
class QueuedChildren;
class QueuedReference;
class Character;
class AttachDistant3DTask;
class BSTaskManagerThread;

class ModelLoader;

class NiNode;
class NiControllerSequence;
class NiRefObject;
class RefNiObject;

class BSAnimGroupSequence;
struct BSAData;

class RefNiRefObject
{
public:
	NiRefObject*	niRefObject;
	
	//	RefNiRefObject SetNiRefObject(NiRefObject* niRefObject);
};

/*
// 38

// 30
class BSTaskManager : public LockFreeMap< NiPointer< BSTask > >
{
public:
	virtual void Unk_0F(UInt32 arg0) = 0;
	virtual void Unk_10(UInt32 arg0) = 0;
	virtual void Unk_11(UInt32 arg0) = 0;
	virtual void Unk_12(void) = 0;
	virtual void Unk_13(UInt32 arg0) = 0;

	UInt32				unk1C;			// 1C
	UInt32				unk20;			// 20
	UInt32				numThreads;		// 24
	BSTaskManagerThread	** threads;		// 28 array of size numThreads
	UInt32				unk2C;			// 2C
};

// 3C
class IOManager : public BSTaskManager
{
public:
	virtual void Unk_14(UInt32 arg0) = 0;

	static IOManager* GetSingleton();

	UInt32									unk30;			// 30
	LockFreeQueue< NiPointer< IOTask > >	* taskQueue;	// 34
	UInt32									unk38;			// 38

	bool IsInQueue(TESObjectREFR *refr);
	void QueueForDeletion(TESObjectREFR* refr);
	void DumpQueuedTasks();
};

extern IOManager** g_ioManager;
*/

// O4 assumed