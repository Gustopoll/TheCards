#include "settingscontroller.h"

#include "src/Settings/settings.h"

namespace
{
    constexpr char kDelimiter = '/';
    constexpr std::string EmptyString = "";
}

SettingsController::SettingsController() {}

void SettingsController::Load()
{
    RegisterGroup(Settings::General::kGroup, Settings::General::kFilePath,
    {
        {Settings::General::Fullscreen, Settings::General::FullscreenDefault}
    });

    RegisterGroup(Settings::Network::kGroup, Settings::Network::kFilePath,
    {
        {Settings::Network::ServerPort, Settings::Network::ServerPortDefault}
    });
}

void SettingsController::RegisterGroup(
    const std::string& group,
    const std::string& filePath,
    std::vector<std::pair<std::string, std::string>> defaults)
{
    auto& writer = _settings.emplace(group, filePath).first->second;

    for (const auto& [path, defaultValue] : defaults)
        writer.SetSettingDefault(path, defaultValue);

    writer.ReadSettings();

    for (const auto& [path, defaultValue] : defaults)
        _settingChangedEvent.Fire(path, writer.GetSetting(path));
}

void SettingsController::SetSettingValue(const std::string& path, const std::string& value)
{
    const auto& settingsGroup = path.substr(0, path.find_first_of(kDelimiter));

    const auto settingsIter = _settings.find(settingsGroup);
    if (settingsIter == _settings.end())
        return;

    settingsIter->second.SetSetting(path, value);
    _settingChangedEvent.Fire(path, value);
}

const std::string& SettingsController::GetSettingValue(const std::string& path)
{
    const auto& settingsGroup = path.substr(0, path.find_first_of(kDelimiter));

    const auto settingsIter = _settings.find(settingsGroup);
    if (settingsIter == _settings.end())
        return EmptyString;

    return settingsIter->second.GetSetting(path);
}
