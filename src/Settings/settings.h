#pragma once

namespace Settings
{

namespace General
{
    constexpr auto kGroup = "General";
    constexpr auto kFilePath = "Data/Settings/General";

    constexpr auto Fullscreen = "General/Fullscreen";
    constexpr auto FullscreenDefault = "false";
}

namespace Network
{
    constexpr auto kGroup = "Network";
    constexpr auto kFilePath = "Data/Settings/Network";

    constexpr auto ServerPort = "Network/ServerPort";
    constexpr auto ServerPortDefault = "3652";
}

} // namespace Settings
