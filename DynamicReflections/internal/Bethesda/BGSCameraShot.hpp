#pragma once

#include "TESForm.hpp"
#include "TESModel.hpp"

class TESImageSpaceModifier;
class NiRefObject;

class BGSCameraShot : public TESForm {
	BGSCameraShot();
	~BGSCameraShot();

	enum Location;

	enum Action;

	enum Target : SInt32
	{
		kTargetAttacker = 0x0,
		kTargetProjectile = 0x1,
		kTargetTarget = 0x2,
	};

	enum Flags : SInt32
	{
		kPositionFollowsLocation = 0x1,
		kPositionFollowsTarget = 0x2,
		kDontFollowBone = 0x4,
		kFirstPersonCamera = 0x8,
		kNoTracer = 0x10,
		kStartAtTimeZero = 0x20,
	};

	struct s30
	{
		UInt32 unk00;
		TESImageSpaceModifier* imod;
	};

	TESModel model;
	BGSCameraShot::s30 unk030;
	BGSCameraShot::Action action;
	BGSCameraShot::Location location;
	BGSCameraShot::Target target;
	BGSCameraShot::Flags flags;
	float unk048;
	float unk04C;
	float globalTimeMult;
	float unk054;
	float unk058;
	float unk05C;
	NiRefObject* unk060;
	NiRefObject* unk064;
	UInt32 unk068;
	NiRefObject* unk06C;
	NiRefObject* unk070;
	UInt8 byte074;
	UInt8 byte075;
	UInt8 byte076;
	UInt8 gap077;
};

ASSERT_SIZE(BGSCameraShot, 0x78);