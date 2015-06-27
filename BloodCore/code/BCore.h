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

		virtual void Load(ifstream* is);
		virtual void Store(ofstream* os);

	private:
		SystemColl*	mSystems;

		ofstream*	mLogger;
		ofstream*	mStateDump;
	};
}