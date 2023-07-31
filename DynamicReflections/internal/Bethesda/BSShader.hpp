#pragma once

#include "NiD3DDefaultShader.hpp"
#include "NiDX9ShaderDeclaration.hpp"
#include "BSRenderPass.hpp"

class NiD3DPass;
class BSShaderProperty;

class BSShader : public NiD3DDefaultShader {
public:
	enum ShaderType {
		TYPE_ShadowLightShader = 0x1,
		TYPE_HairShader = 0x2,
		TYPE_ParallaxShader = 0x3,
		TYPE_SkinShader = 0x4,
		TYPE_SpeedTreeBranchShader = 0x5,
		TYPE_TallGrassShader = 0x6,
		TYPE_DistantLODShader = 0x7,
		TYPE_SpeedTreeFrondShader = 0x8,
		TYPE_SpeedTreeLeafShader = 0x9,
		TYPE_NiD3DDefaultShader = 0xA,
		TYPE_SkyShader = 0xB,
		TYPE_GeometryDecalShader = 0xC,
		TYPE_WaterShader = 0xD,
		TYPE_ParticleShader = 0xE,
		TYPE_BoltShader = 0xF,
		TYPE_BeamShader = 0x10,
		TYPE_Lighting30Shader = 0x11,
		TYPE_PrecipitationShader = 0x12,
		TYPE_VolumetricFogShader = 0x13,
		TYPE_TileShader = 0x14,
		TYPE_BSShaderNoLighting = 0x16,
		TYPE_BSShaderBloodSplatter = 0x17,
		TYPE_BSImagespaceShader = 0x18,
		TYPE_BSDistantTreeShader = 0x19,
	};

	virtual void SetRenderPass(UInt32 aeType);
	virtual void SetShaders(UInt32 aeType);
	virtual void Func_62(UInt32 aeType);
	virtual void Func_63(UInt32 aeType);
	virtual void Func_64(UInt32 aeType);
	virtual void RestoreTechnique(UInt32 uiLastPass);
	virtual void Func_66();
	virtual void Func_67();
	virtual void Func_68(NiPropertyState* pShaderProps);
	virtual void Func_69();
	virtual NiDX9ShaderDeclaration* GetShaderDeclaration(int, BSShaderProperty* property);
	virtual void InitShaderConstants();
	virtual void Func_72();
	virtual void Func_73();
	virtual void ClearRenderStages(NiD3DPass* pass);
	virtual void Func_75();
	virtual void CreateNewPass();
	virtual void Func_77();
	virtual void Func_78(UInt32* apeType, int a2);

	NiD3DPass* pass;
	void* Unk60;
	bool Unk64;
	UInt32 iShaderType;

	bool IsShadowLightShader() const { return iShaderType == TYPE_ShadowLightShader; }
	bool IsHairShader() const { return iShaderType == TYPE_HairShader; }
	bool IsParallaxShader() const { return iShaderType == TYPE_ParallaxShader; }
	bool IsSkinShader() const { return iShaderType == TYPE_SkinShader; }
	bool IsSpeedTreeBranchShader() const { return iShaderType == TYPE_SpeedTreeBranchShader; }
	bool IsTallGrassShader() const { return iShaderType == TYPE_TallGrassShader; }
	bool IsDistantLODShader() const { return iShaderType == TYPE_DistantLODShader; }
	bool IsSpeedTreeFrondShader() const { return iShaderType == TYPE_SpeedTreeFrondShader; }
	bool IsSpeedTreeLeafShader() const { return iShaderType == TYPE_SpeedTreeLeafShader; }
	bool IsNiD3DDefaultShader() const { return iShaderType == TYPE_NiD3DDefaultShader; }
	bool IsSkyShader() const { return iShaderType == TYPE_SkyShader; }
	bool IsGeometryDecalShader() const { return iShaderType == TYPE_GeometryDecalShader; }
	bool IsWaterShader() const { return iShaderType == TYPE_WaterShader; }
	bool IsParticleShader() const { return iShaderType == TYPE_ParticleShader; }
	bool IsBoltShader() const { return iShaderType == TYPE_BoltShader; }
	bool IsBeamShader() const { return iShaderType == TYPE_BeamShader; }
	bool IsLighting30Shader() const { return iShaderType == TYPE_Lighting30Shader; }
	bool IsPrecipitationShader() const { return iShaderType == TYPE_PrecipitationShader; }
	bool IsVolumetricFogShader() const { return iShaderType == TYPE_VolumetricFogShader; }
	bool IsTileShader() const { return iShaderType == TYPE_TileShader; }
	bool IsBSShaderNoLighting() const { return iShaderType == TYPE_BSShaderNoLighting; }
	bool IsBSShaderBloodSplatter() const { return iShaderType == TYPE_BSShaderBloodSplatter; }
	bool IsBSImagespaceShader() const { return iShaderType == TYPE_BSImagespaceShader; }
	bool IsBSDistantTreeShader() const { return iShaderType == TYPE_BSDistantTreeShader; }

	static void __fastcall SetShadersEx(BSShader* apThis, void*, RenderPassTypes aeType);
};

ASSERT_SIZE(BSShader, 0x6C);