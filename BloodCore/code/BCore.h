#pragma once

#include "BHead.h"
#include "BObject.h"
#include "BCollection.h"

namespace Bloodstone
{
	class SystemColl : public BSortedCollection
	{
	public:
		SystemColl(const char* name)
			: BSortedCollection(name)
		{

		}

		virtual bool Compare(void* availableElement, void* newElement)
		{
			
			return ((BObject*)availableElement)->GetWP() > ((BObject*)newElement)->GetWP() ? true : false;
		}
	};

	class BLOODCORE_API BCore : public BObject
	{
	public:
		BCore();
		~BCore();

		virtual void Load(istream& is);
		virtual void Store(ostream& os);

	private:
		SystemColl*	mObjects;
	};
}