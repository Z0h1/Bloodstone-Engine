#include "DexConfigFile.h"
#include "DexStringConverter.h"

namespace Dex
{
	ConfigFile::ConfigFile(const string& configfile, ofstream* logger)
		: CoreObject("CONFIGFILE_" + configfile, logger, WorkPriority::WP_MAIN)
	{
		mFile.open(configfile,  ios::in);

		if (mFile)
		{
			char lineBuffer[256];
			string line, parametor, value;

			while (!mFile.eof())
			{
				mFile.getline(lineBuffer, 256);
				line = lineBuffer;

				// ������� ������ � "#" ���������������� �����
				if (line.length() > 0 && line.at(0) != '#')
				{
					string::size_type separator_pos = line.find_first_of("=", 0);
					if (separator_pos != string::npos)
					{
						// parametor
						parametor = line.substr(0, separator_pos);

						// value
						value = line.substr(separator_pos + 1, line.length());

						// trim
						StringConverter::trim(parametor);
						StringConverter::trim(value);

						mConfigs.push_back(make_pair(parametor, value));
					}
				}
			}
		}
		else
		{
			DrawLine("ConfigFile: ���� \"" + configfile + "\" �� ������!", MessageTypes::MT_ERROR);
		}
	}

	ConfigFile::~ConfigFile()
	{
		mFile.close();
	}
}