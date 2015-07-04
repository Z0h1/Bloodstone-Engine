#include "DexConfigFile.h"
#include "DexStringConverter.h"

namespace Dex
{
	ConfigFile::ConfigFile(const String& configfile)
		: CoreObject("CONFIGFILE_" + configfile, WorkPriority::WP_MAIN)
	{
		mFile.open(configfile.c_str(), std:: ios::in);

		if (mFile)
		{
			char lineBuffer[256];
			String line, parametor, value;

			while (!mFile.eof())
			{
				mFile.getline(lineBuffer, 256);
				line += lineBuffer;

				// Пропуск пустых и "#" закоментированых строк
				if (line.length() > 0 && line.at(0) != '#')
				{
					String::size_type separator_pos = line.find_first_of("=", 0);
					if (separator_pos != String::npos)
					{
						// parametor
						parametor = line.substr(0, separator_pos);

						// value
						value = line.substr(separator_pos + 1, line.length());

						// trim
						StringConverter::trim(parametor);
						StringConverter::trim(value);

						mConfigs.push_back(std::make_pair(parametor, value));
					}
				}
			}
		}
		else
		{
			DrawLine("ConfigFile: Файл \"" + configfile + "\" не найден!", MessageTypes::EZ_ERROR);
		}
	}

	ConfigFile::~ConfigFile()
	{
		mFile.close();
	}
}