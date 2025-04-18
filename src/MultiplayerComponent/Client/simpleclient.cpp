#include "simpleclient.h"

#include "MultiplayerComponent/Utility/messageutils.h"

#include <Logger/logger.h>

SimpleClient::SimpleClient()
{
    _broadcastClient = std::make_unique<BroadcastClient>();
    _broadcastClient->SetOnReadyReadData(
        [this](const QString &ipAddress, quint16 port, const QJsonObject &data)
        {
            OnReadyReadBroadcastData(ipAddress, port, data);
        }
    );

    _socket = new QTcpSocket(this);
    connect(_socket, &QTcpSocket::connected, this, &SimpleClient::OnConnected);
    connect(_socket, &QTcpSocket::disconnected, this, &SimpleClient::OnDisconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &SimpleClient::OnReadyReadData);
}

void SimpleClient::Connect(const QString &ipAddress, quint16 port)
{
    if (!_serverAddress.isEmpty())
    {
        Log::Multiplayer.LogError("SimpleClient::Connect: Failed to connect - Client is already connected to " +
                                  _serverAddress + ":" + QString::number(_serverPort));
        return;
    }

    Log::Multiplayer.LogInfo("SimpleClient::Connect: Trying to connect to " +
                             _serverAddress + ":" + QString::number(_serverPort));
    _serverAddress = ipAddress;
    _serverPort = port;
    _socket->connectToHost(ipAddress, port);
}

void SimpleClient::Disconnect()
{
    // Reset server settings
    _serverAddress.clear();
    _serverPort = 0;

    _socket->disconnectFromHost();
    _state = ClientState::NotConnected;
    Log::Multiplayer.LogInfo("SimpleClient::Disconnect: Client disconnected");
}

void SimpleClient::SendData(const QJsonObject& data)
{
    if (!_socket->isOpen() || !_socket->isValid())
        return;

    const auto jSonData = MessageUtils::ToJsonAsString(data);
    _socket->write(jSonData.toUtf8());
    _socket->flush();
    Log::Multiplayer.LogInfo("SimpleClient::SendMessage: Message sent\nData: " + jSonData);
}

bool SimpleClient::StartFindindServers()
{
    _serverListBuilder.SetOnServerFoundCallback(_callbacks.GetServerFound());
    _serverListBuilder.SetOnServerLostCallback(_callbacks.GetServerLost());
    _serverListBuilder.SetTTC(_settings.GetTTC());

    Log::Multiplayer.LogInfo("SimpleClient::StartFindindServers: Start of finding servers at port " +
                             QString::number(_settings.GetBroadcastPort()) + " and TTC " +
                             QString::number(_settings.GetTTC()));
    return _broadcastClient->Bind(QHostAddress::AnyIPv4, _settings.GetBroadcastPort());
}

void SimpleClient::StopFindingServers()
{
    _broadcastClient->Close();
}

const ServerList &SimpleClient::GetAllAvailableServers()
{
    return _serverListBuilder.GetServerList();
}

void SimpleClient::OnReadyReadBroadcastData(const QString &ipAddress, quint16 port, const QJsonObject &data)
{
    _serverListBuilder.OnMessageFromServer(ipAddress, port, data);

    const auto function = _callbacks.GetReadyReadBroadcastData();
    if (function)
        function(ipAddress, port, data);
}

void SimpleClient::OnConnected()
{
    _state = ClientState::ConnectedNotReady;
    Log::Multiplayer.LogInfo("SimpleClient::OnConnected: Connected but not ready");

    // Send welcome message (first message after connection)
    SendData(_messageBuilder.CreateWelcomeData(_settings.GetClientName()));
}

void SimpleClient::OnDisconnected()
{
    _state = ClientState::NotConnected;
    Log::Multiplayer.LogInfo("SimpleClient::OnDisconnected: Disconnected");

    if (const auto function = _callbacks.GetClientDisconnected())
        function();
}

void SimpleClient::OnReadyReadData()
{
    auto data = MessageUtils::ToJsonObject(_socket->readAll());

    Log::Multiplayer.LogInfo("SimpleClient::OnReadyReadData: \nData: " + MessageUtils::ToJsonAsString(data));

    const auto printError = [this, statusCode = MessageUtils::GetStatusCode(data)](ClientState expectState)
    {
        Log::Multiplayer.LogError("SimpleClient::OnReadyReadData: Invalid message state ["+
                                  QString::number((int)statusCode) + "] for client state [" +
                                  QString::number(static_cast<int>(_state)) + "] expected state is [" +
                                  QString::number(static_cast<int>(expectState)) + "]");
    };

    switch (MessageUtils::GetStatusCode(data)) {
        case StatusCode::OK:
        {
            if (_state != ClientState::Connected)
            {
                printError(ClientState::Connected);
                return;
            }

            if (const auto function = _callbacks.GetReadyReadData())
                function(_serverAddress, _serverPort, data);
            break;
        }
        case StatusCode::Error:
        {
            if (const auto function = _callbacks.GetErrorFromServer())
                function(MessageUtils::GetErrorString(data));
            break;
        }
        case StatusCode::RegisterRequestBad:
        {
            if (_state != ClientState::ConnectedNotReady)
            {
                printError(ClientState::ConnectedNotReady);
                return;
            }

            Disconnect();
            if (const auto function = _callbacks.GetErrorFromServer())
                function(MessageUtils::GetErrorString(data));
            break;
        }
        case StatusCode::RegisterResponseGood:
        {
            if (_state != ClientState::ConnectedNotReady)
            {
                printError(ClientState::ConnectedNotReady);
                return;
            }

            _state = ClientState::Connected;
            Log::Multiplayer.LogInfo("SimpleClient::OnReadyReadData: Connected - registered");
            const auto function = _callbacks.GetClientConnected();
            if (function)
                function();
            break;
        }
        default:
            return;
    }
}

