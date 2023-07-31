#pragma once

class NiCriticalSection {
public:
	CRITICAL_SECTION m_kCriticalSection;
	UInt32 m_ulThreadOwner;
	UInt32 m_uiLockCount;
};