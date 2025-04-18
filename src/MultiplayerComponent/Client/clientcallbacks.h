#ifndef CLIENTCALLBACKS_H
#define CLIENTCALLBACKS_H

#include "MultiplayerComponent/Utility/CallbackDefinitions.h"

class ClientCallbacks
{
public:
    ClientCallbacks();

    void SetOnReadyReadData(OnReadyReadDataCallback callback) { _readyReadDataCallback = callback; }
    void SetOnReadyReadBroadcastData(OnReadyReadDataCallback callback) { _readyReadBroadcastDataCallback = callback; }
    void SetOnServerFound(OnBroadcastServerFoundCallback callback) { _serverFoundCallback = callback; }
    void SetOnServerLost(OnBroadcastServerLostCallback callback) { _serverLostCallback = callback; }
    void SetOnClientConnected(OnClientConnectedCallback callback) { _clientConnectedCallback = callback; }
    void SetOnClientDisconnected(OnClientDisconnectedCallback callback) { _clientDisconnectedCallback = callback; }
    void SetOnErrorFromServer(OnErrorFromServer callback) { _errorFromServer = callback; }

    OnReadyReadDataCallback GetReadyReadData() const;
    OnReadyReadDataCallback GetReadyReadBroadcastData() const;
    OnBroadcastServerFoundCallback GetServerFound() const;
    OnBroadcastServerLostCallback GetServerLost() const;
    OnClientConnectedCallback GetClientConnected() const;
    OnClientDisconnectedCallback GetClientDisconnected() const;
    OnErrorFromServer GetErrorFromServer() const;

private:
    OnReadyReadDataCallback _readyReadDataCallback = nullptr;
    OnReadyReadDataCallback _readyReadBroadcastDataCallback = nullptr;
    OnBroadcastServerFoundCallback _serverFoundCallback = nullptr;
    OnBroadcastServerLostCallback _serverLostCallback = nullptr;
    OnClientConnectedCallback _clientConnectedCallback = nullptr;
    OnClientDisconnectedCallback _clientDisconnectedCallback = nullptr;
    OnErrorFromServer _errorFromServer = nullptr;
};

#endif // CLIENTCALLBACKS_H
