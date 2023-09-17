#include "NiObjectNET.hpp"

// 0xA5BDD0
NiExtraData* NiObjectNET::GetExtraData(const NiFixedString& kKey) {
	return ThisStdCall<NiExtraData*>(0xA5BDD0, this, &kKey);
}