#include "NiBound.hpp"

NiBound NiBound::ms_kDefaultBound = NiBound();

NiBound* NiBound::GetGlobalWorldBound() {
	return &ms_kDefaultBound;
}