#pragma once

#include "GameForms.h"
#include "GameBSExtraData.h"
#include "GameExtraData.h"
#include "GameProcess.h"
#include "NiPoint.h"

struct ScriptEventList;
class ActiveEffect;
class NiNode;
class Animation;

#include "TESChildCell.hpp"
#include "TESObjectREFR.hpp"
#include "BaseProcess.hpp"
#include "MobileObject.hpp"
#include "MagicCaster.hpp"
#include "MagicTarget.hpp"

class hkaRaycastInterface
{
public:
	hkaRaycastInterface();
	~hkaRaycastInterface();
	virtual hkaRaycastInterface*	Destroy(bool doFree);
	virtual void					Unk_01(void* arg0);
	virtual void					Unk_02(void);

	// Assumed to be 0x010 bytes due to context where the vftable is used
	UInt32	unk000[(0x010 - 0x004) >> 2];	// 0000
};
STATIC_ASSERT(sizeof(hkaRaycastInterface) == 0x010);

class bhkRagdollController : public hkaRaycastInterface
{
public:
	bhkRagdollController();
	~bhkRagdollController();

	UInt32	unk000[(0x021C - 0x010) >> 2];	// 0010
	UInt8	fill021C[3];					// 021C
	bool	bool021F;						// 021F	when null assume FIK status is false
	bool	fikStatus;						// 0220
	UInt8	fill0221[3];					// 0221
};
STATIC_ASSERT(sizeof(bhkRagdollController) == 0x0224);

class bhkRagdollPenetrationUtil;
class ActorMover;
class PlayerMover;
class ImageSpaceModifierInstanceDOF;
class ImageSpaceModifierInstanceDRB;

#include "Actor.hpp"
#include "Character.hpp"

struct CombatActors;

// 9BC
#include "PlayerCharacter.hpp"