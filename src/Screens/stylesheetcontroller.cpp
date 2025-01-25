#include "stylesheetcontroller.h"

#include "src/Screens/screencontroller.h"

#include <QDir>
#include <QFile>
#include <QTextStream>

StyleSheetController::StyleSheetController()
{

}

const QString StyleSheetController::GetStyleSheet(const QString &path)
{
    const auto& dataIter = _cache.find(path.toStdString());
    if (dataIter != _cache.end())
    {
        return dataIter->second;
    }

    const auto fullPath = QDir::currentPath() + '/' + path;

    QFile file(fullPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString message = "Unable to load a style from:<br>'" + fullPath + "'";
        ScreenController::Get().ShowWarningDialog(message);
        return {};
    }

    QString data = file.readAll();
    _cache.insert({path.toStdString(), data});

    return data;
}
