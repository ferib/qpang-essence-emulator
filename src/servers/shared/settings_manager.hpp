#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "database.hpp"
#include "logger.hpp"
#include <string>
#include <map>
#include "boost/format.hpp"

class SettingsManager {

public:
	SettingsManager() {}
	~SettingsManager() {}

	static SettingsManager* Instance()
	{
		static SettingsManager settings;
		return &settings;
	}

	void Initialize()
	{
		Database database{};
		auto result = database.storeQuery("SELECT * FROM settings");

		if (result)
		{
			sLogger->Get()->info("Loading server settings");
			do
			{
				std::string key = result->getString("key");
				std::string value = result->getString("value");
				_settings[key] = value;
				//_settings.insert_or_assign(key, value);

				result->next();
		
			} while (result->hasNext());

			sLogger->Get()->debug("Loaded following server settings:");
			for (auto pair : _settings)
			{
				sLogger->Get()->debug("Key: {0} Value: {1}", pair.first, pair.second);
			}
		}
		database.Close();
	}

	std::string GetSetting(std::string key)
	{
		if (!_settings.size())
			return std::string();
		
		auto value = _settings.find(key);
		if (value != _settings.cend())
		{
			return value->second;
		}
		else
		{
			sLogger->Get()->error("Requested key setting {0} is not available", key);
		}

		return std::string();
	}


private:
	std::map<std::string, std::string> _settings;
};

#define sSettings SettingsManager::Instance()

#endif // !SETTINGS_HPP