#include "BCollection.h"

#include <memory.h>
#include <climits>

namespace Bloodstone
{
	const UInt32 MaxCollectionSize = INT_MAX;
	const UInt32 MaxCollectionDelta = INT_MAX / 2;

	BCollection::BCollection(const char* name, UInt32 limit, UInt32 delta)
		: BObject(name, WP_COLLECTION)
	{
		mDelta = delta;
		if (mDelta > MaxCollectionDelta) {
			mDelta = MaxCollectionDelta;
		}
		if (limit > MaxCollectionSize) {
			limit = MaxCollectionSize;
			mDelta = 0;
		}
		mCount = 0;
		mItens = nullptr;

		if (limit == 0) {
			if (mDelta == 0 && limit != MaxCollectionSize) {
				mDelta = 1;
			}

			SetLimit(mDelta);
		}
		else {
			SetLimit(limit);
		}
	}

	BCollection::~BCollection()
	{
		// TODO free memory
	}

	void* BCollection::operator[](UInt32 index)
	{
		return At(index);
	}

	void* BCollection::At(UInt32 index)
	{
		if (index <= mCount)
		{
			return mItens[index];
		}

		return nullptr;
	}

	UInt32 BCollection::Insert(void* element)
	{
		return IndexInsert(mCount, element);
	}

	UInt32 BCollection::Size()
	{
		return mCount;
	}

	bool BCollection::IndexOf(void* item, UInt32& find)
	{
		for (UInt32 n = 0; n < Size(); n++) {
			if (mItens[n] == item) {
				find = n;

				return true;
			}
		}

		return false;
	}

	void BCollection::Remove(void* item)
	{
		UInt32 index = 0;

		if (IndexOf(item, index)) {
			IndexRemove(index);
		}
	}

	void BCollection::Remove(UInt32 index)
	{
		IndexRemove(index);
	}

	UInt32 BCollection::IndexInsert(UInt32 index, void* element)
	{
		if (index != MaxCollectionSize) {
			if (Increase()) {
				memmove(&mItens[index + 1], &mItens[index], (mCount - index - 1) * sizeof(void*));

				mItens[index] = element;
			}
		}

		return index;
	}

	void BCollection::IndexRemove(UInt32 index)
	{
		if (index < mCount) {
			if (Decrease()) {
				memmove(&mItens[index], &mItens[index + 1], (mCount - index) * sizeof(void*));
			}
		}
	}

	bool BCollection::Increase()
	{
		if (mCount == MaxCollectionSize) {
			return false;
		}

		mCount++;

		if (mCount > mLimit) {
			SetLimit(mLimit + mDelta);
		}

		return true;
	}

	bool BCollection::Decrease()
	{
		if (mCount == 0) {
			return false;
		}

		mCount--;

		return true;
	}

	void BCollection::storeItem(void * item, ostream & os)
	{
		((BObject*)item)->Store(os);
	}

	void BCollection::Load(istream & is)
	{

	}

	void BCollection::Store(ostream & os)
	{
		os.write((char*)&mCount, sizeof(mCount));
		os.write((char*)&mLimit, sizeof(mLimit));
		os.write((char*)&mDelta, sizeof(mDelta));
		for (UInt32 n = 0; n < mCount; n++) {
			storeItem(mItens[n], os);
		}
	}
	/*
	void BCollection::message(ostream & os, const char * mes)
	{
		os.write(mes, sizeof());
	}*/

	void BCollection::SetLimit(UInt32 limit)
	{
		if (mLimit != MaxCollectionSize)
		{
			if (limit > 0) { // увеличение

				if (mLimit != limit) {
					if (limit > MaxCollectionSize) {
						limit = MaxCollectionSize;
					}

					void** newItems = new void*[limit];
					if ((mCount != 0) && (mItens != nullptr)) {
						memcpy(newItems, mItens, mCount * sizeof(void*));
						delete mItens;
					}

					mItens = newItems;
					mLimit = limit;
				}
			}
		}
	}

	BSortedCollection::BSortedCollection(const char* name, UInt32 limit, UInt32 delta, bool duplication)
		: BCollection(name, limit, delta)
	{
		mDuplication = duplication;
	}

	UInt32 BSortedCollection::Insert(void* element)
	{
		UInt32 index;
		if (Search(element, index)) {
			if (!mDuplication) {
				return index;
			}
		}

		IndexInsert(index, element);
		return index;
	}

	void* BSortedCollection::KeyOf(void* item)
	{
		return item;
	}

	bool BSortedCollection::Search(void* item, UInt32& index)
	{
		for (UInt32 n = 0; n < Size(); n++) {
			if (Compare(KeyOf(mItens[n]), KeyOf(item))) {
				index = n;

				return true;
			}
		}

		index = mCount;
		return false;
	}
}
