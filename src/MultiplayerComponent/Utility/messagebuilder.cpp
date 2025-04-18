#include "messagebuilder.h"

MessageBuilder::MessageBuilder()
{

}

QJsonObject MessageBuilder::CreateWelcomeData(const QString& clientName)
{
    QJsonObject data;
    data[kMessageTypeStatusCode] = static_cast<int32_t>(StatusCode::RegisterRequest);
    data[kMessageTypeName] = clientName;
    return data;
}

QJsonObject MessageBuilder::CreateWelcomeResponseData(
    WelcomeResponseType type,
    const QString& futureName)
{
    QJsonObject data;
    switch (type)
    {
    case WelcomeResponseType::Ok:
    {
        data[kMessageTypeStatusCode] = static_cast<int32_t>(StatusCode::RegisterResponseGood);
        break;
    }
    case WelcomeResponseType::ClientAlreadyRegistered:
    {
        data[kMessageTypeStatusCode] = static_cast<int32_t>(StatusCode::RegisterRequestBad);
        data[kMessageTypeErrorString] = "Client is already registered.";
        break;
    }
    case WelcomeResponseType::NameAlreadyExists:
    {
        data[kMessageTypeStatusCode] = static_cast<int32_t>(StatusCode::RegisterRequestBad);
        data[kMessageTypeErrorString] = "Client with name: '" + futureName + "' already exist.";
        break;
    }
    case WelcomeResponseType::ServerFull:
    {
        data[kMessageTypeStatusCode] = static_cast<int32_t>(StatusCode::RegisterRequestBad);
        data[kMessageTypeErrorString] = "Server is full.";
        break;
    }
    }

    return data;
}
