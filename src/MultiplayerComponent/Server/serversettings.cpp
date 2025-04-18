#include "serversettings.h"

int ServerSettings::GetTTS() const
{
    return _tts;
}

void ServerSettings::SetTTS(const int tts)
{
    _tts = tts;
}

int ServerSettings::GetDiscoveryInterval() const
{
    return _discoveryInterval;
}

void ServerSettings::SetDiscoveryInterval(const int discoveryInterval)
{
    _discoveryInterval = discoveryInterval;
}

quint16 ServerSettings::GetBroadcastPort() const
{
    return _broadcastPort;
}

void ServerSettings::SetBroadcastPort(const quint16 broadcastPort)
{
    _broadcastPort = broadcastPort;
}

quint16 ServerSettings::GetPort() const
{
    return _port;
}

void ServerSettings::SetPort(const quint16 port)
{
    _port = port;
}

int32_t ServerSettings::GetMaxPlayers() const
{
    return _maxPlayers;
}

void ServerSettings::SetMaxPlayers(const int32_t maxPlayers)
{
    _maxPlayers = maxPlayers;
}

QString ServerSettings::GetServerName() const
{
    return _serverName;
}

void ServerSettings::SetServerName(const QString& serverName)
{
    _serverName = serverName;
}
