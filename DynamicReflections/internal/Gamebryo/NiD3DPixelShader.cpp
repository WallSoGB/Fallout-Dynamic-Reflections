#include "NiD3DPixelShader.hpp"

NiD3DPixelShader* NiD3DPixelShader::Create(NiDX9Renderer* apRenderer) {
    return NiCreate<NiD3DPixelShader, 0xBE08F0>(apRenderer);
}
