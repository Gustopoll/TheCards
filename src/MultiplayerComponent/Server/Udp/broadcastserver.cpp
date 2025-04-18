#include "broadcastserver.h"

#include "MultiplayerComponent/Utility/Constants.h"
#include "MultiplayerComponent/Utility/messageutils.h"
#include <Logger/logger.h>

BroadcastServer::BroadcastServer()
{
    _guid = QUuid::createUuid();
    connect(&_timer, &QTimer::timeout, this, &BroadcastServer::TimerTimeout);
}

BroadcastServer::BroadcastServer(const QUuid& guid) : _guid(guid)
{
    connect(&_timer, &QTimer::timeout, this, &BroadcastServer::TimerTimeout);
}

void BroadcastServer::SendData(const QHostAddress &address, quint16 port, const QByteArray &data)
{
    QUdpSocket udpSocket;

    // Bind socket to any IPv4 address, we need to specify destination port.
    // Without bind, system automaticky choose random free port.
    if (!udpSocket.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
    {
        Log::Multiplayer.LogError("BroadcastServer::SendData: Binding failed: " + udpSocket.errorString());
        return;
    }

    if (udpSocket.writeDatagram(data, address, port) == -1)
    {
        Log::Multiplayer.LogError("BroadcastServer::SendData: Sending data failed: " + udpSocket.errorString());
        return;
    }
}

void BroadcastServer::StartSendingData(const QHostAddress &address, quint16 port, const QJsonObject &data, int interval)
{
    if (_timer.isActive())
        return;

    auto jSonData = data;
    jSonData[kMessageTypeGuid] = _guid.toString();
    jSonData[kMessageTypeServerIsRunning] = true;
    const auto dataWithGuid = QJsonDocument(jSonData).toJson();

    _dataToSend = {
        address,
        port,
        dataWithGuid};

    _timer.start(interval);
    Log::Multiplayer.LogInfo("BroadcastServer::StartSendingData: Start of sending broadcast data to " +
                             address.toString() + ":" + QString::number(port) +
                             " each " + QString::number(interval) + " ms\n Data: " + dataWithGuid);
}

void BroadcastServer::StopSendingData()
{
    _timer.stop();
    Log::Multiplayer.LogInfo("BroadcastServer::StopSendingData: Stop of sending broadcast data from " +
                             _dataToSend.address.toString() + ":" + QString::number(_dataToSend.port));

    ChangeData(kMessageTypeServerIsRunning, false);
    SendData(_dataToSend.address, _dataToSend.port, _dataToSend.data);
}

void BroadcastServer::ChangeData(const QString &key, const QJsonValue &value)
{
    const auto data = QJsonDocument::fromJson(_dataToSend.data);
    if (!data.isObject())
    {
        Log::Multiplayer.LogError("BroadcastServer::ChangeData: Cannot change key '" + key +
                                  "' with value '" + value.toVariant().toString() +
                                  "' - Value is not an object");
        return;
    }

    auto objectData = data.object();
    auto foundData = objectData.find(key);
    if (foundData == objectData.end())
    {
        Log::Multiplayer.LogError("BroadcastServer::ChangeData: Cannot change key '" + key +
                                  "' with '" + value.toVariant().toString() +
                                  "' - Key does not exist");
        return;
    }

    auto oldValue = objectData[key].toVariant().toString();
    objectData[key] = value;
    _dataToSend.data = QJsonDocument(objectData).toJson();
    Log::Multiplayer.LogInfo("BroadcastServer::ChangeData: "
        "Value of '" + key + "' is changed from '" + oldValue + "' to '" + value.toVariant().toString() + "'");
}

void BroadcastServer::TimerTimeout()
{
    SendData(_dataToSend.address, _dataToSend.port, _dataToSend.data);
}
