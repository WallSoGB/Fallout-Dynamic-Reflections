#pragma once

#include "BSShaderManager.hpp"
#include "NiShadeProperty.hpp"
#include "BSRenderPass.hpp"

class BSShaderAccumulator;
class NiSourceTexture;
class Lighting30ShaderProperty;

NiSmartPointer(BSShaderProperty);

enum Flags {
	BSSP_SPECULAR = 0X0,
	BSSP_SKINNED = 0X1,
	BSSP_LOW_DETAIL = 0X2,
	BSSP_VERTEX_ALPHA = 0X3,
	BSSP_MOTION_BLUR = 0X4,
	BSSP_SINGLE_PASS = 0X5,
	BSSP_EMPTY = 0X6,
	BSSP_ENVIRONMENT_MAPPING = 0X7,
	BSSP_ALPHA_TEXTURE = 0X8,
	BSSP_ZPREPASS = 0X9,
	BSSP_FACEGEN = 0XA,
	BSSP_PARALLAX = 0XB,
	BSSP_MODEL_SPACE_NORMALS = 0XC,
	BSSP_NON_PROJECTIVE_SHADOWS = 0XD,
	BSSP_LANDSCAPE = 0XE,
	BSSP_REFRACTION = 0XF,
	BSSP_FIRE_REFRACTION = 0X10,
	BSSP_EYE_ENVIRONMENT_MAPPING = 0X11,
	BSSP_HAIR = 0X12,
	BSSP_DYNAMIC_ALPHA = 0X13,
	BSSP_LOCAL_MAP_HIDE_SECRET = 0X14,
	BSSP_WINDOW_ENVIRONMENT_MAPPING = 0X15,
	BSSP_TREE_BILLBOARD = 0X16,
	BSSP_SHADOW_FRUSTUM = 0X17,
	BSSP_MULTIPLE_TEXTURES = 0X18,
	BSSP_REMAPPABLE_TEXTURES = 0X19,
	BSSP_DECAL = 0X1A,
	BSSP_DYNAMIC_DECAL = 0X1B,
	BSSP_PARALLAX_OCCLUSION = 0X1C,
	BSSP_EXTERNAL_EMITTANCE = 0X1D,
	BSSP_SHADOW_MAP = 0X1E,
	BSSP_ZBUFFER_TEST = 0X1F,
	BSSP_ZBUFFER_WRITE = 0X20,
	BSSP_LOD_LANDSCAPE = 0X21,
	BSSP_LOD_BUILDING = 0X22,
	BSSP_NO_FADE = 0X23,
	BSSP_REFRACTION_TINT = 0X24,
	BSSP_VERTEX_COLORS = 0X25,
	BSSP_1ST_PERSON = 0X26,
	BSSP_1ST_LIGHT_IS_POINTLIGHT = 0X27,
	BSSP_2ND_LIGHT = 0X28,
	BSSP_3RD_LIGHT = 0X29,
	BSSP_VERTEX_LIGHTING = 0X2A,
	BSSP_UNIFORM_SCALE = 0X2B,
	BSSP_FIT_SLOPE = 0X2C,
	BSSP_BILLBOARD_ENV_FADE = 0X2D,
	BSSP_NO_LOD_LAND_BLEND = 0X2E,
	BSSP_ENVMAP_LIGHT_FADE = 0X2F,
	BSSP_WIRE_FRAME = 0X30,
	BSSP_VATS_SELECTION = 0X31,
	BSSP_SHOW_IN_LOCAL_MAP = 0X32,
	BSSP_PREMULT_ALPHA = 0X33,
	BSSP_SKIP_NORMAL_MAPS = 0X34,
	BSSP_ALPHA_DECAL = 0X35,
	BSSP_NO_TRANSPARENCY_MULTISAMPLING = 0X36,
	BSSP_STINGER_PROP = 0X37,
};


class BSShaderProperty : public NiShadeProperty {
public:
	BSShaderProperty();
	virtual ~BSShaderProperty();

	enum BSShaderFlags {
		Specular = 0x1,
		Skinned = 0x2,
		LowDetail = 0x4,
		Vertex_Alpha = 0x8,
		Motion_Blur = 0x10,
		Single_Pass = 0x20,
		Empty = 0x40,
		Environment_Mapping = 0x80,
		Alpha_Texture = 0x100,
		Z_Prepass = 0x200,
		FaceGen = 0x400,
		Parallax_Shader = 0x800,
		Model_Space_Normals = 0x1000,
		Non_Projective_Shadows = 0x2000,
		Landscape = 0x4000,
		Refraction = 0x8000,
		Fire_Refraction = 0x10000,
		Eye_Environment_Mapping = 0x20000,
		Hair = 0x40000,
		Dynamic_Alpha = 0x80000,
		Localmap_Hide_Secret = 0x100000,
		Window_Environment_Mapping = 0x200000,
		Tree_Billboard = 0x400000,
		Shadow_Frustum = 0x800000,
		Multiple_Textures = 0x1000000,
		Remappable_Textures = 0x2000000,
		Decal_Single_Pass = 0x4000000,
		Dynamic_Decal_Single_Pass = 0x8000000,
		Parallax_Occlusion = 0x10000000,
		External_Emittance = 0x20000000,
		Shadow_Map = 0x40000000,
		ZBuffer_Test = 0x80000000,
	};

	enum BSShaderFlags2 {
		ZBuffer_Write = 0x1,
		LOD_Landscape = 0x2,
		LOD_Building = 0x4,
		No_Fade = 0x8,
		Refraction_Tint = 0x10,
		Vertex_Colors = 0x20,
		_1st_person = 0x40,
		_1st_Light_is_Point_Light = 0x80,
		_2nd_Light = 0x100,
		_3rd_Light = 0x200,
		Vertex_Lighting = 0x400,
		Uniform_Scale = 0x800,
		Fit_Slope = 0x1000,
		Billboard_and_Envmap_Light_Fade = 0x2000,
		No_LOD_Land_Blend = 0x4000,
		Envmap_Light_Fade = 0x8000,
		Wireframe = 0x10000,
		VATS_Selection = 0x20000,
		Show_in_Local_Map = 0x40000,
		Premult_Alpha = 0x80000,
		Skip_Normal_Maps = 0x100000,
		Alpha_Decal = 0x200000,
		No_Transparency_Multisampling = 0x400000,
		stinger_prop = 0x800000,
		Unknown3 = 0x1000000,
		Unknown4 = 0x2000000,
		Unknown5 = 0x4000000,
		Unknown6 = 0x8000000,
		Unknown7 = 0x10000000,
		Unknown8 = 0x20000000,
		Unknown9 = 0x40000000,
		Wall_RealTimeEnv = 0x80000000,
	};

	struct RenderPassList : public NiTArray<BSRenderPass*> {
		UInt32 uiNumPasses;
	};

	virtual void				CopyTo(BSShaderProperty* apTarget);
	virtual void				CopyData(BSShaderProperty* apTarget);
	virtual void				SetupGeometry(NiGeometry* apGeometry);
	virtual RenderPassList*		GetRenderPasses(NiGeometry* apGeometry, UInt32 auiEnabledPasses, WORD* pusPassCount, int a5, BSShaderAccumulator* apAccumulator, int a7);
	virtual UInt16				GetNumberofPasses(NiGeometry* apGeometry);
	virtual RenderPassList*		GetRenderPassList4C();
	virtual BSRenderPass*		SetDepthPass(NiGeometry* apGeometry);
	virtual BSShaderProperty*	Unk_2A(NiGeometry* pGeometry, UInt32 unk0 = 0, UInt32 unk2 = 0);
	virtual NiSourceTexture*	GetDiffuseTexture();
	virtual RenderPassList*		WaterDepth(NiGeometry* pGeometry);
	virtual void				Unk_2D();
	virtual void				PrecacheTextures();

	UInt32 ulFlags[2];
	float fAlpha;
	float fFadeAlpha;
	float fEnvMapScale;
	float fLODFade;
	UInt32 iLastRenderPassState;
	BSShaderProperty::RenderPassList* pRenderPassList;
	BSShaderProperty::RenderPassList* pRenderPassList_depthMap;
	BSShaderProperty::RenderPassList* pRenderPassList_constAlpha;
	BSShaderProperty::RenderPassList* pRenderPassList_localMap;
	BSShaderProperty::RenderPassList* pRenderPassList_unk4C;
	BSShaderProperty::RenderPassList* pRenderPassList_waterDepth;
	BSShaderProperty::RenderPassList* pRenderPassList_silhouette;
	BSShaderManager::Shader uiShaderIndex;
	float fDepthBias;

	CREATE_OBJECT(BSShaderProperty, 0xBA9250);

	bool GetFlag(Flags auiFlag) const;
	void SetFlag(Flags auiFlag, bool abEnable);

	bool HasSpecular() { return (ulFlags[0] & Specular) != 0; }
	bool IsSkinned() { return (ulFlags[0] & Skinned) != 0; }
	bool IsLowDetail() { return (ulFlags[0] & LowDetail) != 0; }
	bool HasVertexAlpha() { return (ulFlags[0] & Vertex_Alpha) != 0; }
	bool HasMotionBlur() { return (ulFlags[0] & Motion_Blur) != 0; }
	bool IsSinglePass() { return (ulFlags[0] & Single_Pass) != 0; }
	bool IsEmpty() { return (ulFlags[0] & Empty) != 0; }
	bool HasEnvironmentMap() { return (ulFlags[0] & Environment_Mapping) != 0; }
	bool HasAlphaTexture() { return (ulFlags[0] & Alpha_Texture) != 0; }
	bool IsZPrePass() { return (ulFlags[0] & Z_Prepass) != 0; }
	bool IsFaceGen() { return (ulFlags[0] & FaceGen) != 0; }
	bool IsParallax() { return (ulFlags[0] & Parallax_Shader) != 0; }
	bool HasModelSpaceNormals() { return (ulFlags[0] & Model_Space_Normals) != 0; }
	bool HasNonProjectiveShadows() { return (ulFlags[0] & Non_Projective_Shadows) != 0; }
	bool IsLandscape() { return (ulFlags[0] & Landscape) != 0; }
	bool HasRefraction() { return (ulFlags[0] & Refraction) != 0; }
	bool HasFireRefraction() { return (ulFlags[0] & Fire_Refraction) != 0; }
	bool HasEyeEnvironmentMap() { return (ulFlags[0] & Eye_Environment_Mapping) != 0; }
	bool IsHair() { return (ulFlags[0] & Hair) != 0; }
	bool HasDynamicAlpha() { return (ulFlags[0] & Dynamic_Alpha) != 0; }
	bool IsLocalMapHideSecret() { return (ulFlags[0] & Localmap_Hide_Secret) != 0; }
	bool HasWindowEnvironmentMap() { return (ulFlags[0] & Window_Environment_Mapping) != 0; }
	bool IsTreeBillboard() { return (ulFlags[0] & Tree_Billboard) != 0; }
	bool UsesShadowFrustum() { return (ulFlags[0] & Shadow_Frustum) != 0; }
	bool HasMultipleTextures() { return (ulFlags[0] & Multiple_Textures) != 0; }
	bool HasRemappableTextures() { return (ulFlags[0] & Remappable_Textures) != 0; }
	bool IsSinglePassDecal() { return (ulFlags[0] & Decal_Single_Pass) != 0; }
	bool IsSinglePassDynamicDecal() { return (ulFlags[0] & Dynamic_Decal_Single_Pass) != 0; }
	bool HasParallaxOcclusion() { return (ulFlags[0] & Parallax_Occlusion) != 0; }
	bool HasExternalEmittance() { return (ulFlags[0] & External_Emittance) != 0; }
	bool IsShadowMap() { return (ulFlags[0] & Shadow_Map) != 0; }
	bool HasZBufferTest() { return (ulFlags[0] & ZBuffer_Test) != 0; }
	bool HasZBufferWrite() { return (ulFlags[1] & ZBuffer_Write) != 0; }
	bool IsLODLand() { return (ulFlags[1] & LOD_Landscape) != 0; }
	bool IsLODBuilding() { return (ulFlags[1] & LOD_Building) != 0; }
	bool HasNoFade() { return (ulFlags[1] & No_Fade) != 0; }
	bool HasRefractionTint() { return (ulFlags[1] & Refraction_Tint) != 0; }
	bool HasVertexColors() { return (ulFlags[1] & Vertex_Colors) != 0; }
	bool Is1stPerson() { return (ulFlags[1] & _1st_person) != 0; }
	bool Is1stLightPointlight() { return (ulFlags[1] & _1st_Light_is_Point_Light) != 0; }
	bool Is2ndLight() { return (ulFlags[1] & _2nd_Light) != 0; }
	bool Is3rdLight() { return (ulFlags[1] & _3rd_Light) != 0; }
	bool HasVertexLighting() { return (ulFlags[1] & Vertex_Lighting) != 0; }
	bool HasUniformScale() { return (ulFlags[1] & Uniform_Scale) != 0; }
	bool DoesFitSlopes() { return (ulFlags[1] & Fit_Slope) != 0; }
	bool HasBillboarbAndEnvmapLightFade() { return (ulFlags[1] & Billboard_and_Envmap_Light_Fade) != 0; }
	bool HasNoLODLandBlend() { return (ulFlags[1] & No_LOD_Land_Blend) != 0; }
	bool HasEnvmapLightFade() { return (ulFlags[1] & Envmap_Light_Fade) != 0; }
	bool IsWireframe() { return (ulFlags[1] & Wireframe) != 0; }
	bool IsVATSSelection() { return (ulFlags[1] & VATS_Selection) != 0; }
	bool IsShownOnMap() { return (ulFlags[1] & Show_in_Local_Map) != 0; }
	bool HasPremultAlpha() { return (ulFlags[1] & Premult_Alpha) != 0; }
	bool DoesSkipNormalMaps() { return (ulFlags[1] & Skip_Normal_Maps) != 0; }
	bool IsAlphaDecal() { return (ulFlags[1] & Alpha_Decal) != 0; }
	bool HasNoTMSAA() { return (ulFlags[1] & No_Transparency_Multisampling) != 0; }
	bool IsStingerProperty() { return (ulFlags[1] & stinger_prop) != 0; }
	bool HasRealtimeCubeMaps() { return (ulFlags[1] & Wall_RealTimeEnv) != 0; }
};

ASSERT_SIZE(BSShaderProperty, 0x60);
ASSERT_SIZE(BSShaderProperty::RenderPassList, 0x14);