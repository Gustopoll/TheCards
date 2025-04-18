#ifndef SIMPLESERVER_H
#define SIMPLESERVER_H

#include "MultiplayerComponent/Server/serversettings.h"
#include "MultiplayerComponent/Server/servercallbacks.h"
#include "MultiplayerComponent/Server/Udp/broadcastserver.h"
#include "MultiplayerComponent/Server/connectedclient.h"
#include "MultiplayerComponent/Utility/Constants.h"
#include "MultiplayerComponent/Utility/messagebuilder.h"

#include <QObject>
#include <QTcpServer>

#include <unordered_map>

enum class ServerState
{
    Idle,
    WaitingInLobby,
    Running
};

class SimpleServer : public QObject
{
    Q_OBJECT
public:
    SimpleServer();

    //! Starts the server in waiting mode and other cliesnt can join.
    bool StartWaitingInLobby();

    //! Starts the communication with all connected clients, new clients
    //! cannot join.
    bool StartCommunication();

    //! Changes the running server state to waiting.
    void BackToLobby();

    //! Stops the runnig server.
    void EndServer();

    //! Disconnect the client based on the name.
    //!
    //! @param clientName Name of the client.
    void DisconnectClientByName(const QString& clientName);

    //! Disconnect the client based on the GUID.
    //!
    //! @param clientGuid GUID of the client.
    void DisconnectClientByGuid(const QString& clientGuid);

    //! Sets the data to be send to all the clients that want to find
    //! this server.
    //!
    //! @param data Json data to be send.
    void SetDiscoveryData(const QJsonObject& data);

    //! Gets the server settings.
    ServerSettings& GetSettings() { return _settings;}

    //! Gets the server callbacks.
    ServerCallbacks& GetCallbacks() { return _callbacks;}
private:

    ServerState _state = ServerState::Idle;

    std::unique_ptr<QTcpServer> _tcpServer;

    //! <Guid of client, connected client>
    std::unordered_map<QString, std::unique_ptr<ConnectedClient>> _connectedClients;

    BroadcastServer _broadcastServer;
    MessageBuilder _messageBuilder;
    QJsonObject _broadcastData;

    ServerSettings _settings;
    ServerCallbacks _callbacks;

    //! Calls when new client connect.
    void OnNewConnection();

    //! Calls when client disconnect.
    void OnClientDisconnect(const QString& guid);

    void OnReadyReadData(const QString& guid, const QJsonObject& data);

    //! Gets the pointer to client based on client name.
    //!
    //! @param clientName Name of the client.
    //! @retval 'pointer of connected client' when the client exists.
    //! @retval 'nullptr' when the client with given name does not exits.
    ConnectedClient* GetClientByName(const QString& clientName);
};

#endif // SIMPLESERVER_H
