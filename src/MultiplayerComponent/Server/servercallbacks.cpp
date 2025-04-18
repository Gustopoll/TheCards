#include "servercallbacks.h"

ServerCallbacks::ServerCallbacks()
{

}

OnReadyReadClientDataCallback ServerCallbacks::GetOnReadyReadClientData() const
{
    return _onReadyReadClientDataCallback;
}

OnConnectedClientDisconnectCallback ServerCallbacks::GetOnConnectedClientDisconnected() const
{
    return _onConnectedClientDisconnectedCallback;
}

OnConnectedClientToServerCallback ServerCallbacks::GetOnConnectedClientToServer() const
{
    return _onConnectedClientToServerCallback;
}
