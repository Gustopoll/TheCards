#ifndef CONSTANTS_H
#define CONSTANTS_H

enum class StatusCode
{
    OK,

    Error,

    // Client sends this code to server to register.
    RegisterRequest,

    // Server sends this code when client is registered succsefull.
    RegisterResponseGood,

    // Server sends this code when client is not registered.
    RegisterRequestBad
};


//! Values that can be present in standard JSON object.
constexpr const char kMessageTypeStatusCode[] = "StatusCode";
constexpr const char kMessageTypeName[] = "Name";
constexpr const char kMessageTypeErrorString[] = "ErrorString";

//! Values that can be present in broadcast JSON object.
constexpr const char kMessageTypeMaxPlayers[] = "MaxPlayers";
constexpr const char kMessageTypeCurrentPlayers[] = "CurrentPlayers";
constexpr const char kMessageTypeGuid[] = "Guid";
constexpr const char kMessageTypePort[] = "Port";
constexpr const char kMessageTypeServerIsRunning[] = "ServerIsRunning";
constexpr const char kMessageTypeServerName[] = "ServerName";


//! Values that can be present in both standard and broadcast JSON object.

#endif // CONSTANTS_H
