#pragma once
#define _BLOODSTONE_COLLECTION

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT BCollection : public CoreObject
	{
	public:
		BCollection(const char* name, UInt32 limit, UInt32 delta);
		virtual ~BCollection();

		void* operator[](UInt32 index);
		void* At(UInt32 index);

		virtual UInt32 Insert(void* element);
		UInt32 Size();

		void Remove(void* item);
		void Remove(UInt32 index);

		virtual void Load(IFStream* is);
		virtual void Store(OFStream* os);

		bool IndexOf(void* item, UInt32& find);

	protected:
		void SetLimit(UInt32 limit);
		UInt32 IndexInsert(UInt32 index, void* element);
		void IndexRemove(UInt32 index);

		bool Increase();
		bool Decrease();

		void StoreItem(void* item, OFStream* os);

		UInt32 mCount;
		UInt32 mDelta;
		UInt32 mLimit;
		void** mItens;
	};

	class D_EXPORT BSortedCollection : public BCollection
	{
	public:
		BSortedCollection(const char* name, UInt32 limit = 0, UInt32 delta = 1, bool duplication = true);

		virtual UInt32 Insert(void* element);

		virtual void* KeyOf(void* item);
		virtual bool Compare(void* availableElement, void* newElement) = 0;

		bool Search(void* item, UInt32& index);

	protected:
		bool mDuplication;
	};
}