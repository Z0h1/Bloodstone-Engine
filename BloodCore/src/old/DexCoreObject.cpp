#include "DexCoreObject.h"

namespace DEX
{
	CoreObject::CoreObject(const string& c_name, ofstream* logger, WorkPriority wp, bool fw)
	{
		mObjectName = c_name;
		mWorkPriority = wp;
		mFreeWork = fw;
		mOutFileStream = nullptr;
		SetOutFileStream(logger);
	}

	CoreObject::~CoreObject()
	{
	}

	void CoreObject::SetOutFileStream(ofstream* os)
	{
		if (mOutFileStream != nullptr) {
			*mOutFileStream << "Go to/n";
		}
		
		mOutFileStream = os;
	}

	ofstream* CoreObject::GetOutFileStream()
	{
		return mOutFileStream;
	}

	void CoreObject::DrawLine(const string& text, const MessageTypes& mt)
	{
		if (mOutFileStream != nullptr) {
			char* mt_c = "";
			switch (mt)
			{
			case MessageTypes::NORMAL:
				mt_c = "normal ";
				break;
			case MessageTypes::MT_WARNING:
				mt_c = "warning";
				break;
			case MessageTypes::MT_ERROR:
				mt_c = "error  ";
				break;
			}

			*mOutFileStream << mt_c << " [" << mObjectName << "] " << text.c_str() << endl;
			mOutFileStream->flush();
		}
	}

	const string& CoreObject::GetName()
	{
		return mObjectName;
	}

	WorkPriority CoreObject::GetWP()
	{
		return mWorkPriority;
	}
}