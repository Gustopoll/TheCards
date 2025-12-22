#include "Settings.h"

namespace
{

constexpr char kDeliminer = '/';

}

Settings::Settings(const std::string& name)
{
    const auto splittedName = Tokenize(name, kDeliminer);

    _root = _doc.append_child((splittedName.back() + "Settings").c_str());
    _name = name + ".xml";
}

void Settings::SetSetting(const std::string& path, const std::string& value)
{
    const auto tokens = Tokenize(path, kDeliminer);

    auto node = _root;
    for (const auto& item : tokens)
    {
        pugi::xml_node temp;
        for (const auto& child : node.children())
        {
            if (child.name() == item)
            {
                temp = child;
                break;
            }
        }

        if (temp.empty())
            node = node.append_child(item.c_str());
        else
            node = temp;
    }
    node.text().set(value.c_str());
    _doc.save_file(_name.c_str());
}

void Settings::SetSettingDefault(const std::string& path, const std::string& defaultValue)
{
    _defaultStringValues[path] = defaultValue;
}

const std::string& Settings::GetSetting(const std::string& path)
{
    return _storedStringValues[path];
}

void Settings::ReadSettings()
{
    struct Walker : pugi::xml_tree_walker
    {
        virtual bool for_each(pugi::xml_node& node)
        {
            auto path = node.path(kDeliminer);
            auto index = path.find_first_of(kDeliminer, 1);
            if (index == std::string::npos)
                return true;
            path = path.substr(index + 1, std::string::npos);

            auto value = stringValues.find(path);
            if (value != stringValues.end())
                stringValues[path] = node.text().get();

            return true;
        }

        SettingsStringValues stringValues;;

    };

    pugi::xml_document doc;
    doc.load_file(_name.c_str());
    
    Walker w;
    w.stringValues = _defaultStringValues;
    doc.traverse(w);

    _storedStringValues = w.stringValues;
    
    for (const auto& item : _storedStringValues)
        SetSetting(item.first, item.second);
}

std::vector<std::string> Settings::Tokenize(const std::string& input, const char delimiter)
{
    std::vector<std::string> tokens;
    std::string temporary = input;
    size_t lastPosition = 0;

    while (lastPosition != std::string::npos)
    {
        lastPosition = temporary.find_first_of(delimiter);
        const std::string toStore = temporary.substr(0, lastPosition);

        if (!toStore.empty())
            tokens.push_back(toStore);

        temporary = temporary.substr(lastPosition + 1, std::string::npos);
    }

    return tokens;
}
