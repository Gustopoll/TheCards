#include "clientcallbacks.h"

ClientCallbacks::ClientCallbacks()
{

}

OnReadyReadDataCallback ClientCallbacks::GetReadyReadData() const
{
    return _readyReadDataCallback;
}

OnReadyReadDataCallback ClientCallbacks::GetReadyReadBroadcastData() const
{
    return _readyReadBroadcastDataCallback;
}

OnBroadcastServerFoundCallback ClientCallbacks::GetServerFound() const
{
    return _serverFoundCallback;
}

OnBroadcastServerLostCallback ClientCallbacks::GetServerLost() const
{
    return _serverLostCallback;
}

OnClientConnectedCallback ClientCallbacks::GetClientConnected() const
{
    return _clientConnectedCallback;
}

OnClientDisconnectedCallback ClientCallbacks::GetClientDisconnected() const
{
    return _clientDisconnectedCallback;
}

OnErrorFromServer ClientCallbacks::GetErrorFromServer() const
{
    return _errorFromServer;
}
