//#pragma once
//
//#include "DexPreCompletion.h"
//#include <cstring>
//
//class D_EXPORT DEXString
//{
//public:
//	DEXString();
//	DEXString(const DEXString* in_pdexstring);
//	DEXString(const string in_stdstring);
//	DEXString(const char* in_pchar);
//	DEXString(const wchar_t* in_pwchar);
//
//	~DEXString();
//
//	void operator += (const DEXString* in_pdexstring);
//	void operator += (const char* in_pchar);
//
//	void operator = (const DEXString* in_pdexstring);
//	void operator = (const char* in_pchar);
//
//	const DEXCHAR* Get() const;
//
//	DEXUINT GetCount() const;
//
//private:
//	string		mSTDString;
//};