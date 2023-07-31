#pragma once

#include <span>

#include "NiTypes.h"
#include "GameTypes.h"
#include "Utilities.h"

/*** class hierarchy
 *
 *	yet again taken from rtti information
 *	ni doesn't seem to use multiple inheritance
 *
 *	thanks to the NifTools team for their work on the on-disk format
 *	thanks to netimmerse for NiObject::DumpAttributes
 *
 *	all offsets here are assuming patch 1.2 as they changed dramatically
 *	0xE8 bytes were removed from NiObjectNET, and basically everything derives from that
 *
 *	NiObject derives from NiRefObject
 *
 *	BSFaceGenMorphData - derived from NiRefObject
 *		BSFaceGenMorphDataHead
 *		BSFaceGenMorphDataHair
 *
 *	BSTempEffect - derived from NiObject
 *		BSTempEffectDecal
 *		BSTempEffectGeometryDecal
 *		BSTempEffectParticle
 *		MagicHitEffect
 *			MagicModelHitEffect
 *			MagicShaderHitEffect
 *
 *	NiDX92DBufferData - derived from NiRefObject and something else
 *		NiDX9DepthStencilBufferData
 *			NiDX9SwapChainDepthStencilBufferData
 *			NiDX9ImplicitDepthStencilBufferData
 *			NiDX9AdditionalDepthStencilBufferData
 *		NiDX9TextureBufferData
 *		NiDX9OnscreenBufferData
 *			NiDX9SwapChainBufferData
 *			NiDX9ImplicitBufferData
 *
 *	NiObject
 *		NiObjectNET
 *			NiProperty
 *				NiTexturingProperty
 *				NiVertexColorProperty
 *				NiWireframeProperty
 *				NiZBufferProperty
 *				NiMaterialProperty
 *				NiAlphaProperty
 *				NiStencilProperty
 *				NiRendererSpecificProperty
 *				NiShadeProperty
 *					BSShaderProperty
 *						SkyShaderProperty
 *						ParticleShaderProperty
 *						BSShaderLightingProperty
 *							DistantLODShaderProperty
 *							TallGrassShaderProperty
 *							BSShaderPPLightingProperty
 *								SpeedTreeShaderPPLightingProperty
 *									SpeedTreeBranchShaderProperty
 *								Lighting30ShaderProperty
 *								HairShaderProperty
 *							SpeedTreeShaderLightingProperty
 *								SpeedTreeLeafShaderProperty
 *								SpeedTreeFrondShaderProperty
 *							GeometryDecalShaderProperty
 *						PrecipitationShaderProperty
 *						BoltShaderProperty
 *						WaterShaderProperty
 *				NiSpecularProperty
 *				NiFogProperty
 *					BSFogProperty
 *				NiDitherProperty
 *			NiTexture
 *				NiDX9Direct3DTexture
 *				NiSourceTexture
 *					NiSourceCubeMap
 *				NiRenderedTexture
 *					NiRenderedCubeMap
 *			NiAVObject
 *				NiDynamicEffect
 *					NiLight
 *						NiDirectionalLight
 *						NiPointLight
 *							NiSpotLight
 *						NiAmbientLight
 *					NiTextureEffect
 *				NiNode
 *					SceneGraph
 *					BSTempNodeManager
 *					BSTempNode
 *					BSCellNode
 *					BSClearZNode
 *					BSFadeNode
 *					BSScissorNode
 *					BSTimingNode
 *					BSFaceGenNiNode
 *					NiBillboardNode
 *					NiSwitchNode
 *						NiLODNode
 *							NiBSLODNode
 *					NiSortAdjustNode
 *					NiBSPNode
 *					ShadowSceneNode
 *				NiCamera
 *					BSCubeMapCamera - RTTI data incorrect
 *					NiScreenSpaceCamera
 *				NiGeometry
 *					NiLines
 *					NiTriBasedGeom
 *						NiTriShape
 *							BSScissorTriShape
 *							NiScreenElements
 *							NiScreenGeometry
 *							TallGrassTriShape
 *						NiTriStrips
 *							TallGrassTriStrips
 *					NiParticles
 *						NiParticleSystem
 *							NiMeshParticleSystem
 *						NiParticleMeshes
 *			NiSequenceStreamHelper
 *		NiRenderer
 *			NiDX9Renderer
 *		NiPixelData
 *		NiCollisionObject
 *			NiCollisionData
 *			bhkNiCollisionObject
 *				bhkCollisionObject
 *					bhkBlendCollisionObject
 *						WeaponObject
 *						bhkBlendCollisionObjectAddRotation
 *				bhkPCollisionObject
 *					bhkSPCollisionObject
 *		NiControllerSequence
 *			BSAnimGroupSequence
 *		NiTimeController
 *			BSDoorHavokController
 *			BSPlayerDistanceCheckController
 *			NiD3DController
 *			NiControllerManager
 *			NiInterpController
 *				NiSingleInterpController
 *					NiTransformController
 *					NiPSysModifierCtlr
 *						NiPSysEmitterCtlr
 *						NiPSysModifierBoolCtlr
 *							NiPSysModifierActiveCtlr
 *						NiPSysModifierFloatCtlr
 *							NiPSysInitialRotSpeedVarCtlr
 *							NiPSysInitialRotSpeedCtlr
 *							NiPSysInitialRotAngleVarCtlr
 *							NiPSysInitialRotAngleCtlr
 *							NiPSysGravityStrengthCtlr
 *							NiPSysFieldMaxDistanceCtlr
 *							NiPSysFieldMagnitudeCtlr
 *							NiPSysFieldAttenuationCtlr
 *							NiPSysEmitterSpeedCtlr
 *							NiPSysEmitterPlanarAngleVarCtlr
 *							NiPSysEmitterPlanarAngleCtlr
 *							NiPSysEmitterLifeSpanCtlr
 *							NiPSysEmitterInitialRadiusCtlr
 *							NiPSysEmitterDeclinationVarCtlr
 *							NiPSysEmitterDeclinationCtlr
 *							NiPSysAirFieldSpreadCtlr
 *							NiPSysAirFieldInheritVelocityCtlr
 *							NiPSysAirFieldAirFrictionCtlr
 *					NiFloatInterpController
 *						NiFlipController
 *						NiAlphaController
 *						NiTextureTransformController
 *						NiLightDimmerController
 *					NiBoolInterpController
 *						NiVisController
 *					NiPoint3InterpController
 *						NiMaterialColorController
 *						NiLightColorController
 *					NiExtraDataController
 *						NiFloatsExtraDataPoint3Controller
 *						NiFloatsExtraDataController
 *						NiFloatExtraDataController
 *						NiColorExtraDataController
 *				NiMultiTargetTransformController
 *				NiGeomMorpherController
 *			bhkBlendController
 *			bhkForceController
 *			NiBSBoneLODController
 *			NiUVController
 *			NiPathController
 *			NiLookAtController
 *			NiKeyframeManager
 *			NiBoneLODController
 *			NiPSysUpdateCtlr
 *			NiPSysResetOnLoopCtlr
 *			NiFloatController
 *				NiRollController
 *		bhkRefObject
 *			bhkSerializable
 *				bhkWorld - NiRTTI has incorrect parent
 *					bhkWorldM
 *				bhkAction
 *					bhkUnaryAction
 *						bhkMouseSpringAction
 *						bhkMotorAction
 *					bhkBinaryAction
 *						bhkSpringAction
 *						bhkAngularDashpotAction
 *						bhkDashpotAction
 *				bhkWorldObject
 *					bhkPhantom
 *						bhkShapePhantom
 *							bhkSimpleShapePhantom
 *							bhkCachingShapePhantom
 *						bhkAabbPhantom
 *							bhkAvoidBox
 *					bhkEntity
 *						bhkRigidBody
 *							bhkRigidBodyT
 *				bhkConstraint
 *					bhkLimitedHingeConstraint
 *					bhkMalleableConstraint
 *					bhkBreakableConstraint
 *					bhkWheelConstraint
 *					bhkStiffSpringConstraint
 *					bhkRagdollConstraint
 *					bhkPrismaticConstraint
 *					bhkHingeConstraint
 *					bhkBallAndSocketConstraint
 *					bhkGenericConstraint
 *						bhkFixedConstraint
 *					bhkPointToPathConstraint
 *					bhkPoweredHingeConstraint
 *				bhkShape
 *					bhkTransformShape
 *					bhkSphereRepShape
 *						bhkConvexShape
 *							bhkSphereShape
 *							bhkCapsuleShape
 *							bhkBoxShape
 *							bhkTriangleShape
 *							bhkCylinderShape
 *							bhkConvexVerticesShape
 *								bhkCharControllerShape
 *							bhkConvexTransformShape
 *							bhkConvexSweepShape
 *						bhkMultiSphereShape
 *					bhkBvTreeShape
 *						bhkTriSampledHeightFieldBvTreeShape
 *						bhkMoppBvTreeShape
 *					bhkShapeCollection
 *						bhkListShape
 *						bhkPackedNiTriStripsShape
 *						bhkNiTriStripsShape
 *					bhkHeightFieldShape
 *						bhkPlaneShape
 *				bhkCharacterProxy
 *					bhkCharacterListenerArrow - no NiRTTI
 *					bhkCharacterListenerSpell - no NiRTTI
 *					bhkCharacterController - no NiRTTI
 *		NiExtraData
 *			TESObjectExtraData
 *			BSFaceGenAnimationData
 *			BSFaceGenModelExtraData
 *			BSFaceGenBaseMorphExtraData
 *			DebugTextExtraData
 *			NiStringExtraData
 *			NiFloatExtraData
 *				FadeNodeMaxAlphaExtraData
 *			BSFurnitureMarker
 *			NiBinaryExtraData
 *			BSBound
 *			NiSCMExtraData
 *			NiTextKeyExtraData
 *			NiVertWeightsExtraData
 *			bhkExtraData
 *			PArrayPoint
 *			NiIntegerExtraData
 *				BSXFlags
 *			NiFloatsExtraData
 *			NiColorExtraData
 *			NiVectorExtraData
 *			NiSwitchStringExtraData
 *			NiStringsExtraData
 *			NiIntegersExtraData
 *			NiBooleanExtraData
 *		NiAdditionalGeometryData
 *			BSPackedAdditionalGeometryData
 *		NiGeometryData
 *			NiLinesData
 *			NiTriBasedGeomData
 *				NiTriStripsData
 *					NiTriStripsDynamicData
 *				NiTriShapeData
 *					NiScreenElementsData
 *					NiTriShapeDynamicData
 *					NiScreenGeometryData
 *			NiParticlesData
 *				NiPSysData
 *					NiMeshPSysData
 *				NiParticleMeshesData
 *		NiTask
 *			BSTECreateTask
 *			NiParallelUpdateTaskManager::SignalTask
 *			NiGeomMorpherUpdateTask
 *			NiPSysUpdateTask
 *		NiSkinInstance
 *		NiSkinPartition
 *		NiSkinData
 *		NiRenderTargetGroup
 *		Ni2DBuffer
 *			NiDepthStencilBuffer
 *		NiUVData
 *		NiStringPalette
 *		NiSequence
 *		NiRotData
 *		NiPosData
 *		NiMorphData
 *		NiTransformData
 *		NiFloatData
 *		NiColorData
 *		NiBSplineData
 *		NiBSplineBasisData
 *		NiBoolData
 *		NiTaskManager
 *			NiParallelUpdateTaskManager
 *		hkPackedNiTriStripsData
 *		NiInterpolator
 *			NiBlendInterpolator
 *				NiBlendTransformInterpolator
 *				NiBlendAccumTransformInterpolator
 *				NiBlendFloatInterpolator
 *				NiBlendQuaternionInterpolator
 *				NiBlendPoint3Interpolator
 *				NiBlendColorInterpolator
 *				NiBlendBoolInterpolator
 *			NiLookAtInterpolator
 *			NiKeyBasedInterpolator
 *				NiFloatInterpolator
 *				NiTransformInterpolator
 *				NiQuaternionInterpolator
 *				NiPoint3Interpolator
 *				NiPathInterpolator
 *				NiColorInterpolator
 *				NiBoolInterpolator
 *					NiBoolTimelineInterpolator
 *			NiBSplineInterpolator
 *				NiBSplineTransformInterpolator
 *					NiBSplineCompTransformInterpolator
 *				NiBSplinePoint3Interpolator
 *					NiBSplineCompPoint3Interpolator
 *				NiBSplineFloatInterpolator
 *					NiBSplineCompFloatInterpolator
 *				NiBSplineColorInterpolator
 *					NiBSplineCompColorInterpolator
 *		NiAVObjectPalette
 *			NiDefaultAVObjectPalette
 *		BSReference
 *		BSNodeReferences
 *		NiPalette
 *		NiLODData
 *			NiRangeLODData
 *			NiScreenLODData
 *		NiPSysModifier
 *			BSWindModifier
 *			NiPSysMeshUpdateModifier
 *			NiPSysRotationModifier
 *			NiPSysEmitter
 *				NiPSysMeshEmitter
 *				NiPSysVolumeEmitter
 *					NiPSysCylinderEmitter
 *					NiPSysSphereEmitter
 *					NiPSysBoxEmitter
 *					BSPSysArrayEmitter
 *			NiPSysGravityModifier
 *			NiPSysSpawnModifier
 *			BSParentVelocityModifier
 *			NiPSysPositionModifier
 *			NiPSysGrowFadeModifier
 *			NiPSysDragModifier
 *			NiPSysColorModifier
 *			NiPSysColliderManager
 *			NiPSysBoundUpdateModifier
 *			NiPSysBombModifier
 *			NiPSysAgeDeathModifier
 *			NiPSysFieldModifier
 *				NiPSysVortexFieldModifier
 *				NiPSysTurbulenceFieldModifier
 *				NiPSysRadialFieldModifier
 *				NiPSysGravityFieldModifier
 *				NiPSysDragFieldModifier
 *				NiPSysAirFieldModifier
 *		NiPSysEmitterCtlrData
 *		NiAccumulator
 *			NiBackToFrontAccumulator
 *				NiAlphaAccumulator
 *					BSShaderAccumulator
 *		NiScreenPolygon
 *		NiScreenTexture
 *		NiPSysCollider
 *			NiPSysSphericalCollider
 *			NiPSysPlanarCollider
 *
 *	NiShader
 *		NiD3DShaderInterface
 *			NiD3DShader
 *				NiD3DDefaultShader
 *					SkyShader
 *					ShadowLightShader
 *						ParallaxShader
 *						SkinShader
 *						HairShader
 *						SpeedTreeBranchShader
 *					WaterShaderHeightMap
 *					WaterShader
 *					WaterShaderDisplacement
 *					ParticleShader
 *					TallGrassShader
 *					PrecipitationShader
 *					SpeedTreeLeafShader
 *					BoltShader
 *					Lighting30Shader
 *					GeometryDecalShader
 *					SpeedTreeFrondShader
 *					DistantLODShader
 *
 *	NiD3DShaderConstantMap
 *		NiD3DSCM_Vertex
 *		NiD3DSCM_Pixel
 *
 ****/

class NiAVObject;
class BSFadeNode;
class NiExtraData;
class NiTimeController;
class NiControllerManager;
class NiStringPalette;
class NiTextKeyExtraData;
class NiCamera;
class NiProperty;
class NiStream;
class TESAnimGroup;
class NiNode;
class NiGeometry;
class ParticleShaderProperty;
class TESObjectREFR;
class TESEffectShader;
class ActiveEffect;

#include "NiSourceCubeMap.hpp"
#include "NiRenderedCubeMap.hpp"
#include "NiSequenceStreamHelper.hpp"
#include "NiControllerSequence.hpp"
#include "NiPropertyState.hpp"
#include "NiDynamicEffectState.hpp"
#include "NiCullingProcess.hpp"
#include "BSFile.hpp"
#include "MagicShaderHitEffect.hpp"

// 06C
class BSAnimGroupSequence : public NiControllerSequence
{
public:
	BSAnimGroupSequence();
	~BSAnimGroupSequence();

	TESAnimGroup		* animGroup;	//068
};

class NiNode;

// 02C+
class TESAnimGroup
{
public:
	// derived from NiRefObject
	TESAnimGroup();
	~TESAnimGroup();

	virtual void Destructor(bool arg0);

	enum{
		kAnimGroup_Idle					= 0x0,
		kAnimGroup_DynamicIdle,
		kAnimGroup_SpecialIdle,
		kAnimGroup_Forward,
		kAnimGroup_Backward,
		kAnimGroup_Left,
		kAnimGroup_Right,
		kAnimGroup_FastForward,
		kAnimGroup_FastBackward,
		kAnimGroup_FastLeft,
		kAnimGroup_FastRight,
		kAnimGroup_DodgeForward,
		kAnimGroup_DodgeBack,
		kAnimGroup_DodgeLeft,
		kAnimGroup_DodgeRight,
		kAnimGroup_TurnLeft,
		kAnimGroup_TurnRight,
		kAnimGroup_Aim,
		kAnimGroup_AimUp,
		kAnimGroup_AimDown,
		kAnimGroup_AimIS,
		kAnimGroup_AimISUp,
		kAnimGroup_AimISDown,
		kAnimGroup_Holster,
		kAnimGroup_Equip,
		kAnimGroup_Unequip,
		kAnimGroup_AttackLeft,
		kAnimGroup_AttackLeftUp,
		kAnimGroup_AttackLeftDown,
		kAnimGroup_AttackLeftIS,
		kAnimGroup_AttackLeftISUp,
		kAnimGroup_AttackLeftISDown,
		kAnimGroup_AttackRight,
		kAnimGroup_AttackRightUp,
		kAnimGroup_AttackRightDown,
		kAnimGroup_AttackRightIS,
		kAnimGroup_AttackRightISUp,
		kAnimGroup_AttackRightISDown,
		kAnimGroup_Attack3,
		kAnimGroup_Attack3Up,
		kAnimGroup_Attack3Down,
		kAnimGroup_Attack3IS,
		kAnimGroup_Attack3ISUp,
		kAnimGroup_Attack3ISDown,
		kAnimGroup_Attack4,
		kAnimGroup_Attack4Up,
		kAnimGroup_Attack4Down,
		kAnimGroup_Attack4IS,
		kAnimGroup_Attack4ISUp,
		kAnimGroup_Attack4ISDown,
		kAnimGroup_Attack5,
		kAnimGroup_Attack5Up,
		kAnimGroup_Attack5Down,
		kAnimGroup_Attack5IS,
		kAnimGroup_Attack5ISUp,
		kAnimGroup_Attack5ISDown,
		kAnimGroup_Attack6,
		kAnimGroup_Attack6Up,
		kAnimGroup_Attack6Down,
		kAnimGroup_Attack6IS,
		kAnimGroup_Attack6ISUp,
		kAnimGroup_Attack6ISDown,
		kAnimGroup_Attack7,
		kAnimGroup_Attack7Up,
		kAnimGroup_Attack7Down,
		kAnimGroup_Attack7IS,
		kAnimGroup_Attack7ISUp,
		kAnimGroup_Attack7ISDown,
		kAnimGroup_Attack8,
		kAnimGroup_Attack8Up,
		kAnimGroup_Attack8Down,
		kAnimGroup_Attack8IS,
		kAnimGroup_Attack8ISUp,
		kAnimGroup_Attack8ISDown,
		kAnimGroup_AttackLoop,
		kAnimGroup_AttackLoopUp,
		kAnimGroup_AttackLoopDown,
		kAnimGroup_AttackLoopIS,
		kAnimGroup_AttackLoopISUp,
		kAnimGroup_AttackLoopISDown,
		kAnimGroup_AttackSpin,
		kAnimGroup_AttackSpinUp,
		kAnimGroup_AttackSpinDown,
		kAnimGroup_AttackSpinIS,
		kAnimGroup_AttackSpinISUp,
		kAnimGroup_AttackSpinISDown,
		kAnimGroup_AttackSpin2,
		kAnimGroup_AttackSpin2Up,
		kAnimGroup_AttackSpin2Down,
		kAnimGroup_AttackSpin2IS,
		kAnimGroup_AttackSpin2ISUp,
		kAnimGroup_AttackSpin2ISDown,
		kAnimGroup_AttackPower,
		kAnimGroup_AttackForwardPower,
		kAnimGroup_AttackBackPower,
		kAnimGroup_AttackLeftPower,
		kAnimGroup_AttackRightPower,
		kAnimGroup_AttackCustom1Power,
		kAnimGroup_AttackCustom2Power,
		kAnimGroup_AttackCustom3Power,
		kAnimGroup_AttackCustom4Power,
		kAnimGroup_AttackCustom5Power,
		kAnimGroup_PlaceMine,
		kAnimGroup_PlaceMineUp,
		kAnimGroup_PlaceMineDown,
		kAnimGroup_PlaceMineIS,
		kAnimGroup_PlaceMineISUp,
		kAnimGroup_PlaceMineISDown,
		kAnimGroup_PlaceMine2,
		kAnimGroup_PlaceMine2Up,
		kAnimGroup_PlaceMine2Down,
		kAnimGroup_PlaceMine2IS,
		kAnimGroup_PlaceMine2ISUp,
		kAnimGroup_PlaceMine2ISDown,
		kAnimGroup_AttackThrow,
		kAnimGroup_AttackThrowUp,
		kAnimGroup_AttackThrowDown,
		kAnimGroup_AttackThrowIS,
		kAnimGroup_AttackThrowISUp,
		kAnimGroup_AttackThrowISDown,
		kAnimGroup_AttackThrow2,
		kAnimGroup_AttackThrow2Up,
		kAnimGroup_AttackThrow2Down,
		kAnimGroup_AttackThrow2IS,
		kAnimGroup_AttackThrow2ISUp,
		kAnimGroup_AttackThrow2ISDown,
		kAnimGroup_AttackThrow3,
		kAnimGroup_AttackThrow3Up,
		kAnimGroup_AttackThrow3Down,
		kAnimGroup_AttackThrow3IS,
		kAnimGroup_AttackThrow3ISUp,
		kAnimGroup_AttackThrow3ISDown,
		kAnimGroup_AttackThrow4,
		kAnimGroup_AttackThrow4Up,
		kAnimGroup_AttackThrow4Down,
		kAnimGroup_AttackThrow4IS,
		kAnimGroup_AttackThrow4ISUp,
		kAnimGroup_AttackThrow4ISDown,
		kAnimGroup_AttackThrow5,
		kAnimGroup_AttackThrow5Up,
		kAnimGroup_AttackThrow5Down,
		kAnimGroup_AttackThrow5IS,
		kAnimGroup_AttackThrow5ISUp,
		kAnimGroup_AttackThrow5ISDown,
		kAnimGroup_Attack9,
		kAnimGroup_Attack9Up,
		kAnimGroup_Attack9Down,
		kAnimGroup_Attack9IS,
		kAnimGroup_Attack9ISUp,
		kAnimGroup_Attack9ISDown,
		kAnimGroup_AttackThrow6,
		kAnimGroup_AttackThrow6Up,
		kAnimGroup_AttackThrow6Down,
		kAnimGroup_AttackThrow6IS,
		kAnimGroup_AttackThrow6ISUp,
		kAnimGroup_AttackThrow6ISDown,
		kAnimGroup_AttackThrow7,
		kAnimGroup_AttackThrow7Up,
		kAnimGroup_AttackThrow7Down,
		kAnimGroup_AttackThrow7IS,
		kAnimGroup_AttackThrow7ISUp,
		kAnimGroup_AttackThrow7ISDown,
		kAnimGroup_AttackThrow8,
		kAnimGroup_AttackThrow8Up,
		kAnimGroup_AttackThrow8Down,
		kAnimGroup_AttackThrow8IS,
		kAnimGroup_AttackThrow8ISUp,
		kAnimGroup_AttackThrow8ISDown,
		kAnimGroup_Counter,
		kAnimGroup_stomp,
		kAnimGroup_BlockIdle,
		kAnimGroup_BlockHit,
		kAnimGroup_Recoil,
		kAnimGroup_ReloadWStart,
		kAnimGroup_ReloadXStart,
		kAnimGroup_ReloadYStart,
		kAnimGroup_ReloadZStart,
		kAnimGroup_ReloadA,
		kAnimGroup_ReloadB,
		kAnimGroup_ReloadC,
		kAnimGroup_ReloadD,
		kAnimGroup_ReloadE,
		kAnimGroup_ReloadF,
		kAnimGroup_ReloadG,
		kAnimGroup_ReloadH,
		kAnimGroup_ReloadI,
		kAnimGroup_ReloadJ,
		kAnimGroup_ReloadK,
		kAnimGroup_ReloadL,
		kAnimGroup_ReloadM,
		kAnimGroup_ReloadN,
		kAnimGroup_ReloadO,
		kAnimGroup_ReloadP,
		kAnimGroup_ReloadQ,
		kAnimGroup_ReloadR,
		kAnimGroup_ReloadS,
		kAnimGroup_ReloadW,
		kAnimGroup_ReloadX,
		kAnimGroup_ReloadY,
		kAnimGroup_ReloadZ,
		kAnimGroup_JamA,
		kAnimGroup_JamB,
		kAnimGroup_JamC,
		kAnimGroup_JamD,
		kAnimGroup_JamE,
		kAnimGroup_JamF,
		kAnimGroup_JamG,
		kAnimGroup_JamH,
		kAnimGroup_JamI,
		kAnimGroup_JamJ,
		kAnimGroup_JamK,
		kAnimGroup_JamL,
		kAnimGroup_JamM,
		kAnimGroup_JamN,
		kAnimGroup_JamO,
		kAnimGroup_JamP,
		kAnimGroup_JamQ,
		kAnimGroup_JamR,
		kAnimGroup_JamS,
		kAnimGroup_JamW,
		kAnimGroup_JamX,
		kAnimGroup_JamY,
		kAnimGroup_JamZ,
		kAnimGroup_Stagger,
		kAnimGroup_Death,
		kAnimGroup_Talking,
		kAnimGroup_PipBoy,
		kAnimGroup_JumpStart,
		kAnimGroup_JumpLoop,
		kAnimGroup_JumpLand,
		kAnimGroup_HandGrip1,
		kAnimGroup_HandGrip2,
		kAnimGroup_HandGrip3,
		kAnimGroup_HandGrip4,
		kAnimGroup_HandGrip5,
		kAnimGroup_HandGrip6,
		kAnimGroup_JumpLoopForward,
		kAnimGroup_JumpLoopBackward,
		kAnimGroup_JumpLoopLeft,
		kAnimGroup_JumpLoopRight,
		kAnimGroup_PipBoyChild,
		kAnimGroup_JumpLandForward,
		kAnimGroup_JumpLandBackward,
		kAnimGroup_JumpLandLeft,
		kAnimGroup_JumpLandRight,

		kAnimGroup_Max						// = 0x0FFF,	// Temporary until known
	};

	// 24
	struct AnimGroupInfo {
		const char	* name;				// 00
		UInt8		sequenceType;		// 04
		UInt8		pad[3];
		UInt32		unk08[7];			// 08
	};

	//void**	vtbl			//000
	UInt8		unk004;			//004
	UInt8		unk005[3];
	UInt8		animGroup;		//008 init'ed to word arg in c'tor
	UInt8		unk009;			//009 does what?
	UInt16		unk00A;
	UInt32		numFrames;		//00C count of group frames (Start, Detach, Attack, End, etc)
	float		** frameData;	//010 pointer to float array of group frame times (size numFrames)
	UInt32		unk014;			//014
	UInt32		unk018;			//018
	UInt32		unk01C;			//01C
	UInt8		unk020;			//020
	UInt8		unk021;
	UInt8		pad022[2];
	UInt32		unk024;			//024
	void		* unk028;		//028

	static const char* StringForAnimGroupCode(UInt32 groupCode);
	static UInt32 AnimGroupForString(const char* groupName);
};

extern std::span<TESAnimGroup::AnimGroupInfo> g_animGroups;

void DumpAnimGroups(void);
