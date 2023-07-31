#pragma once

#include "IMemoryHeap.hpp"
#include "ScrapHeap.hpp"
#include "NiTMap.hpp"

class BSExtraData;
struct ExtraDataList;
class NiNode;
class ScriptLocals;
class TESObjectREFR;

enum Context
{
	MC_WINDOW = 0x4,
	MC_THREAD_SAFE_STRUCT = 0x6,
	MC_EFFECTS = 0x7,
	MC_STRING = 0x8,
	MC_SETTINGS = 0x9,
	MC_SYSTEM = 0xA,
	MC_AUDIO = 0xB,
	MC_MENU = 0xD,
	MC_LOCAL_MAP = 0xE,
	MC_RENDER_15 = 0xF,
	MC_HAVOK = 0x10,
	MC_SAVE_LOAD = 0x11,
	MC_ARCHIVE_MANAGER = 0x13,
	MC_MOVIE_PLAYER = 0x14,
	MC_SCRIPT = 0x15,
	MC_UNK_22 = 0x16,
	MC_FILE_BUFFER = 0x17,
	MC_FILE_CACHE = 0x18,
	MC_SCENEGRAPH = 0x19,
	MC_CELL = 0x1A,
	MC_TERRAIN_LAND = 0x1B,
	MC_TERRAIN_LOD = 0x1C,
	MC_WATER = 0x1D,
	MC_TREES_0 = 0x1E,
	MC_TREES_1 = 0x1F,
	MC_GRIDCELL = 0x20,
	MC_SKY = 0x21,
	MC_TERRAIN_NODE = 0x22,
	MC_TERRAIN_35 = 0x23,
	MC_TERRAIN_36 = 0x24,
	MC_TERRAIN_37 = 0x25,
	MC_RENDER_38 = 0x26,
	MC_IMAGESPACE = 0x27,
	MC_PROCESS_MANAGER = 0x2A,
	MC_COMBAT_SYSTEM = 0x2B,
	MC_LOADED_REF_COLLECTION = 0x2C,
	MC_ACTOR_0 = 0x2D,
	MC_NAVMESH = 0x2E,
	MC_DATAHANDLER = 0x2F,
	MC_FILE_COMPRESSED = 0x30,
	MC_REF = 0x31,
	MC_ACTOR_1 = 0x32,
	MC_ANIMATION = 0x33,
	MC_PLAYER = 0x34,
	MC_UNK_53 = 0x35,
	MC_INVENTORY = 0x36,
	MC_FACEGEN_0 = 0x37,
	MC_FACEGEN_1 = 0x38,
	MC_FACEGEN_2 = 0x39,
};

// Stolen from JIP
struct TLSData {

	UInt32			unk000;				// 000
	UInt32			unk004;				// 004
	ExtraDataList*	pLastXtraList;		// 008
	UInt32			unk00C;				// 00C
	BSExtraData*	xDatas[0x93];	// 010
	bool			byte25C;			// 25C
	bool			byte25D;			// 25C
	NiNode*			pLastNiNode;		// 260
	TESObjectREFR*  pLastNiNodeREFR;	// 264
	bool			bConsoleMode;		// 268
	UInt32			unk26C[4];			// 26C
	TESForm*		pLastRefVar;		// 27C
	SInt32			iLastVarIndex;		// 280
	ScriptLocals*	pLastEventList;		// 284
	Script*			pLastScript;		// 288
	UInt32			activateRecursionDepth;	// 28C
	UInt32			unk290;				// 290
	UInt32			uiFlags;			// 294
	bool			bUnk298;
	UInt32			unk29C[6];
	UInt32			uiHeapIndex;			// 2B4
	UInt32			unk2B8;				// 2B8
	UInt32			uiAccumulatorCount;				// 2BC
    UInt32          unk2C0;

	static TLSData* GetTLSData();
	static UInt32 GetHeapIndex();
	static void SetHeapIndex(UInt32 index);

	// 25C is used as do not head track the player , 2B8 is used to init QueudFile::unk0018
};
static_assert(sizeof(TLSData) == 0x2C4);

struct MemoryManager {
    bool bInitialized;
    UInt16 usNumHeaps;
    UInt16 usNumPhysicalHeaps;
    IMemoryHeap** ppHeaps;
    IMemoryHeap* pHeapsByContextA[66];
    NiTMap<UInt32, ScrapHeap*> kHeapMap; // BSMapBase
    DWORD dword124;
    bool byte128;
    bool byte129;
    DWORD dword12C;
    DWORD dword130;
    DWORD dword134;


    static MemoryManager* GetSingleton();
    static ScrapHeap* GetThreadScrapHeap();
    
    template <typename T_Data>
    static T_Data* Allocate() {
        return ThisStdCall<T_Data*>(0xAA3E40, MemoryManager::GetSingleton(), sizeof(T_Data));
    };
    static void* Allocate(size_t aSize); // operator new
    static void* Reallocate(void* apOldMem, size_t auiNewSize);
    static void Deallocate(void* apMemory); // operator delete

    static void* AllocateScrap(size_t aSize, UInt32 aAlignment);
    static void DeallocateScrap(void* apMemory);

	static void EnterContext(UInt32& apPrevious, UInt32 auiNew);
	static void LeaveContext(UInt32& apPrevious);
};

template <typename T, const UInt32 ConstructorPtr = 0, typename... Args>
T* New(Args &&... args)
{
	auto* alloc = MemoryManager::Allocate<T>();
	if constexpr (ConstructorPtr)
	{
		ThisStdCall(ConstructorPtr, alloc, std::forward<Args>(args)...);
	}
	else
	{
		memset(alloc, 0, sizeof(T));
	}
	return static_cast<T*>(alloc);
}

template <typename T, const UInt32 DestructorPtr = 0, typename... Args>
void Delete(T* t, Args &&... args)
{
	if constexpr (DestructorPtr)
	{
		ThisStdCall(DestructorPtr, t, std::forward<Args>(args)...);
	}
	MemoryManager::Deallocate(t);
}