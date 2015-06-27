#include "BCore.h"
#include "BSRender.h"

namespace Bloodstone
{
	BCore::BCore()
		: BObject("BLOODCORE", WP_MAIN)
	{
		mLogger = new ofstream("log.txt");
		mStateDump = new ofstream("dump.bloodstoneenginedump");
		SetOutFileStream(mLogger);

		mSystems = new SystemColl("SYSTEM_COLLECTION");
		mSystems->SetOutFileStream(mOutFileStream);

		mSystems->Insert(new BSRender(mOutFileStream));

		Store(mStateDump);
	}

	BCore::~BCore()
	{
		mLogger->close();
		mStateDump->close();
	}

	void BCore::Load(ifstream* is)
	{
	}

	void BCore::Store(ofstream* os)
	{
		mSystems->Store(os);
	}
}