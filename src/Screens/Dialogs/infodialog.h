#ifndef INFODIALOG_H
#define INFODIALOG_H

#include "src/Utils/eventhandler.h"

#include <QWidget>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QWidget
{
    Q_OBJECT

public:

    //! Event called when dialog is closed.
    using CloseDialogEvent = EventHandler<
        //! Position of closed dialog.
        uint32_t>;

    InfoDialog(
        QWidget *parent = nullptr,
        uint32_t orderNumber = 0);
    ~InfoDialog();

    void SetText(const QString& text);

    //! Changes position of dialog.
    void ChangePosition(uint32_t position);

    CloseDialogEvent::Subscriber& GetCloseDialogEvent()
    {
        return _closeDialogEvent.GetSubscriber();
    }

private slots:
    void on_buttonHide_clicked();

private:
    Ui::InfoDialog *ui;

    //! Represents how many dialog windows are shown above this dialog.
    uint32_t _position = 0;

    CloseDialogEvent _closeDialogEvent;
};

#endif // INFODIALOG_H
