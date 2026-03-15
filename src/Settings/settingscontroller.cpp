#include "settingscontroller.h"

namespace
{

constexpr char kDeliminer = '/';
constexpr std::string EmptyString = "";

constexpr char SettingsGroupGeneral[] = "General";
constexpr char SettingsGroupGeneralPath[] = "Data/Settings/General";

constexpr char SettingsGroupNetwork[] = "Network";
constexpr char SettingsGroupNetworkPath[] = "Data/Settings/Network";
}

SettingsController::SettingsController()
{

}

void SettingsController::Load()
{
    const auto generalIter = _settings.emplace(SettingsGroupGeneral, SettingsGroupGeneralPath).first;
    auto& general = generalIter->second;
    general.SetSettingDefault(Settings::GeneralFullscreen, "false");
    general.ReadSettings();

    const auto networkIter = _settings.emplace(SettingsGroupNetwork, SettingsGroupNetworkPath).first;
    auto& network = networkIter->second;
    network.SetSettingDefault(Settings::NetworkServerPort, "3652");
    network.ReadSettings();

    _settingChangedEvent.Fire(Settings::GeneralFullscreen, general.GetSetting(Settings::GeneralFullscreen));
    _settingChangedEvent.Fire(Settings::NetworkServerPort, network.GetSetting(Settings::NetworkServerPort));
}

void SettingsController::SetSettingValue(const std::string& path, const std::string& value)
{
    const auto& settingsGroup = path.substr(0, path.find_first_of(kDeliminer));

    const auto settingsIter = _settings.find(settingsGroup);
    if (settingsIter == _settings.end())
        return;

    settingsIter->second.SetSetting(path, value);
    _settingChangedEvent.Fire(path, value);
}

const std::string& SettingsController::GetSettingValue(const std::string& path)
{
    const auto& settingsGroup = path.substr(0, path.find_first_of(kDeliminer));

    const auto settingsIter = _settings.find(settingsGroup);
    if (settingsIter == _settings.end())
        return EmptyString;

    return settingsIter->second.GetSetting(path);
}
