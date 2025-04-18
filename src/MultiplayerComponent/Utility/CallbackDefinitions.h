#ifndef CALLBACKDEFINITIONS_H
#define CALLBACKDEFINITIONS_H

#include <functional>
#include <QString>
#include <QJsonObject>

using OnReadyReadDataCallback = std::function<void(const QString& ipAddress, quint16 port, const QJsonObject& data)>;

//! When server receive data from connected client.
using OnReadyReadClientDataCallback = std::function<void(const QString& clientName, const QJsonObject& data)>;

//! When client receive broadcast UDP packet from the server.
using OnBroadcastServerFoundCallback = std::function<void(const QString& ipAddress, quint16 port, const QJsonObject& data)>;

//! When server does not send UDP packet. TTC expired.
using OnBroadcastServerLostCallback = std::function<void(const QString& ipAddress, quint16 port, const QJsonObject& data)>;

//! When client and server connect.
using OnClientConnectedCallback = std::function<void()>;

//! When client and server disconnect.
using OnClientDisconnectedCallback = std::function<void()>;

//! When client connect to the server with unieqe client name.
using OnConnectedClientToServerCallback = std::function<void(const QString clientName)>;

//! When connected client disconnect.
using OnConnectedClientDisconnectCallback = std::function<void(const QString clientName)>;

//! When server send error message to client.
using OnErrorFromServer = std::function<void(const QString errorMessage)>;

#endif // CALLBACKDEFINITIONS_H
