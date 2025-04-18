#ifndef MESSAGEBUILDER_H
#define MESSAGEBUILDER_H

#include "MultiplayerComponent/Utility/Constants.h"

#include <QString>
#include <QJsonObject>

enum class WelcomeResponseType
{
    Ok,
    ClientAlreadyRegistered,
    NameAlreadyExists,
    ServerFull
};

class MessageBuilder
{
public:
    MessageBuilder();

    //! Initial message from client to server. Clients wants to register.
    QJsonObject CreateWelcomeData(const QString& clientName);

    //! Response on welcome message. Server sent this message to client.
    QJsonObject CreateWelcomeResponseData(WelcomeResponseType type, const QString& futureName = "");
};

#endif // MESSAGEBUILDER_H
