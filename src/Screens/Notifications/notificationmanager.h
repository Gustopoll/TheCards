#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "src/Screens/Notifications/infodialog.h"
#include "src/Screens/stylesheetcontroller.h"

#include <QObject>
#include <QString>
#include <memory>
#include <vector>

class QWidget;

class NotificationManager : public QObject
{
    Q_OBJECT

public:
    explicit NotificationManager(QObject* parent = nullptr);
    ~NotificationManager() override = default;

    NotificationManager(const NotificationManager&) = delete;
    NotificationManager& operator=(const NotificationManager&) = delete;

    //! Initializes the notification manager with the root/main widget.
    void Initialize(QWidget* parentWidget);

    //! Shows an informational warning notification.
    void ShowWarning(const QString& text);

    //! Clears and closes all active notifications.
    void ClearAll();

private:
    void OnDialogClosed(InfoDialog* dialog);
    void RepositionDialogs();

    QWidget* _parentWidget = nullptr;
    bool _initialized = false;

    StyleSheetController _styleSheetController;
    std::vector<std::shared_ptr<InfoDialog>> _dialogs;
};

#endif // NOTIFICATIONMANAGER_H
