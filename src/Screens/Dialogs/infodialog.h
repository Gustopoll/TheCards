#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QWidget>
#include <functional>

using OnClose = std::function<void(uint32_t)>;

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QWidget
{
    Q_OBJECT

public:
    explicit InfoDialog(
        QWidget *parent = nullptr,
        uint32_t orderNumber = 0);
    ~InfoDialog();

    void SetText(const QString& text);

    //! Sets the function called when window is closed.
    void SetOnCloseFunction(OnClose callback) { _onCloseCallback = callback;}

    //! Changes position of dialog.
    void ChangePosition(uint32_t position);
private slots:
    void on_buttonHide_clicked();

private:
    Ui::InfoDialog *ui;

    //! Represents how many dialog windows are shown above this dialog.
    uint32_t _position = 0;
    OnClose _onCloseCallback = nullptr;
};

#endif // INFODIALOG_H
