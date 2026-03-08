#pragma once
#include <string>
#include <vector>
#include <map>

#include "External/pugixml/pugixml.hpp"

using SettingsStringValues = std::map<std::string, std::string>;

class Settings
{
public:
    Settings(const std::string& name);

    void SetSetting(const std::string& path, const std::string& value);
    
    void SetSettingDefault(const std::string& path, const std::string& defaultValue);
    
    const std::string& GetSetting(const std::string& path);

    void ReadSettings();

private:
    std::vector<std::string> Tokenize(const std::string& input, char delimiter);

    SettingsStringValues _defaultStringValues;
    SettingsStringValues _storedStringValues;


    pugi::xml_document _doc;
    pugi::xml_node _root;
    std::string _name;
};

