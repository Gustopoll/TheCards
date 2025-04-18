#ifndef SIMPLECLIENT_H
#define SIMPLECLIENT_H

#include "MultiplayerComponent/Client/clientsettings.h"
#include "MultiplayerComponent/Client/clientcallbacks.h"
#include "MultiplayerComponent/Client/Udp/broadcastclient.h"
#include "MultiplayerComponent/Client/serverlistbuilder.h"
#include "MultiplayerComponent/Utility/Constants.h"
#include "MultiplayerComponent/Utility/messagebuilder.h"

#include <QString>
#include <QUuid>
#include <QTcpSocket>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

enum class ClientState
{
    NotConnected,
    ConnectedNotReady,
    Connected
};

class SimpleClient : public QObject
{
    Q_OBJECT
public:
    SimpleClient();

    //! Connects to the server.
    //!
    //! @param address IP address of the server.
    //!                Cannot be an emptry string.
    //! @param port Port of the server.
    void Connect(const QString& address, quint16 port);

    //! Disconnects from the server.
    void Disconnect();

    //! Sends the data to the server.
    void SendData(const QJsonObject& data);

    //! Starts the process of finding server. You are not allow to change found and lost server callbacks when finding server is running.
    bool StartFindindServers();

    //! Stops the process of finding server.
    void StopFindingServers();

    //! List of settings for simple client.
    ClientSettings& Settings() { return _settings; }

    //! List of callbacks for simple clients.
    ClientCallbacks& Callbacks() { return _callbacks; }

    //! Gets all currently available servers.
    const ServerList& GetAllAvailableServers();

private:
    QString _serverAddress;
    quint16 _serverPort;

    ClientSettings _settings;
    ClientCallbacks _callbacks;

    ClientState _state = ClientState::NotConnected;

    ServerListBuilder _serverListBuilder;
    MessageBuilder _messageBuilder;
    std::unique_ptr<BroadcastClient> _broadcastClient;
    QTcpSocket* _socket = nullptr;

    void OnReadyReadBroadcastData(const QString& ipAddress, quint16 port, const QJsonObject& data);
    void OnConnected();
    void OnDisconnected();
    void OnReadyReadData();
};

#endif // SIMPLECLIENT_H
