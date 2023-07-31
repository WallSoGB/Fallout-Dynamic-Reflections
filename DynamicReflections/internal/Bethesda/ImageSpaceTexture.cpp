#include "ImageSpaceTexture.hpp"

ImageSpaceTexture::~ImageSpaceTexture() {
    if (bAcquiredTarget)
        Reset();

    // Game decreases the refcount *and* resets the pointer. Normal destructor does not do that.
    NiObject* pTexture = spTexture;
    if (pTexture) {
        if (!InterlockedDecrement(&pTexture->m_uiRefCount))
            pTexture->DeleteThis();
        spTexture.m_pObject = 0;
    }
    pTexture = spTexture;
    if (pTexture) {
        if (!InterlockedDecrement(&pTexture->m_uiRefCount))
            pTexture->DeleteThis();
    }
}
