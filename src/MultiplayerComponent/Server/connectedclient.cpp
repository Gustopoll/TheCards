#include "connectedclient.h"

#include <MultiplayerComponent/Utility/Constants.h>
#include "MultiplayerComponent/Utility/messageutils.h"
#include <Logger/logger.h>

ConnectedClient::ConnectedClient(QTcpSocket* socket)
    : _socket(socket)
{
    _guid = QUuid::createUuid();
    connect(socket, &QTcpSocket::readyRead, this, &ConnectedClient::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ConnectedClient::onDisconnected);
}

ConnectedClient::~ConnectedClient()
{
}

void ConnectedClient::SendData(const QJsonObject &data)
{
    if (!_socket->isOpen() || !_socket->isValid())
    {
        Log::Multiplayer.LogError("ConnectedClient::SendData: Cannot sent data to client with name '" +
                                  _name + "' - Invalid socket");
        return;
    }

    const auto jSonData = MessageUtils::ToJsonAsString(data);
    _socket->write(jSonData.toUtf8());
    _socket->flush();
    Log::Multiplayer.LogInfo("ConnectedClient::SendData: Sending data to client with name '" + _name + "'" +
                             "\nData: " + jSonData);
}

void ConnectedClient::Disconnect()
{
    Log::Multiplayer.LogInfo("ConnectedClient::Disconnect: Server disconnected client with name '" +
                             _name + "' from host");
    if (_socket)
    {
        _socket->disconnectFromHost();
        _socket->close();
    }

    _socket = nullptr;
}

void ConnectedClient::onReadyRead()
{
    auto data = MessageUtils::ToJsonObject(_socket->readAll());
    Log::Multiplayer.LogInfo("ConnectedClient::onReadyRead: Recieved data to client with name '" + _name + "'" +
                             "\nData: " + MessageUtils::ToJsonAsString(data));

    if (_onReadyReadClientDataCallback)
        _onReadyReadClientDataCallback(_guid.toString(), data);
}

void ConnectedClient::onDisconnected()
{
    Log::Multiplayer.LogInfo("ConnectedClient::onDisconnected: Client '" + _name + "' was disconnected");
    if (_onDisconnectCallback)
        _onDisconnectCallback(_guid.toString());
}
