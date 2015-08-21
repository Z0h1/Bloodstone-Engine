#pragma once

#include "DexPreCompletion.h"

template<typename DEXT>
DEXT* DEXArrayNew(DEXUINT count)
{
	DEXT* data = new DEXT[count + 1];
	data[0] = count;
	return ++data;
}

template<typename DEXT>
DEXUINT DEXArrayGetCount(const DEXT* in_dexp)
{
	if (in_dexp) {
		return *(in_dexp - 1);
	}

	return 0;
}

template <typename DEXT>
DEXVOID DEXArrayDelete(DEXT* in_dexp)
{
	if (in_dexp) {
		delete[] --in_dexp;
	}
}

#define DEXARRAYDELETE(type, data) DEXArrayDelete<type>(data); data = nullptr;

template <typename DEXT>
bool DEXArraySearchFirst(DEXT* in_dexp, const DEXT& element, DEXUINT& index)
{
	for (DEXUINT i = 0; i < DEXArrayGetCount<DEXT>(in_dexp); i++)
	{
		if (in_dexp[i] == element) {
			index = i;
			return true;
		}
	}
		
	return false;
}

template <typename DEXT>
bool DEXArraySearchLast(DEXT* in_dexp, const DEXT& element, DEXUINT& index)
{
	for (DEXUINT i = DEXArrayGetCount<DEXT>(in_dexp); i != 0; i--)
	{
		if (in_dexp[i] == element) {
			index = i;
			return true;
		}
	}

	return false;
}

//
//template<typename DEXT>
//class DEXIndexedDynamicArray
//{
//public:
//	DEXIndexedDynamicArray();
//	DEXIndexedDynamicArray(DEXUINT count);
//	~DEXIndexedDynamicArray();
//
//	DEXT& Get(DEXUINT index);
//	const DEXT& Get(DEXUINT index) const;
//
//	DEXT& operator[](DEXUINT index);
//	const DEXT& operator[](DEXUINT index) const;
//
//	bool GetIndex(const DEXT& element, DEXUINT& index);
//
//	const DEXT* GetData(void) const;
//	DEXT* GetData(void);
//
//	bool Insert(const DEXT& element);
//	bool Search(const DEXT& element);
//	bool Remove(const DEXT& element)
//	bool RemoveToIndex(DEXUINT index);
//	void Clear(void);
//	DEXUINT GetCount(void) const;
//
//private:
//	bool ReSizeArray(DEXUINT new_count);
//
//	DEXUINT		mCount;
//	DEXT*		mDATA;
//};
//
//class DEXString;
//
//class D_EXPORT DEXNamedArray
//{
//public:
//	DEXNamedArray();
//};