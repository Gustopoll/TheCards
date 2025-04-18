#ifndef SERVERLISTBUILDER_H
#define SERVERLISTBUILDER_H

#include "MultiplayerComponent/Utility/CallbackDefinitions.h"

#include <QHostAddress>
#include <QJsonDocument>
#include <QObject>
#include <QTimer>

struct NetworkData
{
    QString address;
    quint16 port;
    QJsonObject data;
    int ttc;
};

//! GUID and network data
using ServerList = std::map<QString, NetworkData>;

class ServerListBuilder : public QObject
{
public:
    ServerListBuilder();

    //! Calls when client get message that some server is alive.
    //!
    //! @param address IP address of the server.
    //! @param port Port of the server.
    //! @param data Data of the message.
    void OnMessageFromServer(const QString& address, quint16 port, const QJsonObject& data);

    //! Gets all available servers.
    const ServerList& GetServerList() { return _serverList; }

    //! Sets TTC (Time to close).
    void SetTTC(int ttc) { _ttc = ttc; }

    void SetOnServerFoundCallback(OnBroadcastServerFoundCallback callback) { _serverFoundCallback = callback; }
    void SetOnServerLostCallback(OnBroadcastServerLostCallback callback) { _serverLostCallback = callback; }

private:
    //! Map of all available servers.
    ServerList _serverList;

    //! Tiemr for decreasing TTC.
    QTimer _timer;

    //! Speed of the timer [ms] (one iteration).
    int _timerSpeed = 1000;

    //! Time to close, number of iterations until server is deleted from the list.
    int _ttc = 3;

    OnBroadcastServerFoundCallback _serverFoundCallback = nullptr;
    OnBroadcastServerLostCallback _serverLostCallback = nullptr;

    void OnTimerTimeout();
};

#endif // SERVERLISTBUILDER_H
