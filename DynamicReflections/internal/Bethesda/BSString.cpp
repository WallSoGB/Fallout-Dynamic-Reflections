#include "BSString.hpp"
#include "MemoryManager.hpp"

BSStringT::BSStringT() : pString(NULL), usLen(0), usMaxLen(0) {}

BSStringT::~BSStringT() {
	if (pString) {
		MemoryManager::Deallocate(pString);
		pString = NULL;
	}
	usMaxLen = usLen = 0;
}