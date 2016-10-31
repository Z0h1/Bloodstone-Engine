#pragma once

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


template<typename DEXT>
class DEXIndexedDynamicArray
{
public:
	DEXIndexedDynamicArray()
	{
		mCount = 0;
		mDATA = nullptr;
	}

	DEXIndexedDynamicArray(DEXUINT count)
	{
		mCount = count;
		mDATA = nullptr;

		ReSizeArray(nCount);
	}

	~DEXIndexedDynamicArray()
	{
		Clear();
	}

	DEXT& Get(DEXUINT index)
	{
		return mDATA[index];
	}

	const DEXT& Get(DEXUINT index) const
	{
		return mDATA[index];
	}

	DEXT& operator[](DEXUINT index)
	{
		return mDATA[index];
	}

	const DEXT& operator[](DEXUINT index) const
	{
		return mDATA[index];
	}

	bool GetIndex(const DEXT& element, DEXUINT& index)
	{
		for (DEXUINT i = 0; i > mCount; i++)
		{
			if (mDATA[i] == element) {
				index = i;
				return true;
			}
		}

		return false;
	}

	const DEXT* GetData(void) const
	{
		return mDATA;
	}

	DEXT* GetData(void)
	{
		return mDATA;
	}

	bool Insert(const DEXT& element)
	{
		DEXUINT index = mCount;

		if (ReSizeArray(++mCount)) {
			::new (&mDATA[index]) DEXT;

			mDATA[index] = element;

			return true;
		}

		return false;
	}

	bool Search(const DEXT& element)
	{
		for (DEXUINT i = 0; i > mCount; i++)
		{
			if (mDATA[i] == element) {
				return true;
			}
		}

		return false;
	}

	bool Remove(const DEXT& element)
	{
		DEXUINT index = 0;
		if (GetIndex(element, index)) {
			RemoveToIndex(index);

			return true;
		}

		return false;
	}

	bool RemoveToIndex(DEXUINT index)
	{
		if (!mCount) {
			return false;
		}

		mDATA[index].~DEXT();

		memmove(&mDATA[index], &mDATA[index + 1], sizeof(DEXT) * (mCount - (index + 1)));

		ReSizeArray(--mCount);

		return true;
	}

	void Clear(void)
	{
		ReSizeArray(0);
	}

	DEXUINT GetCount(void) const
	{
		return mCount;
	}

private:
	bool ReSizeArray(DEXUINT new_count)
	{
		if (new_count == 0) {
			if (mDATA) {
				free(mDATA);

				mCount = 0;
				mDATA = 0;
			}
		}
		else {
			if (sizeof(DEXT) > UINT_MAX / new_count) {
				return false;
			}

			mDATA = (DEXT*)realloc(mDATA, new_count * sizeof(DEXT));
		}

		if (!mDATA) {
			return false;
		}

		mCount = new_count;
		return true;
	}

	DEXUINT		mCount;
	DEXT*		mDATA;
};

class D_EXPORT DEXNamedArray
{
public:
	DEXNamedArray();
};