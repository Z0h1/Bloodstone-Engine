#include "DEXString.h"

DEXUINT DEXStrLen(const DEXPCHAR in_pdexchar)
{
	DEXUINT size_in_pchar = 0;
	while (in_pdexchar[size_in_pchar])
	{
		size_in_pchar++;
	}

	return size_in_pchar;
}

DEXVOID DEXStrCpy(DEXPCHAR out_pdexchar, const DEXPCHAR in_pdexchar)
{
	DEXStrCpy(out_pdexchar, DEXStrLen(in_pdexchar), in_pdexchar);
}

DEXVOID DEXStrCpy(DEXPCHAR out_pdexchar, DEXUINT in_buffer, const DEXPCHAR in_pdexchar)
{
	DEXUINT n = 0;
	for (; n < in_buffer; n++)
	{
		out_pdexchar[n] = in_pdexchar[n];
	}

	out_pdexchar[n] = '\0';
}

DEXString::DEXString()
{
	mSize = 0;
}

DEXString::DEXString(const DEXString* in_pdexstring)
{

}

//DEXString::DEXString(const DEXCHAR* in_pdexchar)
//{
//
//}

DEXString::DEXString(const DEXPCHAR in_pchar)
{
	mStrng = nullptr;
	mSize = 0;

	ResizeString(DEXStrLen(in_pchar));

	DEXStrCpy(mStrng, mSize, in_pchar);

	char string[80];
	strcpy_s(string, "Hello world from ");
	strcat_s(string, "strcpy_s ");
}

DEXString::DEXString(const wchar_t* in_pwchar)
{

}

DEXString::~DEXString()
{

}

void DEXString::operator += (const DEXString* in_pdexstring)
{

}

bool DEXString::ResizeString(DEXUINT new_size)
{
	if (new_size == mSize) {
		return false;
	}

	DEXCHAR* new_string = new DEXCHAR[new_size];

	if (mStrng) {
		memcpy(new_string, mStrng, mSize * sizeof(DEXCHAR));
		delete[] mStrng;
	}

	mSize = new_size;
	mStrng = new_string;

	return true;
}