#pragma once

#include "src/Settings/settingswriter.h"
#include "src/Utils/eventhandler.h"

#include <string>
#include <unordered_map>
#include <utility>


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
    //! Registers a settings group, applies defaults, reads from disk and fires
    //! a SettingChangedEvent for every setting in the group.
    void RegisterGroup(
        const std::string& group,
        const std::string& filePath,
        std::vector<std::pair<std::string, std::string>> defaults);

    std::unordered_map<std::string, SettingsWriter> _settings;

    SettingChangedEvent _settingChangedEvent;
};
