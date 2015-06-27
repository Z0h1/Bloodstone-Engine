#pragma once
#define _BLOODSTONE_COLLECTION

#include "BHead.h"
#include "BObject.h"

namespace Bloodstone
{
	class BLOODCORE_API BCollection : public BObject
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

		virtual void Load(istream& is);
		virtual void Store(ostream& os);

		//virtual void message(ostream& os, const char* mes);

	protected:
		void SetLimit(UInt32 limit);
		UInt32 IndexInsert(UInt32 index, void* element);
		void IndexRemove(UInt32 index);
		bool IndexOf(void* item, UInt32& find);

		bool Increase();
		bool Decrease();

		void storeItem(void* item, ostream& os);

		UInt32 mCount;
		UInt32 mDelta;
		UInt32 mLimit;
		void** mItens;
	};

	class BLOODCORE_API BSortedCollection : public BCollection
	{
	public:
		BSortedCollection(const char* name, UInt32 limit = 0, UInt32 delta = 1, bool duplication = true);

		virtual UInt32 Insert(void* element);

		virtual void* KeyOf(void* item);
		virtual bool Compare(void* availableElement, void* newElement) = 0;

	protected:
		bool Search(void* item, UInt32& index);

		bool mDuplication;
	};
}