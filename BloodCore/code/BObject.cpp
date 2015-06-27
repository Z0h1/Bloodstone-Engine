#include "BObject.h"

namespace Bloodstone
{
	/*BObject::BObject()
	{
	os << "<html>" << endl;
	os << "<head>" << endl;
	os << "<title>Work log</title>" << endl;
	os << "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">" << endl;
	os << "</head>" << endl;
	os << "<body>" << endl;
	os << "<div class=\"header\"><b>Hailstorm Engine - Work log</b></div>" << endl;
	}*/

	BObject::BObject(const char * name, WorkPriority wp, bool fw)
	{
		mObjectName = name;
		mWorkPriority = wp;
		mFreeWork = fw;
		mOutFileStream = nullptr;
	}

	BObject::~BObject()
	{
	}

	void BObject::SetOutFileStream(ofstream* os)
	{
		if (mOutFileStream != nullptr) {
			char* ms = "Go to/n";
			mOutFileStream->write(ms, sizeof(ms));
		}
		
		mOutFileStream = os;
	}

	void BObject::DrawLine(const char* text, MessageTypes mt)
	{
		if (mOutFileStream != nullptr) {
			string ms;

			switch (mt)
			{
			case MT_NORMAL:
				ms += "normal";
				break;
			case MT_WARNING:
				ms += "warning";
				break;
			case MT_ERROR:
				ms += "error";
				break;
			}

			ms += "--";
			ms += mObjectName;
			ms += "--";
			ms += text;
			ms += "\n";

			mOutFileStream->write(ms.c_str(), ms.size());
			mOutFileStream->flush();
		}
	}

	const char * BObject::GetName()
	{
		return mObjectName;
	}

	WorkPriority BObject::GetWP()
	{
		return mWorkPriority;
	}
}