#pragma once

#include "NiD3DGeometryGroupManager.hpp"
#include "NiD3DShader.hpp"
#include "NiD3DShaderLibraryVersion.hpp"
#include "NiDX92DBufferData.hpp"
#include "NiDX9AdapterDesc.hpp"
#include "NiDX9DynamicTextureData.hpp"
#include "NiDX9IndexBufferManager.hpp"
#include "NiDX9LightManager.hpp"
#include "NiDX9RenderedCubeMapData.hpp"
#include "NiDX9RenderedTextureData.hpp"
#include "NiDX9RenderState.hpp"
#include "NiDX9ShaderDeclaration.hpp"
#include "NiDX9TextureManager.hpp"
#include "NiDynamicEffectState.hpp"
#include "NiDynamicGeometryGroup.hpp"
#include "NiRenderedCubeMap.hpp"
#include "NiRenderer.hpp"
#include "NiRenderTargetGroup.hpp"
#include "NiRenderTargetGroup.hpp"
#include "NiTStringMap.hpp"
#include "NiUnsharedGeometryGroup.hpp"

class NiMaterialDescriptor;
struct NiViewport;

class NiDX9Renderer : public NiRenderer {
public:
	enum FrameBufferFormat {
		FBFMT_UNKNOWN = 0,
		FBFMT_R8G8B8,
		FBFMT_A8R8G8B8,
		FBFMT_X8R8G8B8,
		FBFMT_R5G6B5,
		FBFMT_X1R5G5B5,
		FBFMT_A1R5G5B5,
		FBFMT_A4R4G4B4,
		FBFMT_R3G3B2,
		FBFMT_A8,
		FBFMT_A8R3G3B2,
		FBFMT_X4R4G4B4,
		FBFMT_R16F,
		FBFMT_G16R16F,
		FBFMT_A16B16G16R16F,
		FBFMT_R32F,
		FBFMT_G32R32F,
		FBFMT_A32B32G32R32F,
		FBFMT_NUM
	};

	enum DepthStencilFormat {
		DSFMT_UNKNOWN = 0,
		DSFMT_D16_LOCKABLE = 70,
		DSFMT_D32 = 71,
		DSFMT_D15S1 = 73,
		DSFMT_D24S8 = 75,
		DSFMT_D16 = 80,
		DSFMT_D24X8 = 77,
		DSFMT_D24X4S4 = 79,
	};

	enum PresentationInterval {
		PRESENT_INTERVAL_IMMEDIATE = 0,
		PRESENT_INTERVAL_ONE = 1,
		PRESENT_INTERVAL_TWO = 2,
		PRESENT_INTERVAL_THREE = 3,
		PRESENT_INTERVAL_FOUR = 4,
		PRESENT_INTERVAL_NUM
	};

	enum SwapEffect {
		SWAPEFFECT_DEFAULT,
		SWAPEFFECT_DISCARD,
		SWAPEFFECT_FLIP,
		SWAPEFFECT_COPY,
		SWAPEFFECT_NUM
	};

	enum FrameBufferMode {
		FBMODE_DEFAULT,
		FBMODE_LOCKABLE,
		FBMODE_MULTISAMPLES_2 = 0x00010000,
		FBMODE_MULTISAMPLES_3 = 0x00020000,
		FBMODE_MULTISAMPLES_4 = 0x00030000,
		FBMODE_MULTISAMPLES_5 = 0x00040000,
		FBMODE_MULTISAMPLES_6 = 0x00050000,
		FBMODE_MULTISAMPLES_7 = 0x00060000,
		FBMODE_MULTISAMPLES_8 = 0x00070000,
		FBMODE_MULTISAMPLES_9 = 0x00080000,
		FBMODE_MULTISAMPLES_10 = 0x00090000,
		FBMODE_MULTISAMPLES_11 = 0x000a0000,
		FBMODE_MULTISAMPLES_12 = 0x000b0000,
		FBMODE_MULTISAMPLES_13 = 0x000c0000,
		FBMODE_MULTISAMPLES_14 = 0x000d0000,
		FBMODE_MULTISAMPLES_15 = 0x000e0000,
		FBMODE_MULTISAMPLES_16 = 0x000f0000,
		FBMODE_MULTISAMPLES_NONMASKABLE = 0x80000000,
		FBMODE_QUALITY_MASK = 0x0000FFFF,
		FBMODE_NUM = 18
	};

	enum RefreshRate {
		REFRESHRATE_DEFAULT = 0
	};

	enum TexFormat {
		TEX_RGB555 = 0x0,
		TEX_RGB565 = 0x1,
		TEX_RGB888 = 0x2,
		TEX_RGBA5551 = 0x3,
		TEX_RGBA4444 = 0x4,
		TEX_RGBA8888 = 0x5,
		TEX_PAL8 = 0x6,
		TEX_PALA8 = 0x7,
		TEX_DXT1 = 0x8,
		TEX_DXT3 = 0x9,
		TEX_DXT5 = 0xA,
		TEX_BUMP88 = 0xB,
		TEX_BUMPLUMA556 = 0xC,
		TEX_BUMPLUMA888 = 0xD,
		TEX_L8 = 0xE,
		TEX_A8 = 0xF,
		TEX_R16F = 0x10,
		TEX_RG32F = 0x11,
		TEX_RGBA64F = 0x12,
		TEX_R32F = 0x13,
		TEX_RG64F = 0x14,
		TEX_RGBA128F = 0x15,
		TEX_DEFAULT = 0x16,
		TEX_NUM = 0x16,
	};

	enum DeviceDesc
	{
		DEVDESC_PURE = 0x0,
		DEVDESC_HAL_HWVERTEX = 0x1,
		DEVDESC_HAL_MIXEDVERTEX = 0x2,
		DEVDESC_HAL_SWVERTEX = 0x3,
		DEVDESC_REF = 0x4,
		DEVDESC_REF_HWVERTEX = 0x5,
		DEVDESC_REF_MIXEDVERTEX = 0x6,
		DEVDESC_NUM = 0x7,
	};

	virtual void					SetDefaultProgramCache();
	virtual NiPixelFormat*			FindClosestDepthStencilFormat(const NiPixelFormat* apFrontBufferFormat, UInt32 uiDepthBPP, UInt32 uiStencilBPP);
	virtual void					FindClosestPixelFormat();
	virtual void					GetDriverInfo();
	virtual UInt32					GetFlags();
	virtual void					SetDepthClear(float afValue);
	virtual float					GetDepthClear();
	virtual void					SetBackgroundColorAlpha(const NiColorA&);
	virtual void					SetBackgroundColor(const NiColor&);
	virtual void					GetBackgroundColor(NiColorA&);
	virtual void					SetStencilClear(UInt32 uiClear);
	virtual UInt32					GetStencilClear();
	virtual void					ValidateRenderTargetGroup();
	virtual void					IsDepthBufferCompatible();
	virtual NiRenderTargetGroup*	GetDefaultRenderTargetGroup();
	virtual NiRenderTargetGroup*	GetCurrentRenderTargetGroup();
	virtual NiRenderTargetGroup*	GetDefaultDepthStencilBuffer();
	virtual Ni2DBuffer*				GetDefaultBackBuffer();
	virtual UInt32					GetMaxBuffersPerRenderTargetGroup();
	virtual bool					GetIndependentBufferBitDepths();
	virtual bool					PrecacheTexture(NiTexture* apIm, bool abForceLoad = false, bool abLocked = false);
	virtual bool					SetMipmapSkipLevel();
	virtual UInt32					GetMipmapSkipLevel();
	virtual bool					PrecacheGeometry(NiGeometry* apGeometry, UInt32 uiBonesPerPartition, UInt32 uiBonesPerVertex, NiD3DShaderDeclaration* apShaderDeclaration);
	virtual void					PurgeGeometryData(NiGeometryData*);
	virtual void					PurgeMaterial(NiMaterialProperty*);
	virtual void					PurgeEffect(NiDynamicEffect*);
	virtual void					PurgeScreenTexture();
	virtual void					PurgeSkinPartition(NiSkinPartition* apSkinPartition);
	virtual void					PurgeSkinInstance(NiSkinInstance* apSkinInstance);
	virtual bool					PurgeTexture(NiTexture* apTexture);
	virtual bool					PurgeAllTextures();
	virtual NiPixelData*			TakeScreenShot(const NiRect<UInt32>* apScreenRect, const NiRenderTargetGroup* apTarget);
	virtual bool					FastCopy(const Ni2DBuffer* apSrc, Ni2DBuffer* apDest, const NiRect<UInt32>* apSrcRect = 0, UInt32 uiDestX = 0, UInt32 uiDestY = 0);
	virtual bool					Copy(const Ni2DBuffer* apSrc, Ni2DBuffer* apDest, NiRect<UInt32>* apSrcRect, NiRect<UInt32>* apDestRect, Ni2DBuffer::CopyFilterPreference ePref);
	virtual bool					GetLeftRightSwap();
	virtual bool					SetLeftRightSwap(bool bSwap);
	virtual float					GetMaxFogValue();
	virtual void					SetMaxFogValue(float);
	virtual void*					Allocate_4B(UInt32 auiSize);
	virtual void					Unk_4C(UInt8* apucDataBlock, UInt32 auiBlockSize); // Empty
	virtual void					Unk_4D(UInt8* apucDataBlock, UInt32 auiBlockSize); // Empty
	virtual void					Deallocate_4E(void*);
	virtual bool					CreateSourceTextureRendererData(NiSourceTexture* apTexture);
	virtual bool					CreateRenderedTextureRendererData(NiRenderedTexture* apTexture, Ni2DBuffer::MultiSamplePreference eMSAAPref);
	virtual bool					CreateSourceCubeMapRendererData(NiSourceCubeMap*);
	virtual bool					CreateRenderedCubeMapRendererData(NiRenderedCubeMap* apCubeMap);
	virtual bool					CreateDynamicTextureRendererData(void*);
	virtual bool					CreatePaletteRendererData(NiPalette* apPalette);
	virtual bool					CreateDepthStencilRendererData(NiDepthStencilBuffer* apDSBuffer, const NiPixelFormat* apFormat, int eMSAAPref);
	virtual void					RemoveRenderedCubeMapData(NiRenderedCubeMap* apCubeMap);
	virtual void					RemoveRenderedTextureData(NiRenderedTexture* apTexture);
	virtual void					RemoveDynamicTextureData(void* apTexture);
	virtual void					LockDynamicTexture(const NiTexture::RendererData* apRData, int* iPitch);
	virtual bool					UnLockDynamicTexture(const NiTexture::RendererData* apRData);
	virtual NiShader*				GetFragmentShader(NiMaterialDescriptor* apMaterialDescriptor);
	virtual void					Unk_5C();
	virtual void					DrawIndexedPrimitive_TRIANGLELIST();
	virtual void					DrawIndexedPrimitive_TRIANGLESTRIP();
	virtual bool					Do_BeginFrame();
	virtual bool					Do_EndFrame();
	virtual bool					Do_DisplayFrame();
	virtual void					Do_ClearBuffer(const NiRect<float>*, UInt32 uiMode);
	virtual void					Do_SetCameraData(const NiPoint3* kWorldLoc, const NiPoint3* kWorldDir, const NiPoint3* kWorldUp, const NiPoint3* kWorldRight, const NiFrustum* kFrustum, const NiRect<float>* kPort);
	virtual void					Do_SetScreenSpaceCameraData(const NiRect<float>* apPort);
	virtual bool					Do_BeginUsingRenderTargetGroup(NiRenderTargetGroup* apTarget, NiDX9Renderer::ClearFlags uiClearMode);
	virtual bool					Do_EndUsingRenderTargetGroup();
	virtual void					Do_BeginBatch(NiPropertyState* apPropertyState, NiDynamicEffectState* apEffectState);
	virtual void					Do_EndBatch();
	virtual void					Do_BatchRenderShape(NiTriShape* apTriShape);
	virtual void					Do_BatchRenderStrips(NiTriStrips* apTriStrips);
	virtual void					Do_RenderShape(NiTriShape* apTriShape);
	virtual void					Do_RenderTristrips(NiTriStrips* apTriStrips);
	virtual void					Do_RenderShapeAlt(NiTriShape* apTriShape);
	virtual void					Do_RenderTristripsAlt(NiTriStrips* apTriStrips);
	virtual void					E70140(void*);
	virtual void					Do_RenderPoints(NiParticles* apParticles);
	virtual void					Do_RenderLines(NiLines* apLines);
	virtual void					Do_RenderScreenTexture(NiScreenTexture* apScreenTexture);

	class BatchedObject {
	public:
		NiGeometry*				m_pkGeometry;
		void*					m_pkCurrPartition;
		NiGeometryBufferData*	m_pkBuffData;
		BatchedObject*			m_pkNext;
		BatchedObject*			ms_pkFreeList;
	};

	LPDIRECT3DVERTEXDECLARATION9									hParticleVertexDecls[2];
	LPDIRECT3DDEVICE9												m_pkD3DDevice9;
	D3DCAPS9														m_kD3DCaps9;
	HWND															m_kWndDevice;
	HWND															m_kWndFocus;
	char															m_acDriverDesc[512];
	UInt32															m_uiAdapter;
	D3DDEVTYPE														m_eDevType;
	UInt32															m_uiBehaviorFlags;
	D3DFORMAT														m_eAdapterFormat;
	bool															m_bSWVertexCapable;
	bool															m_bSWVertexSwitchable;
	const NiDX9AdapterDesc*											m_pkAdapterDesc;
	const NiDX9DeviceDesc*											m_pkDeviceDesc;
	UInt32															m_uiBackground;
	float															m_fZClear;
	UInt32															m_uiStencilClear;
	UInt32															m_uiRendFlags;
	char															m_acBehavior[32];
	NiTPointerMap<void*, void*>										m_kPrePackObjects;
	BatchedObject*													m_pkBatchHead;
	BatchedObject*													m_pkBatchTail;
	NiPropertyState*												m_pkBatchedPropertyState;
	NiDynamicEffectState*											m_pkBatchedEffectState;
	NiD3DShaderInterface*											m_spBatchedShader;
	NiPoint3														m_kCamRight;
	NiPoint3														m_kCamUp;
	NiPoint3														m_kModelCamRight;
	NiPoint3														m_kModelCamUp;
	NiBound															m_kWorldBound;
	const NiBound													m_kDefaultBound;
	float															m_fNearDepth;
	float															m_fDepthRange;
	D3DXMATRIX														m_kD3DIdentity;
	D3DVIEWPORT9													m_kD3DPort;
	UInt32															m_uiHWBones;
	UInt32															m_uiMaxStreams;
	UInt32															m_uiMaxPixelShaderVersion;
	UInt32															m_uiMaxVertexShaderVersion;
	bool															m_bMipmapCubeMaps;
	bool															m_bDynamicTexturesCapable;
	UInt32															m_uiResetCounter;
	bool															m_bDeviceLost;
	NiPixelFormat*													m_aapkTextureFormats[4][22];
	NiPixelFormat*													m_apkDefaultTextureFormat[4];
	NiPointer<NiPixelData>											m_aspDefaultTextureData[4];
	TexFormat														m_eReplacementDataFormat;
	NiPointer<NiRenderTargetGroup>									m_spDefaultRenderTargetGroup;
	NiRenderTargetGroup*											m_pkCurrRenderTargetGroup;
	NiRenderTargetGroup*											m_pkCurrOnscreenRenderTargetGroup;
	NiTPointerMap<HWND, NiRenderTargetGroup*>						m_kOnscreenRenderTargetGroups;
	UInt32															m_uiMaxNumRenderTargets;
	bool															m_bIndependentBitDepths;
	bool															m_bMRTPostPixelShaderBlending;
	NiPointer<NiPropertyState>										m_spScreenTexturePropertyState;
	NiD3DGeometryGroupManager*										m_pkGeometryGroupManager;
	NiUnsharedGeometryGroup*										m_pkDefaultGroup;
	NiDynamicGeometryGroup*											m_pkDynamicGroup;
	NiDX9RenderState*												m_pkRenderState;
	NiDX9VertexBufferManager*										m_pkVBManager;
	NiDX9IndexBufferManager*										m_pkIBManager;
	NiDX9TextureManager*											m_pkTextureManager;
	NiDX9LightManager*												m_pkLightManager;
	NiTPointerMap<NiRenderedTexture*, NiDX9RenderedTextureData*>	m_kRenderedTextures;
	NiTPointerMap<NiRenderedCubeMap*, NiDX9RenderedCubeMapData*>	m_kRenderedCubeMaps;
	NiTPointerMap<void*, NiDX9DynamicTextureData*>					m_kDynamicTextures;
	NiTexturePtr													m_spClipperImage;
	NiTPointerList<NiDX92DBufferData*>								m_kBuffersToUseAtDisplayFrame;
	NiTPointerList<NiD3DShaderInterface*>							m_kD3DShaders;
	NiD3DShaderLibraryVersion										m_kShaderLibraryVersion;
	D3DXMATRIX														m_kD3DMat;
	D3DXMATRIX														m_kD3DView;
	D3DXMATRIX														m_kD3DProj;
	D3DXMATRIX														m_kViewProj;
	D3DXMATRIX														m_kInvView;
	NiPoint2*														m_pkScreenTextureVerts;
	NiColorA*														m_pkScreenTextureColors;
	NiPoint2*														m_pkScreenTextureTexCoords;
	UInt16															m_usNumScreenTextureVerts;
	UInt16*															m_pusScreenTextureIndices;
	UInt32															m_uiNumScreenTextureIndices;
	UInt32															m_uiCreationWidth;
	UInt32															m_uiCreationHeight;
	UInt32															m_uiCreationUseFlags;
	HWND															m_kCreationWndDevice;
	HWND															m_kCreationWndFocus;
	UInt32															m_uiCreationAdapter;
	DeviceDesc														m_eCreationDesc;
	FrameBufferFormat												m_eCreationFBFormat;
	DepthStencilFormat												m_eCreationDSFormat;
	PresentationInterval											m_eCreationPresentationInterval;
	SwapEffect														m_eCreationSwapEffect;
	FrameBufferMode													m_uiCreationFBMode;
	UInt32															m_uiCreationBackBufferCount;
	RefreshRate														m_uiCreationRefreshRate;
	bool															unkAD0;
	NiTPrimitiveArray<int>											m_kResetNotifyFuncs;
	NiTPrimitiveArray<void*>										m_kResetNotifyFuncData;
	NiTPrimitiveArray<int>											m_kLostDeviceNotifyFuncs;
	NiTPrimitiveArray<void*>										m_kLostDeviceNotifyFuncData;
	NiTMap<D3DFORMAT, NiPixelFormat*>								m_kDepthStencilFormats;
	NiFrustum														m_kCachedFrustum;
	NiRect<float>													m_kCachedPort;
	void*															unkB50[12];

	static NiDX9Renderer* GetSingleton();

	static LPDIRECT3D9 GetD3D9();

	LPDIRECT3DDEVICE9 GetD3DDevice();

	static bool IsFrameStateOutsideFrame();

	void ClearBuffer(const NiRect<float>* pkR, ClearFlags uiMode);

	UInt32 GetScreenWidth();
	UInt32 GetScreenHeight();

	bool BeginUsingRenderTargetGroup(NiRenderTargetGroup* apTarget, NiRenderer::ClearFlags uiClearMode);
	void EndUsingRenderTargetGroup() { ThisStdCall(0xB6B330, this);}

	static D3DMULTISAMPLE_TYPE GetMultiSampleType(UInt32 auiMode);

	void SetModelTransform(const NiTransform& kXform, bool bPushToDevice);

	void SetScreenSpaceCameraData(NiRect<float>* pkPort);

	void SetCameraData(NiPoint3* kWorldLoc, NiPoint3* kWorldDir, NiPoint3* kWorldUp, NiPoint3* kWorldRight, NiFrustum* kFrustum, NiRect<float>* kPort);
};

ASSERT_SIZE(NiDX9Renderer, 0xB80);
ASSERT_OFFSET(NiDX9Renderer, m_pkAdapterDesc, 0x5D8);
ASSERT_OFFSET(NiDX9Renderer, m_kDefaultBound, 0x674);
ASSERT_OFFSET(NiDX9Renderer, m_eReplacementDataFormat, 0x880);
ASSERT_OFFSET(NiDX9Renderer, m_kBuffersToUseAtDisplayFrame, 0x900);
ASSERT_OFFSET(NiDX9Renderer, m_kD3DShaders, 0x90C);