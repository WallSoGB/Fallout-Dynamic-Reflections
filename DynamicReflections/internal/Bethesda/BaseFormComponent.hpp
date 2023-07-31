#pragma once

class BaseFormComponent {
public:
	BaseFormComponent();
	~BaseFormComponent();

	virtual void	Init(void);
	virtual void	Free(void);
	virtual void	CopyFromBase(BaseFormComponent* component);
	virtual bool	CompareWithBase(BaseFormComponent* src);
};

ASSERT_SIZE(BaseFormComponent, 0x4);