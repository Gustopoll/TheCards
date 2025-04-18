#include "clientsettings.h"

quint16 ClientSettings::GetBroadcastPort() const
{
    return _broadcastPort;
}

void ClientSettings::SetBroadcastPort(quint16 broadcastPort)
{
    _broadcastPort = broadcastPort;
}

int ClientSettings::GetTTC() const
{
    return _ttc;
}

void ClientSettings::SetTTC(int ttc)
{
    _ttc = ttc;
}

QString ClientSettings::GetClientName() const
{
    return _clientName;
}

void ClientSettings::SetClientName(const QString& clientName)
{
    _clientName = clientName;
}
