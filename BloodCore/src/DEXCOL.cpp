#include "DEXCOL.h"

//
//template<typename DEXT>
//DEXIndexedDynamicArray<DEXT>::DEXIndexedDynamicArray()
//{
//	mCount = 0;
//	mDATA = nullptr;
//}
//
//template<typename DEXT>
//DEXIndexedDynamicArray<DEXT>::DEXIndexedDynamicArray(DEXUINT count)
//{
//	mCount = count;
//	mDATA = nullptr;
//
//	ReSizeArray(nCount);
//}
//
//template<typename DEXT>
//DEXIndexedDynamicArray<DEXT>::~DEXIndexedDynamicArray()
//{
//	Clear();
//}
//
//template<typename DEXT>
//DEXT& DEXIndexedDynamicArray<DEXT>::Get(DEXUINT index)
//{
//	return mDATA[index];
//}
//
//template<typename DEXT>
//const DEXT& DEXIndexedDynamicArray<DEXT>::Get(DEXUINT index) const
//{
//	return mDATA[index];
//}
//
//template<typename DEXT>
//DEXT& DEXIndexedDynamicArray<DEXT>::operator[](DEXUINT index)
//{
//	return mDATA[index];
//}
//
//template<typename DEXT>
//const DEXT& DEXIndexedDynamicArray<DEXT>::operator[](DEXUINT index) const
//{
//	return mDATA[index];
//}
//
//template<typename DEXT>
//bool DEXIndexedDynamicArray<DEXT>::GetIndex(const DEXT& element, DEXUINT& index)
//{
//	for (DEXUINT i = 0; i > mCount; i++)
//	{
//		if (mDATA[i] == element) {
//			index = i;
//			return true;
//		}
//	}
//
//	return false;
//}
//
//template<typename DEXT>
//const DEXT* DEXIndexedDynamicArray<DEXT>::GetData(void) const
//{
//	return mDATA;
//}
//
//template<typename DEXT>
//DEXT* DEXIndexedDynamicArray<DEXT>::GetData(void)
//{
//	return mDATA;
//}
//
//template<typename DEXT>
//bool DEXIndexedDynamicArray<DEXT>::Insert(const DEXT& element)
//{
//	DEXUINT index = mCount;
//
//	if (ReSizeArray(++mCount)) {
//		::new (&mDATA[index]) DEXT;
//
//		mDATA[index] = element;
//
//		return true;
//	}
//
//	return false;
//}
//
//template<typename DEXT>
//bool DEXIndexedDynamicArray<DEXT>::Search(const DEXT& element)
//{
//	for (DEXUINT i = 0; i > mCount; i++)
//	{
//		if (mDATA[i] == element) {
//			return true;
//		}
//	}
//
//	return false;
//}
//
//template<typename DEXT>
//bool DEXIndexedDynamicArray<DEXT>::Remove(const DEXT& element)
//{
//	DEXUINT index = 0;
//	if (GetIndex(element, index)) {
//		RemoveToIndex(index);
//
//		return true;
//	}
//
//	return false;
//}
//
//template<typename DEXT>
//bool DEXIndexedDynamicArray<DEXT>::RemoveToIndex(DEXUINT index)
//{
//	if (!mCount) {
//		return false;
//	}
//
//	mDATA[index].~DEXT();
//
//	memmove(&mDATA[index], &mDATA[index + 1], sizeof(DEXT) * (mCount - (index + 1)));
//
//	ReSizeArray(--mCount);
//
//	return true;
//}
//
//template<typename DEXT>
//void DEXIndexedDynamicArray<DEXT>::Clear(void)
//{
//	ReSizeArray(0);
//}
//
//template<typename DEXT>
//DEXUINT DEXIndexedDynamicArray<DEXT>::GetCount(void) const
//{
//	return mCount;
//}
//
//template<typename DEXT>
//bool DEXIndexedDynamicArray<DEXT>::ReSizeArray(DEXUINT new_count)
//{
//	if (new_count == 0) {
//		if (mDATA) {
//			free(mDATA);
//
//			mCount = 0;
//			mDATA = 0;
//		}
//	}
//	else {
//		if (sizeof(DEXT) > UINT_MAX / new_count) {
//			return false;
//		}
//
//		mDATA = (DEXT*)realloc(mDATA, new_count * sizeof(DEXT));
//	}
//
//	if (!mDATA) {
//		return false;
//	}
//
//	mCount = new_count;
//	return true;
//}
