#pragma once

#include "NiD3DShader.hpp"
#include "NiDynamicEffectState.hpp"

class NiD3DDefaultShader : public NiD3DShader {
public:
	enum PassFogStatus
	{
		NO_FOG = 0x0,
		BLACK_FOG = 0x1,
		STANDARD_FOG = 0x2,
	};

	void* Unk3C;
	UInt32 m_uiMaxTextureIndex;
	UInt32 m_uiRemainingStages;
	UInt32 m_uiRemainingTextures;
	UInt32 m_uiOldLightingValue;
	NiD3DDefaultShader::PassFogStatus* m_peFogPassArray;
	UInt32 m_uiFogPassArraySize;
	const NiDynamicEffectState* m_pkLastState;
};

ASSERT_SIZE(NiD3DDefaultShader, 0x5C);