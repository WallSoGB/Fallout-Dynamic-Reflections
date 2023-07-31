#pragma once

#include "bhkNiCollisionObject.hpp"
#include "NiBound.hpp"
#include "NiObjectNET.hpp"
#include "NiProperty.hpp"
#include "NiTListBase.hpp"
#include "NiTransform.hpp"
#include "NiUpdateData.hpp"

class NiCullingProcess;
class NiNode;
class NiCamera;

NiSmartPointer(NiAVObject);

class NiAVObject : public NiObjectNET {
public:
	NiAVObject();
	~NiAVObject();

	virtual void			UpdateControllers(NiUpdateData* arData);
	virtual void			ApplyTransform();
	virtual void			Unk_39();
	virtual NiAVObject*		GetObject_(const NiFixedString& kName);
	virtual NiAVObject*		GetObjectByName(const NiFixedString& kName);
	virtual void			SetSelectiveUpdateFlags(bool* bSelectiveUpdate, bool bSelectiveUpdateTransforms, bool* bRigid);
	virtual void			UpdateDownwardPass(const NiUpdateData& arData, UInt32 uFlags);
	virtual void			UpdateSelectedDownwardPass(const NiUpdateData& arData, UInt32 uFlags);
	virtual void			UpdateRigidDownwardPass(const NiUpdateData& arData, UInt32 uFlags);
	virtual void			Unk_46(void* arg);
	virtual void			UpdateTransform();
	virtual void			UpdateWorldData(const NiUpdateData& arData);
	virtual void			UpdateWorldBound();
	virtual void			UpdateTransformAndBounds(const NiUpdateData& arData);
	virtual void			PreAttachUpdate(NiNode* pEventualParent, const NiUpdateData& arData);
	virtual void			PreAttachUpdateProperties(NiNode* pEventualParent);
	virtual void			DetachParent();
	virtual void			UpdateUpwardPassParent(void* arg);
	virtual void			OnVisible(NiCullingProcess* kCuller);
	virtual void			PurgeRendererData(NiDX9Renderer* pkRenderer);

	enum NiFlags : UInt32
	{
		APP_CULLED = 0x1,
		SELECTIVE_UPDATE= 0x2,
		SELECTIVE_UPDATE_TRANSFORMS = 0x4,
		SELECTIVE_UPDATE_CONTROLLER = 0x8,
		SELECTIVE_UPDATE_RIGID = 0x10,
		DISPLAY_OBJECT = 0x20,
		DISABLE_SORTING = 0x40,
		SELECTIVE_UPDATE_TRANSFORMS_OVERRIDE = 0x80,
		IS_NODE = 0x100,
		SAVE_EXTERNAL_GEOM_DATA = 0x200,
		NO_DECALS = 0x400,
		ALWAYS_DRAW = 0x800,
		MESH_LOD = 0x1000,
		FIXED_BOUND = 0x2000,
		TOP_FADE_NODE = 0x4000,
		IGNORE_FADE = 0x8000,
		NO_ANIM_SYNC_X = 0x10000,
		NO_ANIM_SYNC_Y = 0x20000,
		NO_ANIM_SYNC_Z = 0x40000,
		NO_ANIM_SYNC_S = 0x80000,
		NO_DISMEMBER = 0x100000,
		NO_DISMEMBER_VALIDITY = 0x200000,
		RENDER_USE = 0x400000,
		MATERIALS_APPLIED = 0x800000,
		HIGH_DETAIL = 0x1000000,
		FORCE_UPDATE = 0x2000000,
		PREPROCESSED_NODE = 0x4000000,
		UNK_27 = 0x8000000,
		UNK_28 = 0x10000000,
		IS_POINTLIGHT = 0x20000000,
		DONE_INIT_LIGHTS = 0x40000000,
		IS_INSERTED = 0x80000000,
	};

	NiNode*						m_pkParent;
	bhkNiCollisionObjectPtr		m_spCollisionObject;
	NiBound*					m_kWorldBound;
	NiTListBase<NiPropertyPtr>	m_kPropertyList;
	UInt32						m_uiFlags;
	NiTransform					m_kLocal;
	NiTransform					m_kWorld;

	NiTransform* GetLocalTransform();
	NiTransform* GetWorldTransform();

	const float GetLocalScale() const;
	void SetLocalScale(float fScale) { m_kLocal.m_fScale = fScale; };

	const float GetWorldScale() const;
	void SetWorldScale(float fScale) { m_kWorld.m_fScale = fScale; };


	void SetLocalTranslate(const NiPoint3& pos);
	void SetLocalTranslate(const NiPoint3* pos);
	const NiPoint3& GetLocalTranslate() const;

	void SetWorldTranslate(const NiPoint3& pos);
	void SetWorldTranslate(const NiPoint3* pos);
	const NiPoint3& GetWorldTranslate() const;

	void SetLocalRotate(const NiMatrix3& kRot);
	void SetLocalRotate(const NiMatrix3* rot);
	const NiMatrix3& GetLocalRotate() const;

	void SetWorldRotate(const NiMatrix3& rot);
	void SetWorldRotate(const NiMatrix3* rot);
	const NiMatrix3& GetWorldRotate() const;


	// FLAGS

	void SetBit(bool bVal, int uMask);
	bool GetBit(int uMask);

	void SetAppCulled(bool bVal);
	bool GetAppCulled();

	void SetSelectiveUpdate(bool bVal);
	bool GetSelectiveUpdate();

	void SetSelUpdTransforms(bool bVal);
	bool GetSelUpdTransforms();

	void SetSelUpdController(bool bVal);
	bool GetSelUpdController();

	void SetSelUpdRigid(bool bVal);
	bool GetSelUpdRigid();

	void SetDisplayObject(bool bVal);
	bool GetDisplayObject();

	void SetDisableSorting(bool bVal);
	bool GetDisableSorting();

	void SetSelUpdTransformsOverride(bool bVal);
	bool GetSelUpdTransformsOverride();

	void SetIsNode(bool bVal);
	bool GetIsNode();

	void SetSaveExternalGeomData(bool bVal);
	bool GetSaveExternalGeomData();

	void SetNoDecals(bool bVal);
	bool GetNoDecals();

	void SetAlwaysDraw(bool bVal);
	bool GetAlwaysDraw();

	void SetMeshLOD(bool bVal);
	bool GetMeshLOD();

	void SetFixedBound(bool bVal);
	bool GetFixedBound();

	void SetTopFadeNode(bool bVal);
	bool GetTopFadeNode();

	void SetIgnoreFade(bool bVal);
	bool GetIgnoreFade();

	void SetNoAnimSyncX(bool bVal);
	bool GetNoAnimSyncX();

	void SetNoAnimSyncY(bool bVal);
	bool GetNoAnimSyncY();

	void SetNoAnimSyncZ(bool bVal);
	bool GetNoAnimSyncZ();

	void SetNoAnimSyncS(bool bVal);
	bool GetNoAnimSyncS();

	void SetNoDismember(bool bVal);
	bool GetNoDismember();

	void SetNoDismemberValidity(bool bVal);
	bool GetNoDismemberValidity();



	void Update(NiUpdateData& arData);
	NiNode* GetParent();
	const NiNode* GetParent() const;
	NiProperty* GetProperty(UInt32 iType);
	NiBound* GetWorldBound();
	NiAVObject* GetObjectByNameEx(const char* apName);

	NiNode* FindRootNode();

	void AttachProperty(NiPropertyPtr* aspProperty);
};

ASSERT_OFFSET(NiAVObject, m_pkParent, 0x18);
ASSERT_OFFSET(NiAVObject, m_spCollisionObject, 0x1C);
ASSERT_OFFSET(NiAVObject, m_kWorldBound, 0x20);
ASSERT_OFFSET(NiAVObject, m_kPropertyList, 0x24);
ASSERT_SIZE(NiTListBase<NiPointer<NiProperty>>, 0xC);
ASSERT_OFFSET(NiAVObject, m_uiFlags, 0x30);
ASSERT_OFFSET(NiAVObject, m_kLocal, 0x34);
ASSERT_OFFSET(NiAVObject, m_kWorld, 0x68);
ASSERT_SIZE(NiAVObject, 0x9C);