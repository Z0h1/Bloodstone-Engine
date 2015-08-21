#pragma once

#include "DexPreCompletion.h"

DEXUINT D_EXPORT DEXStrLen(
	const DEXPCHAR in_pdexchar
);

// TODO не работает выход за пределы массива как и в случаи с strcpy_s,
// потому что нельзя получить размера неопределенного массива DEXPCHAR out_pdexchar.
DEXVOID D_EXPORT DEXStrCpy(
	DEXPCHAR out_pdexchar,
	const DEXPCHAR in_pdexchar
);
DEXVOID D_EXPORT DEXStrCpy(
	DEXPCHAR out_pdexchar,
	DEXUINT in_buffer,
	const DEXPCHAR in_pdexchar
);

class D_EXPORT DEXString
{
public:
	DEXString();
	DEXString(const DEXString* in_pdexstring);
	//DEXString(const DEXCHAR* in_pdexchar);
	DEXString(const DEXPCHAR in_pchar);
	DEXString(const wchar_t* in_pwchar);

	~DEXString();

	void operator += (const DEXString* in_pdexstring);

	DEXPCHAR Get() const { return mStrng; }

private:
	bool ResizeString(DEXUINT new_size);

	DEXUINT		mSize;
	DEXPCHAR	mStrng;
};