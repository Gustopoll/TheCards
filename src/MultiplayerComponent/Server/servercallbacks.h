#ifndef SERVERCALLBACKS_H
#define SERVERCALLBACKS_H

#include "MultiplayerComponent/Utility/CallbackDefinitions.h"

class ServerCallbacks
{
public:
    ServerCallbacks();

    void SetOnReadyReadData(OnReadyReadClientDataCallback callback) { _onReadyReadClientDataCallback = callback; }
    void SetOnConnectedClientDisconnect(OnConnectedClientDisconnectCallback callback) { _onConnectedClientDisconnectedCallback = callback; }
    void SetOnConnectedClientToServer(OnConnectedClientToServerCallback callback) { _onConnectedClientToServerCallback = callback; }

    OnReadyReadClientDataCallback GetOnReadyReadClientData() const;
    OnConnectedClientDisconnectCallback GetOnConnectedClientDisconnected() const;
    OnConnectedClientToServerCallback GetOnConnectedClientToServer() const;

private:
    OnReadyReadClientDataCallback _onReadyReadClientDataCallback = nullptr;
    OnConnectedClientDisconnectCallback _onConnectedClientDisconnectedCallback = nullptr;
    OnConnectedClientToServerCallback _onConnectedClientToServerCallback = nullptr;
};

#endif // SERVERCALLBACKS_H
