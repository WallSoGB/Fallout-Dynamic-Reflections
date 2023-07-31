#pragma once

#include "NiShaderConstantMap.hpp"
#include "NiShaderConstantMapEntry.hpp"
#include "NiTArray.hpp"
#include "NiSkinPartition.hpp"
#include "NiTransform.hpp"

class NiD3DRenderState;
class NiD3DShaderProgram;
class NiGeometry;
class NiSkinInstance;
class NiGeometryBufferData;
class NiPropertyState;
class NiDynamicEffectState;

NiSmartPointer(NiD3DShaderConstantMap);

class NiD3DShaderConstantMap : public NiShaderConstantMap {
public:
	virtual NiRTTI GetRTTI();
	virtual void Unk_10();
	virtual void Unk_11();
	virtual void Unk_12();
	virtual void Unk_13();
	virtual void Unk_14();
	virtual void Unk_15();
	virtual void Unk_16();
	virtual void Unk_17();
	virtual void Unk_18();
	virtual void Unk_19();
	virtual void Unk_20();
	virtual void Unk_21();
	virtual void Unk_22();
	virtual void Unk_23();
	virtual void Unk_24();
	virtual NiShaderError AddPredefinedEntry(const char* pszKey, UInt32 uiExtra, UInt32 uiShaderRegister, const char* pszVariableName);
	virtual NiShaderError RemoveEntry(const char* pszKey);
	virtual NiShaderConstantMapEntry*  GetEntry(const char* pszKey);
	virtual int GetEntryAtIndex(UInt32 uiIndex);
	virtual NiShaderError SetShaderConstants(NiD3DShaderProgram* pkShaderProgram, NiGeometry* pkGeometry, NiSkinInstance* pkSkin, NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkBuffData, NiPropertyState* pkState, NiDynamicEffectState* pkEffects, NiTransform* kWorld, NiBound* kWorldBound, UInt32 uiPass, bool bGlobal);
	virtual UInt32 GetEntryIndex(const char* pszKey);
	virtual NiShaderError InsertEntry_0(NiShaderConstantMapEntry* pkEntry);
	virtual NiShaderError InsertEntry(NiShaderConstantMapEntry* pkEntry);
	virtual NiShaderError SetupPredefinedEntry(NiShaderConstantMapEntry* pkEntry);
	virtual NiShaderError SetDefinedConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkBuffData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound, UInt32 uiPass);
	virtual NiShaderError SetConstantConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, UInt32 uiPass);
	virtual NiShaderError SetAttributeConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkBuffData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound, UInt32 uiPass, bool bGlobal, NiExtraData* pkExtraData);
	virtual NiShaderError SetGlobalConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, UInt32 uiPass);
	virtual NiShaderError SetOperatorConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound, UInt32 uiPass);
	virtual NiShaderError SetupObjectEntry(NiShaderConstantMapEntry* pkEntry);
	virtual NiShaderError SetObjectConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkBuffData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound, UInt32 uiPass);

	NiTObjectArray<NiShaderConstantMapEntry> m_aspEntries;
	NiTObjectArray<NiShaderConstantMapEntry> m_aspEntries2;
	bool m_bModified;
	NiD3DShaderProgram* m_pkLastShaderProgram;
	UInt32 m_eLastError;
	LPDIRECT3DDEVICE9 m_pkD3DDevice;
	NiD3DRenderer* m_pkD3DRenderer;
	NiD3DRenderState* m_pkD3DRenderState;
};

ASSERT_SIZE(NiD3DShaderConstantMap, 0x44)