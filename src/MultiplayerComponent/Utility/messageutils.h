#ifndef MESSAGEUTILS_H
#define MESSAGEUTILS_H

#include "MultiplayerComponent/Utility/Constants.h"

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

namespace MessageUtils
{

QJsonObject ToJsonObject(const QByteArray& data);
QString ToJsonAsString(const QJsonObject& data);
QByteArray ToByteArray(const QJsonObject& data);

StatusCode GetStatusCode(const QJsonObject& data);
QString GetGuid(const QJsonObject& data);
QString GetClientName(const QJsonObject& data);
QString GetErrorString(const QJsonObject& data);
bool IsServerRunning(const QJsonObject& data);

}

#endif // MESSAGEUTILS_H
