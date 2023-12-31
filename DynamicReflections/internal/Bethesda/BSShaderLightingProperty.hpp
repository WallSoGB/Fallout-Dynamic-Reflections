#pragma once

#include "BSShaderProperty.hpp"
#include "NiTListBase.hpp"

NiSmartPointer(BSShaderLightingProperty);

class BSShaderLightingProperty : public BSShaderProperty {
public:
	BSShaderLightingProperty();
	virtual ~BSShaderLightingProperty();

	virtual void CopyTo2();
	virtual void Unk_31();

	enum ExtraFlags {
		EF_IsPlayer = 0x1,
	};

	NiTListBase<ShadowSceneLight*>		lLightList;
	float								fUnk06C;
	UInt32								uiExtraFlags; // Originally RefID, but unused
	bool								bLightListChanged;
	NiTListItem<ShadowSceneLight*>*		pLastLight; // last processed light?

	CREATE_OBJECT(BSShaderLightingProperty, 0xB71920);

	UInt32				GetActiveLightCount();
	ShadowSceneLight*	GetIlluminatingLight(NiTListItem<ShadowSceneLight*>* apList);
	ShadowSceneLight*	GetNextIlluminatingLight(NiTListItem<ShadowSceneLight*>* apList);
	void				SortLights(NiBound* apObjBound);
};

ASSERT_SIZE(BSShaderLightingProperty, 0x7C);