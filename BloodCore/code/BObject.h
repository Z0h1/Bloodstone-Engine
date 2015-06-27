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
		BObject(const char* name, WorkPriority wp);
		virtual ~BObject();

		//void setOS(ostream os);

		virtual void Load(istream& is) = 0;
		virtual void Store(ostream& os) = 0;

		void DrawLine(ostream& os, const char* text, MessageTypes type = MT_NORMAL);
		const char* GetName();
		WorkPriority GetWP();

	protected:
		const char*	mObjectName;
		WorkPriority	mWP;
	};
}
