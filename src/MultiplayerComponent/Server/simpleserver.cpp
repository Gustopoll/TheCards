#include "simpleserver.h"

#include "MultiplayerComponent/Utility/messageutils.h"

#include <Logger/logger.h>

SimpleServer::SimpleServer()
{
    _tcpServer = std::make_unique<QTcpServer>(this);
    connect(_tcpServer.get(), &QTcpServer::newConnection, this, &SimpleServer::OnNewConnection);
}

bool SimpleServer::StartWaitingInLobby()
{
    if (_state != ServerState::Idle)
        return false;

    const bool isServreRunnig = _tcpServer->listen(QHostAddress::AnyIPv4, _settings.GetPort());

    if (isServreRunnig)
    {
        Log::Multiplayer.LogInfo("SimpleServer::StartWaitingInLobby: Server starts on port: " +
                                  QString::number(_settings.GetPort()));

        _broadcastServer.StartSendingData(
            QHostAddress::Broadcast,
            _settings.GetBroadcastPort(),
            _broadcastData,
            _settings.GetDiscoveryInterval());

        _state = ServerState::WaitingInLobby;
    }
    else
    {
        Log::Multiplayer.LogError("SimpleServer::StartWaitingInLobby: Failed to start server\nReason: " +
                                  _tcpServer->errorString());
    }

    return isServreRunnig;
}

bool SimpleServer::StartCommunication()
{
    if (_state == ServerState::Running)
    {
        Log::Multiplayer.LogError("SimpleServer::StartCommunication: Unable to start communication - "
                                 "communication already started");
        return false;
    }

    Log::Multiplayer.LogInfo("SimpleServer::StartCommunication: Communication started");
    _state = ServerState::Running;
    return true;
}

void SimpleServer::EndServer()
{
    _broadcastServer.StopSendingData();
    _state = ServerState::Idle;

    Log::Multiplayer.LogInfo("SimpleServer::EndServer: Disconnecting all connected clients (" +
                             QString::number(_connectedClients.size()) + ")");

    std::vector<QString> guidsToDisconnect;
    for (const auto& [guid, _] : _connectedClients)
    {
        guidsToDisconnect.emplace_back(guid);
    }

    for (const auto& guid : guidsToDisconnect)
    {
        DisconnectClientByGuid(guid);
    }

    _tcpServer->close();
    Log::Multiplayer.LogInfo("SimpleServer::EndServer: Server ended (" +
                            QString::number(_connectedClients.size()) + " clients)");
}

void SimpleServer::DisconnectClientByName(const QString &clientName)
{
    auto* client = GetClientByName(clientName);

    if (!client)
    {
        Log::Multiplayer.LogError("SimpleServer::DisconnectClientByName: Unable to disconnect client with name '" +
                                  clientName + "' - Client name was not found");
        return;
    }

    client->Disconnect();
    Log::Multiplayer.LogInfo("SimpleServer::DisconnectClientByName: Server disconnected client with name '" +
                             clientName + "'");
}

void SimpleServer::DisconnectClientByGuid(const QString &clientGuid)
{
    const auto client = _connectedClients.find(clientGuid);
    if (client == _connectedClients.end())
    {
        Log::Multiplayer.LogError("SimpleServer::DisconnectClientByGuid: Unable to disconnect client with GUID '" +
                                  clientGuid + "' - Client was not found");
        return;
    }

    client->second->Disconnect();
    Log::Multiplayer.LogInfo("SimpleServer::DisconnectClientByGuid: Server disconnected client with GUID '" +
                             clientGuid + "'");
}

void SimpleServer::SetDiscoveryData(const QJsonObject &data)
{
    _broadcastData = data;
    _broadcastData[kMessageTypePort] = _settings.GetPort();
    _broadcastData[kMessageTypeCurrentPlayers] = static_cast<int32_t>(_connectedClients.size());
    _broadcastData[kMessageTypeMaxPlayers] = _settings.GetMaxPlayers();
    _broadcastData[kMessageTypeServerName] = _settings.GetServerName();
}

void SimpleServer::OnNewConnection()
{
    auto* socket = _tcpServer->nextPendingConnection();
    auto client = std::make_unique<ConnectedClient>(socket);

    client->SetOnReadyReadData(
        [this](const QString& guid, const QJsonObject& data)
        {
            OnReadyReadData(guid, data);
        });

    client->SetOnDisconnected(
        [this](const QString& guid)
        {
            OnClientDisconnect(guid);
        });

    Log::Multiplayer.LogInfo("SimpleServer::OnNewConnection: New client with GUID '" +
                             client->GetGuid() + "' connected but not ready");
    _connectedClients.insert({client->GetGuid(), std::move(client)});
}

void SimpleServer::OnClientDisconnect(const QString& guid)
{
    auto clientIter = _connectedClients.find(guid);
    if (clientIter == _connectedClients.end())
        return;

    const auto function = _callbacks.GetOnConnectedClientDisconnected();
    if (function)
        function(clientIter->second->GetName());

    Log::Multiplayer.LogInfo("SimpleServer::OnClientDisconnect: Client with GUID '" +
                             guid + "' and name '" + clientIter->second->GetName() + "' disconnected from server");

    _connectedClients.erase(guid);
    _broadcastServer.ChangeData(
        kMessageTypeCurrentPlayers,
        static_cast<int32_t>(_connectedClients.size()));
}

void SimpleServer::OnReadyReadData(const QString& guid, const QJsonObject& data)
{
    const auto& clientIter = _connectedClients.find(guid);
    if (clientIter == _connectedClients.end())
    {
        Log::Multiplayer.LogError("SimpleServer::OnReadyReadData: Received message from unknown client\n"
                                  "Data: " + MessageUtils::ToJsonAsString(data));
        return;
    }

    Log::Multiplayer.LogInfo("SimpleServer::OnReadyReadData: Received message from client with GUID '" +
                             guid + "'\nData: " + MessageUtils::ToJsonAsString(data));

    const auto& client = clientIter->second;
    switch (MessageUtils::GetStatusCode(data))
    {
        case StatusCode::RegisterRequest:
        {
            if (client->IsReady())
            {
                client->SendData(_messageBuilder.CreateWelcomeResponseData(
                    WelcomeResponseType::NameAlreadyExists));
                Log::Multiplayer.LogError("SimpleServer::OnReadyReadData: Unable to register client with GUID '" +
                                          guid + "' and name '" + client->GetName() + "' - Client is already registered");
                return;
            }

            const auto futureName = MessageUtils::GetClientName(data);

            if (GetClientByName(futureName))
            {
                client->SendData(_messageBuilder.CreateWelcomeResponseData(
                    WelcomeResponseType::NameAlreadyExists,
                    futureName));
                Log::Multiplayer.LogError("SimpleServer::OnReadyReadData: Unable to register client with GUID '" +
                                          guid + "' - Client name '" + futureName + "' already exist");
                return;
            }

            if (static_cast<int32_t>(_connectedClients.size()) >= _settings.GetMaxPlayers())
            {
                client->SendData(_messageBuilder.CreateWelcomeResponseData(
                    WelcomeResponseType::ServerFull));
                Log::Multiplayer.LogError("SimpleServer::OnReadyReadData: Unable to register client with GUID '" +
                                          guid + "' - Max client (" + QString::number(_settings.GetMaxPlayers()) + ") reached.");
                return;
            }

            client->SetName(futureName);
            client->SendData(_messageBuilder.CreateWelcomeResponseData(
                WelcomeResponseType::Ok));

            Log::Multiplayer.LogInfo("SimpleServer::OnReadyReadData: Client with GUID '" +
                                     guid + "' is succesfull registered with name '" + futureName + "'");
            _broadcastServer.ChangeData(
                kMessageTypeCurrentPlayers,
                static_cast<int32_t>(_connectedClients.size()));
            break;
        }
        case StatusCode::OK:
        {
            const auto function = _callbacks.GetOnReadyReadClientData();
            if (function)
                function(client->GetName(), data);
            break;
        }
        default:
            return;
    }
}

ConnectedClient* SimpleServer::GetClientByName(const QString& clientName)
{
    for (const auto& [guid, client] : _connectedClients)
    {
        if (client->GetName() == clientName)
        {
            return client.get();
        }
    }

    return nullptr;
}
