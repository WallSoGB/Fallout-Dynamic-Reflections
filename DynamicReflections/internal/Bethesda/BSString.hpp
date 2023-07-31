#pragma once

// Technically it should be a template but I'm lazy
class BSStringT {
public:
	BSStringT();
	~BSStringT();

	char* pString;
	UInt16 usLen;
	UInt16 usMaxLen;

	bool		Set(const char* src);
	bool		Includes(const char* toFind) const;
	bool		Replace(const char* toReplace, const char* replaceWith); // replaces instance of toReplace with replaceWith
	bool		Append(const char* toAppend);
	double		Compare(const BSStringT& compareTo, bool caseSensitive = false);

	UInt32		GetLength();

	const char* CStr(void);
};

typedef BSStringT String;