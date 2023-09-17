#include "NiD3DTextureStage.hpp"

// 0xE7DE90
void NiD3DTextureStage::SetClampMode(NiTexturingProperty::ClampMode eClamp) {
	ThisStdCall(0xE7DE90, this, eClamp);
}
