#pragma once

#include <string>
#include <unordered_map>

#include "src/Settings/settingswriter.h"
#include "src/Utils/eventhandler.h"

namespace Settings
{

constexpr char GeneralFullscreen[] = "General/Fullscreen";
constexpr char NetworkServerPort[] = "Network/ServerPort";
}


class SettingsController
{
public:
    using SettingChangedEvent = EventHandler<
        //! Path of the setting that was changed.
        const std::string&,
        //! Value of the setting that was changed.
        const std::string&>;

    SettingsController();

    void Load();

    void SetSettingValue(const std::string& path, const std::string& value);

    const std::string& GetSettingValue(const std::string& path);

    SettingChangedEvent::Subscriber& GetSettingChangedEvent()
    {
        return _settingChangedEvent.GetSubscriber();
    }

private:
    std::unordered_map<std::string, SettingsWriter> _settings;

    SettingChangedEvent _settingChangedEvent;
};

