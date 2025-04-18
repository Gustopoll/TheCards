#include "serverlistbuilder.h"

#include "MultiplayerComponent/Utility/Constants.h"
#include "MultiplayerComponent/Utility/messageutils.h"

#include <Logger/logger.h>

ServerListBuilder::ServerListBuilder()
{
    connect(&_timer, &QTimer::timeout, this, &ServerListBuilder::OnTimerTimeout);
}

void ServerListBuilder::OnMessageFromServer(const QString &address, quint16 port, const QJsonObject &data)
{
    const auto guid = MessageUtils::GetGuid(data);

    if (!MessageUtils::IsServerRunning(data))
    {
        _serverList.erase(guid);
        Log::Multiplayer.LogInfo("ServerListBuilder::OnMessageFromServer: Server " +
                                 address + ":" + QString::number(port) + " closed");
        return;
    }

    const auto server = _serverList.find(guid);

    // Server is not found in serverList.
    if (server == _serverList.end())
    {
        if (_serverFoundCallback)
            _serverFoundCallback(address, port, data);

        if (_serverList.empty())
            _timer.start(_timerSpeed);

        _serverList[guid] = NetworkData{address, port, data, _ttc};
        Log::Multiplayer.LogInfo("ServerListBuilder::OnMessageFromServer: Found new server " +
                                 address + ":" + QString::number(port) + "\nData: " + MessageUtils::ToJsonAsString(data));
    }
    else
    {
        // Server is found, reset TTC.
        server->second.data = data;
        server->second.ttc = _ttc;
    }
}

void ServerListBuilder::OnTimerTimeout()
{
    for (auto existingServer = _serverList.begin(); existingServer != _serverList.end();)
    {
        // TTC died. Remove existing server from serverList.
        if (existingServer->second.ttc <= 0)
        {
            const auto deadServer = existingServer->second;

            existingServer = _serverList.erase(existingServer);
            Log::Multiplayer.LogInfo("ServerListBuilder::OnTimerTimeout: Server " +
                                     deadServer.address + ":" + QString::number(deadServer.port) +
                                     " is no longer available");
            if (_serverLostCallback)
                _serverLostCallback(deadServer.address, deadServer.port, deadServer.data);
        }
        else
        {
            // Decrease TTC of existing server.
            existingServer->second.ttc--;
            ++existingServer;
        }

        if (_serverList.empty())
            _timer.stop();
    }
}
