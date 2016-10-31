#include "DEXString.h"

// DEXString class implementation

DEXString::DEXString()
{
}

DEXString::DEXString(const DEXString* in_pdexstring)
{
	//mSTDString = in_pdexstring.;
}

DEXString::DEXString(const string in_stdstring)
{
	mSTDString = in_stdstring;
}

DEXString::DEXString(const char* in_pchar)
{
	mSTDString = in_pchar;
}

DEXString::DEXString(const wchar_t* in_pwchar)
{
	//mSTDString = in_pwchar;
}

DEXString::~DEXString()
{
	mSTDString.clear();
}

void DEXString::operator += (const DEXString* in_pdexstring)
{
	//mSTDString += in_pdexstring;
}

void DEXString::operator += (const char* in_pchar)
{
	mSTDString += in_pchar;
}

void DEXString::operator = (const DEXString* in_pdexstring)
{
	//mSTDString = in_pdexstring;
}

void DEXString::operator = (const char* in_pchar)
{
	mSTDString = in_pchar;
}

const DEXCHAR* DEXString::Get() const
{
	return mSTDString.data();
}

DEXUINT DEXString::GetCount() const
{
	return mSTDString.size();
}