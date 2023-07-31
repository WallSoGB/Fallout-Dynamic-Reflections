#pragma once

#include "BaseFormComponent.hpp"
#include "tList.hpp"

struct ContainerItemExtra {
	UInt32	owner;
	UInt32	globalOrRequiredRank;
	double	itemCondition;
};

class TESContainer : public BaseFormComponent {
public:
	TESContainer();
	~TESContainer();

	struct FormCount
	{
		SInt32	i_count;			//	00
		TESForm* pForm;			//	04
		ContainerItemExtra* pItemExtra;	//	08
	};

	typedef tList<FormCount> FormCountList;
	FormCountList formCountList;	// 004

	SInt32 GetCountForForm(TESForm* form);
};

ASSERT_SIZE(TESContainer, 0xC);