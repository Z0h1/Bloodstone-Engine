#pragma once

namespace Bloodstone
{
	enum MessageTypes
	{
		MT_NORMAL,
		MT_WARNING,
		MT_ERROR
	};

	class BLOODCORE_API BObject
	{
	public:
		BObject(const char* name);
		virtual ~BObject();

		virtual void load(istream& is) = 0;
		virtual void store(ostream& os) = 0;

		void DrawLine(ofstream& os, const char* text, MessageTypes type = MT_NORMAL);
		char* GetName();

	protected:
		char*	mObjectName;
	};
}
