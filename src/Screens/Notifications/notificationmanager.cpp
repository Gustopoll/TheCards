#include "notificationmanager.h"

#include <QDebug>
#include <format>

NotificationManager& NotificationManager::Get()
{
    static NotificationManager instance;
    return instance;
}

void NotificationManager::Initialize(QWidget* parentWidget)
{
    _parentWidget = parentWidget;
    _initialized = true;
}

void NotificationManager::ShowWarning(const QString& text)
{
    if (!_initialized || !_parentWidget)
    {
        qWarning() << "NotificationManager is not initialized!";
        return;
    }

    const uint32_t currentPosition = static_cast<uint32_t>(_dialogs.size());
    auto dialog = std::make_shared<InfoDialog>(_parentWidget, currentPosition);
    dialog->SetText(text);

    dialog->GetCloseDialogEvent().Subscribe(
        [this](InfoDialog* closedDialog)
        {
            OnDialogClosed(closedDialog);
        });

    const auto style = _styleSheetController.GetStyleSheet(kStyleInfoDialogPath);
    if (style.isEmpty())
    {
        const QString message = std::format("Unable to load style from:<br>'{}'", kStyleInfoDialogPath).c_str();
        dialog->SetText(message);
    }
    else
    {
        dialog->setStyleSheet(style);
    }

    _dialogs.push_back(dialog);
    dialog->show();
}

void NotificationManager::OnDialogClosed(InfoDialog* dialog)
{
    std::erase_if(_dialogs, [dialog](const std::shared_ptr<InfoDialog>& item)
    {
        return item.get() == dialog;
    });

    RepositionDialogs();
}

void NotificationManager::RepositionDialogs()
{
    for (size_t i = 0; i < _dialogs.size(); ++i)
    {
        _dialogs[i]->ChangePosition(static_cast<uint32_t>(i));
    }
}

void NotificationManager::ClearAll()
{
    for (auto& dialog : _dialogs)
    {
        dialog->close();
    }

    _dialogs.clear();
    _initialized = false;
    _parentWidget = nullptr;
}
