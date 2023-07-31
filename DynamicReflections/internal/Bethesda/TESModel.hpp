#pragma once

#include "BaseFormComponent.hpp"
#include "BSString.hpp"

class TESModel : public BaseFormComponent {
public:
	TESModel();
	~TESModel();

	enum
	{
		kFacegenFlag_Head = 0x01,
		kFacegenFlag_Torso = 0x02,
		kFacegenFlag_RightHand = 0x04,
		kFacegenFlag_LeftHand = 0x08,
	};

	virtual void* Destroy(bool noDealloc);	// 04
	virtual char* GetModelPath(void);
	virtual void	SetModelPath(char* path);	// 06

	BSStringT cModel;
	void* pTextures;
	void* pMaterials;
	UInt8 ucFacegenFlags;

	void SetPath(const char* newPath) { cModel.Set(newPath); }
};

ASSERT_SIZE(TESModel, 0x18);