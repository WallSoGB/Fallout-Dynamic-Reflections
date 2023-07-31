#include "NiAVObject.hpp"
#include "NiBound.hpp"
#include "NiNode.hpp"
#include "NiTListBase.hpp"

NiNode* NiAVObject::GetParent() {
	return m_pkParent;
}

const NiNode* NiAVObject::GetParent() const {
	return m_pkParent;
}

NiTransform* NiAVObject::GetLocalTransform()
{
	return &m_kLocal;
}

NiTransform* NiAVObject::GetWorldTransform(){
	return &m_kWorld;
}

const float NiAVObject::GetLocalScale() const {
	return m_kLocal.m_fScale;
}

const float NiAVObject::GetWorldScale() const {
	return m_kWorld.m_fScale;
}

void NiAVObject::SetLocalTranslate(const NiPoint3& pos) {
	m_kLocal.m_Translate = pos;
}

void NiAVObject::SetLocalTranslate(const NiPoint3* pos) {
	m_kLocal.m_Translate = *pos;
}
const NiPoint3& NiAVObject::GetLocalTranslate() const {
	return m_kLocal.m_Translate;
}

void NiAVObject::SetWorldTranslate(const NiPoint3& pos) {
	m_kWorld.m_Translate = pos;
}

void NiAVObject::SetWorldTranslate(const NiPoint3* pos) {
	m_kWorld.m_Translate = *pos;
}

const NiPoint3& NiAVObject::GetWorldTranslate() const {
	return m_kWorld.m_Translate;
}

void NiAVObject::SetLocalRotate(const NiMatrix3& kRot) {
	m_kLocal.m_Rotate = kRot;
}

void NiAVObject::SetLocalRotate(const NiMatrix3* rot) {
	m_kLocal.m_Rotate = *rot;
}

const NiMatrix3& NiAVObject::GetLocalRotate() const {
	return m_kLocal.m_Rotate;
}

void NiAVObject::SetWorldRotate(const NiMatrix3& rot) {
	m_kWorld.m_Rotate = rot;
}

void NiAVObject::SetWorldRotate(const NiMatrix3* rot) {
	m_kWorld.m_Rotate = *rot;
}

const NiMatrix3& NiAVObject::GetWorldRotate() const {
	return m_kWorld.m_Rotate;
}



// FLAGS

inline void NiAVObject::SetBit(bool bVal, int uMask) {
	bVal ? m_uiFlags |= uMask : m_uiFlags &= ~uMask;
}

bool NiAVObject::GetBit(int uMask) {
	return (m_uiFlags & uMask) != 0;
}

void NiAVObject::SetAppCulled(bool bVal) {
	SetBit(bVal, APP_CULLED);
}

bool NiAVObject::GetAppCulled() {
	return GetBit(APP_CULLED);
}

void NiAVObject::SetSelectiveUpdate(bool bVal) {
	SetBit(bVal, SELECTIVE_UPDATE);
}

bool NiAVObject::GetSelectiveUpdate() {
	return GetBit(SELECTIVE_UPDATE);
}

void NiAVObject::SetSelUpdTransforms(bool bVal) {
	SetBit(bVal, SELECTIVE_UPDATE_TRANSFORMS);
}

bool NiAVObject::GetSelUpdTransforms() {
	return GetBit(SELECTIVE_UPDATE_TRANSFORMS);
}

void NiAVObject::SetSelUpdController(bool bVal) {
	SetBit(bVal, SELECTIVE_UPDATE_CONTROLLER);
}

bool NiAVObject::GetSelUpdController() {
	return GetBit(SELECTIVE_UPDATE_CONTROLLER);
}

void NiAVObject::SetSelUpdRigid(bool bVal) {
	SetBit(bVal, SELECTIVE_UPDATE_RIGID);
}

bool NiAVObject::GetSelUpdRigid() {
	return GetBit(SELECTIVE_UPDATE_RIGID);
}

void NiAVObject::SetDisplayObject(bool bVal) {
	SetBit(bVal, DISPLAY_OBJECT);
}

bool NiAVObject::GetDisplayObject() {
	return GetBit(DISPLAY_OBJECT);
}

void NiAVObject::SetDisableSorting(bool bVal) {
	SetBit(bVal, DISABLE_SORTING);
}

bool NiAVObject::GetDisableSorting() {
	return GetBit(DISABLE_SORTING);
}

void NiAVObject::SetSelUpdTransformsOverride(bool bVal) {
	SetBit(bVal, SELECTIVE_UPDATE_TRANSFORMS_OVERRIDE);
}

bool NiAVObject::GetSelUpdTransformsOverride() {
	return GetBit(SELECTIVE_UPDATE_TRANSFORMS_OVERRIDE);
}

void NiAVObject::SetIsNode(bool bVal) {
	SetBit(bVal, IS_NODE);
}

bool NiAVObject::GetIsNode() {
	return GetBit(IS_NODE);
}

void NiAVObject::SetSaveExternalGeomData(bool bVal) {
	SetBit(bVal, SAVE_EXTERNAL_GEOM_DATA);
}

bool NiAVObject::GetSaveExternalGeomData() {
	return GetBit(SAVE_EXTERNAL_GEOM_DATA);
}

void NiAVObject::SetNoDecals(bool bVal) {
	SetBit(bVal, NO_DECALS);
}

bool NiAVObject::GetNoDecals() {
	return GetBit(NO_DECALS);
}

void NiAVObject::SetAlwaysDraw(bool bVal) {
	SetBit(bVal, ALWAYS_DRAW);
}

bool NiAVObject::GetAlwaysDraw() {
	return GetBit(ALWAYS_DRAW);
}

void NiAVObject::SetMeshLOD(bool bVal) {
	SetBit(bVal, MESH_LOD);
}

bool NiAVObject::GetMeshLOD() {
	return GetBit(MESH_LOD);
}

void NiAVObject::SetFixedBound(bool bVal) {
	SetBit(bVal, FIXED_BOUND);
}

bool NiAVObject::GetFixedBound() {
	return GetBit(FIXED_BOUND);
}

void NiAVObject::SetTopFadeNode(bool bVal) {
	SetBit(bVal, TOP_FADE_NODE);
}

bool NiAVObject::GetTopFadeNode() {
	return GetBit(TOP_FADE_NODE);
}

void NiAVObject::SetIgnoreFade(bool bVal) {
	SetBit(bVal, IGNORE_FADE);
}

bool NiAVObject::GetIgnoreFade() {
	return GetBit(IGNORE_FADE);
}

void NiAVObject::SetNoAnimSyncX(bool bVal) {
	SetBit(bVal, NO_ANIM_SYNC_X);
}

bool NiAVObject::GetNoAnimSyncX() {
	return GetBit(NO_ANIM_SYNC_X);
}

void NiAVObject::SetNoAnimSyncY(bool bVal) {
	SetBit(bVal, NO_ANIM_SYNC_Y);
}

bool NiAVObject::GetNoAnimSyncY() {
	return GetBit(NO_ANIM_SYNC_Y);
}

void NiAVObject::SetNoAnimSyncZ(bool bVal) {
	SetBit(bVal, NO_ANIM_SYNC_Z);
}

bool NiAVObject::GetNoAnimSyncZ() {
	return GetBit(NO_ANIM_SYNC_Z);
}

void NiAVObject::SetNoAnimSyncS(bool bVal) {
	SetBit(bVal, NO_ANIM_SYNC_S);
}

bool NiAVObject::GetNoAnimSyncS() {
	return GetBit(NO_ANIM_SYNC_S);
}

void NiAVObject::SetNoDismember(bool bVal) {
	SetBit(bVal, NO_DISMEMBER);
}

bool NiAVObject::GetNoDismember() {
	return GetBit(NO_DISMEMBER);
}

void NiAVObject::SetNoDismemberValidity(bool bVal) {
	SetBit(bVal, NO_DISMEMBER_VALIDITY);
}

bool NiAVObject::GetNoDismemberValidity() {
	return GetBit(NO_DISMEMBER_VALIDITY);
}


void NiAVObject::Update(NiUpdateData& arData) {
	UpdateDownwardPass(arData, 0);
	if (m_pkParent)
		m_pkParent->UpdateUpwardPass();
}

NiProperty* NiAVObject::GetProperty(UInt32 iType) {
	if (iType >= 7) [[unlikely]] {
		return 0;
	}

	NiTListIterator kPos = m_kPropertyList.GetHeadPos();
	while (kPos) {
		NiProperty* pkProperty = m_kPropertyList.GetNext(kPos).m_pObject;
		if (pkProperty && pkProperty->Type() == iType)
			return pkProperty;
	}

	return 0;
}

NiBound* NiAVObject::GetWorldBound() {
	return m_kWorldBound ? m_kWorldBound : NiBound::GetGlobalWorldBound();
}

NiAVObject* NiAVObject::GetObjectByNameEx(const char* apName) {
	if (apName) {
		NiFixedString string = NiFixedString(apName);
		NiAVObject* pChild = GetObjectByName(string);
		return pChild ? pChild : nullptr;
	}
	return nullptr;
}

NiNode* NiAVObject::FindRootNode() {
	NiNode* parent = m_pkParent;
	if (!parent)
		return nullptr;

	while (parent->m_pkParent) {
		parent = parent->m_pkParent;
	}
	return parent;
}

void NiAVObject::AttachProperty(NiPropertyPtr* aspProperty) {
	ThisStdCall(0x439FD0, &m_kPropertyList, aspProperty);
}