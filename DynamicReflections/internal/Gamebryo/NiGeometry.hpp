#pragma once

#include "NiAVObject.hpp"
#include "NiGeometryData.hpp"
#include "NiSkinInstance.hpp"
#include "NiAlphaProperty.hpp"
#include "NiCullingProperty.hpp"
#include "NiMaterialProperty.hpp"
#include "NiShadeProperty.hpp"
#include "NiStencilProperty.hpp"
#include "NiTexturingProperty.hpp"
#include "NiPropertyState.hpp"

class NiRenderer;
class NiShader;

NiSmartPointer(NiGeometry);

class NiGeometry : public NiAVObject {
public:
	NiGeometry();
	~NiGeometry();

	virtual void	RenderImmediate(NiRenderer* pkRenderer);
	virtual void	Func0038(NiRenderer* pkRenderer);
	virtual void	SetModelData(NiGeometryData* pkModelData);
	virtual void	Unk_3A();
	virtual void	CalculateConsistency(bool bTool);

	struct RendererData
	{
	};

	NiPropertyState m_kProperties;
	NiGeometryDataPtr m_spModelData;
	NiSkinInstancePtr m_spSkinInstance;
	NiShader* m_pShader;

	__forceinline NiGeometryData* GetModelData() const { return m_spModelData.m_pObject; };

	__forceinline NiSkinInstance* GetSkinInstance() const { return m_spSkinInstance.m_pObject; };
	__forceinline void SetSkinInstance(NiSkinInstance* pkSkinInstance) { m_spSkinInstance = pkSkinInstance; };

	__forceinline NiShader* GetShader() const { return m_pShader; };
	__forceinline void SetShader(NiShader* pkShaderDecl) { m_pShader = pkShaderDecl; };

	__forceinline NiAlphaProperty* GetAlphaProperty() const { return m_kProperties.m_aspProperties.m_spAlphaProperty.m_pObject; };

	__forceinline NiCullingProperty* GetCullingProperty() const { return m_kProperties.m_aspProperties.m_spCullingProperty.m_pObject; };

	__forceinline NiMaterialProperty* GetMaterialProperty() const { return m_kProperties.m_aspProperties.m_spMaterialProperty.m_pObject; };

	__forceinline NiShadeProperty* GetShadeProperty() const { return m_kProperties.m_aspProperties.m_spShadeProperty.m_pObject; };

	__forceinline NiStencilProperty* GetStencilProperty() const { return m_kProperties.m_aspProperties.m_spStencilProperty.m_pObject; };

	__forceinline NiTexturingProperty* GetTexturingProperty() const { return m_kProperties.m_aspProperties.m_spTextureProperty.m_pObject; };

	//inline NiPropertyState* GetPropertyState() const { return shaderProperties.m_spPropertyState.m_pObject; };

	static void __fastcall RenderImmediateEx(NiGeometry* apThis, void*, NiDX9Renderer* apRenderer);
};

ASSERT_SIZE(NiGeometry, 0xC4);