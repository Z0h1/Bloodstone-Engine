#pragma once

#include "DexPreCompletion.h"

class D_EXPORT DEXString
{
public:
	DEXString();
};

class D_EXPORT DEXCoreObject
{
public:
	DEXCoreObject();
};

namespace DEX
{
	class D_EXPORT CoreObject
	{
	public:
		CoreObject(const string& c_name, ofstream* logger, WorkPriority wp, bool fw = false);
		virtual ~CoreObject();

		void SetOutFileStream(ofstream* os);
		ofstream* GetOutFileStream();

		/*virtual void Load(IFStream* is) = 0;
		virtual void Store(OFStream* os) = 0;*/

		void DrawLine(const string& text, const MessageTypes& mt = NORMAL);
		const string& GetName();
		WorkPriority GetWP();

	protected:
		string			mObjectName;
		WorkPriority	mWorkPriority;
		bool			mFreeWork;
		ofstream*		mOutFileStream;
	};
}
