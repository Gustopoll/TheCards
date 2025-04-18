#ifndef CONNECTEDCLIENT_H
#define CONNECTEDCLIENT_H

#include "MultiplayerComponent/Utility/CallbackDefinitions.h"

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>

using OnDisconnect = std::function<void(const QString& guid)>;
using OnReayRead = std::function<void(const QString& guid,  const QJsonObject& data)>;
class ConnectedClient : public QObject
{
    Q_OBJECT
public:
    ConnectedClient(QTcpSocket* socket);
    ~ConnectedClient();

    //! Sends the data to the client.
    void SendData(const QJsonObject& data);

    //! Gets the unique name.
    const QString& GetName() { return _name; }

    //! Sets the unique name.
    void SetName(const QString& name) { _name = name; }

    //! Retruns true if client is ready and able to communicate with server.
    bool IsReady() const { return _isReady; }

    //! Changes the ready state.
    void SetIsReady(bool isReady) { _isReady = isReady; }

    //! Gets the Guid of
    const QString GetGuid() { return _guid.toString();}

    void Disconnect();

    void SetOnReadyReadData(OnReayRead callback) { _onReadyReadClientDataCallback = callback; }
    void SetOnDisconnected(OnDisconnect callback) { _onDisconnectCallback = callback; }

private:
    bool _isReady = false;

    QUuid _guid;
    QString _name;
    QTcpSocket* _socket = nullptr;

    void onReadyRead();
    void onDisconnected();

    OnReayRead _onReadyReadClientDataCallback = nullptr;
    OnDisconnect _onDisconnectCallback = nullptr;
};

#endif // CONNECTEDCLIENT_H
