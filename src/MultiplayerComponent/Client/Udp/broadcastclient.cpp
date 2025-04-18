#include "broadcastclient.h"

#include "MultiplayerComponent/Utility/messageutils.h"

#include <Logger/logger.h>

BroadcastClient::BroadcastClient()
{
    _udpSocket = std::make_unique<QUdpSocket>(this);
    connect(_udpSocket.get(), &QUdpSocket::readyRead, this, &BroadcastClient::onReadyReadDiscoveryMessage);
}

bool BroadcastClient::Bind(const QHostAddress &address, quint16 port)
{
    if (const bool bind = _udpSocket->bind(address, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
    {
        Log::Multiplayer.LogInfo("BroadcastClient::Bind: Bind to " + address.toString() + ":" + QString::number(port));
        return true;
    }

    Log::Multiplayer.LogError("BroadcastClient::Bind: Cannot bind to " + address.toString() + ":" + QString::number(port) +
                              " - " + _udpSocket->errorString());
    return false;
}

void BroadcastClient::Close()
{
    _udpSocket->close();
}

void BroadcastClient::onReadyReadDiscoveryMessage()
{
    while (_udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udpSocket->pendingDatagramSize());
        QHostAddress senderAddress;
        quint16 senderPort;

        _udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);

        if (_onReadyReadDataCallback)
        {
            _onReadyReadDataCallback(
                senderAddress.toString(),
                senderPort,
                MessageUtils::ToJsonObject(datagram));
        }
     }
}
