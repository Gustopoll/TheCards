#ifndef BROADCASTCLIENT_H
#define BROADCASTCLIENT_H

#include "MultiplayerComponent/Utility/CallbackDefinitions.h"

#include <QUdpSocket>
#include <QUuid>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

class BroadcastClient : public QObject
{
    Q_OBJECT
public:
    BroadcastClient();

    ~BroadcastClient() = default;

    //! Listens on given ip address and port.
    //! @param address Address to listen.
    //! @param port Port to listen, When port is set to 0, it is automaticly choose some free port.
    //! @return true when this object starts listening on give address and port, otherwise false.
    bool Bind(const QHostAddress &address, quint16 port = 0);

    //! Closes the socket.
    void Close();

    //! Sets callback that is called when data is received.
    void SetOnReadyReadData(OnReadyReadDataCallback callback) { _onReadyReadDataCallback = callback; }

private slots:
    void onReadyReadDiscoveryMessage();

private:
    std::unique_ptr<QUdpSocket> _udpSocket;

    OnReadyReadDataCallback _onReadyReadDataCallback;
};

#endif // BROADCASTCLIENT_H
