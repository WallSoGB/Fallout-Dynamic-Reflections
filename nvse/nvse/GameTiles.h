#pragma once

#include "NiNodes.h"
#include "GameTypes.h"
#include "Menu.hpp"

typedef UInt32 (* _TraitNameToID)(const char* traitName);
extern const _TraitNameToID TraitNameToID;

const char * TraitIDToName(int id);	// slow

//	Tile			
//		TileRect		3C	ID=385
//			TileMenu	40	ID=389
//		TileImage		48	ID=386
//			RadialTile		ID=38C but answer as TileImage !
//		TileText		4C	ID=387
//		Tile3D			50	ID=388
//	Close by:
//		HotRect	ID=38A
//		Window	ID=38B

class NiNode;
class NiObject;
class RefNiObject;

#include "Tile.hpp"

// 3C
class TileRect : public Tile
{
public:
	UInt32	unk38;	// 38
};

// 40
class TileMenu : public TileRect
{
public:
	Menu	* menu;	// 3C - confirmed
};

// 48
class TileImage : public Tile
{
public:
	float		flt038;		// 38
	NiPointer<NiObject> unk03C;		// 3C
	NiPointer<NiObject> unk040;		// 40
	UInt8		byt044;		// 44
	UInt8		fill[3];	// 45-47
};

class TileText : public Tile
{
public:
};

void Debug_DumpTraits(void);
void Debug_DumpTileImages(void);
