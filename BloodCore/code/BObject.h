#pragma once

#include "BHead.h"

namespace Bloodstone
{
	enum MessageTypes
	{
		MT_NORMAL,
		MT_WARNING,
		MT_ERROR
	};

	enum WorkPriority
	{
		// TODO tharde
		WP_MAIN,
		WP_COLLECTION,
		WP_SYSTEM,
		WP_STEP_1,
		WP_STEP_2,
		WP_STEP_3,
		WP_STEP_4,
		WP_END
	};

	class BLOODCORE_API BObject
	{
	public:
		BObject(const char* name, WorkPriority wp, bool fw = false);
		virtual ~BObject();

		void SetOutFileStream(ofstream* os);

		virtual void Load(ifstream* is) = 0;
		virtual void Store(ofstream* os) = 0;

		void DrawLine(const char* text, MessageTypes mt = MT_NORMAL);
		const char* GetName();
		WorkPriority GetWP();

	protected:
		const char*		mObjectName;
		WorkPriority	mWorkPriority;
		bool			mFreeWork;
		ofstream*		mOutFileStream;
	};
}
