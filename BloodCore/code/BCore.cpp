#include "BCore.h"
#include "BSRender.h"

namespace Bloodstone
{
	BCore::BCore()
		: BObject("BLOODCORE", WP_MAIN)
	{
		mObjects = new SystemColl("SYSTEM_COLLECTION");
		mObjects->Insert(new BSRender());

		ofstream os("log.txt");
		Store(os);
		os.close();
	}

	BCore::~BCore()
	{
	}

	void BCore::Load(istream & is)
	{
	}

	void BCore::Store(ostream & os)
	{
		mObjects->Store(os);
	}
}