#pragma once

#include "DexPreCompletion.h"

namespace Dex
{
	class D_EXPORT CoreObject
	{
	public:
		CoreObject(const String& c_name, WorkPriority wp, bool fw = false);
		virtual ~CoreObject();

		void SetOutFileStream(OFStream* os);

		/*virtual void Load(IFStream* is) = 0;
		virtual void Store(OFStream* os) = 0;*/

		void DrawLine(const String& text, const MessageTypes& mt = NORMAL);
		const String& GetName();
		WorkPriority GetWP();

	protected:
		const String&	mObjectName;
		WorkPriority	mWorkPriority;
		bool			mFreeWork;
		OFStream*		mOutFileStream;
	};
}
