#include "messageutils.h"

namespace MessageUtils
{

QJsonObject ToJsonObject(const QByteArray& data)
{
    const auto documentData = QJsonDocument::fromJson(data);
    if (!documentData.isObject())
        return {};

    return documentData.object();
}

QString ToJsonAsString(const QJsonObject& data)
{
    return QJsonDocument(data).toJson();
}

QByteArray ToByteArray(const QJsonObject &data)
{
    return QJsonDocument(data).toJson().toBase64();
}

StatusCode GetStatusCode(const QJsonObject& data)
{
    return static_cast<StatusCode>(data[kMessageTypeStatusCode].toInt());
}

QString GetGuid(const QJsonObject& data)
{
    return data[kMessageTypeGuid].toString();
}

QString GetClientName(const QJsonObject& data)
{
    return data[kMessageTypeName].toString();
}

QString GetErrorString(const QJsonObject &data)
{
    return data[kMessageTypeErrorString].toString();
}

bool IsServerRunning(const QJsonObject &data)
{
    const auto serverIter = data.find(kMessageTypeServerIsRunning);
    if (serverIter == data.end())
        return false;

    return serverIter.value().toBool();
}

}
