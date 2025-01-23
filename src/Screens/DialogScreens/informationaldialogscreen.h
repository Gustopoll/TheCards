#ifndef INFORMATIONALDIALOGSCREEN_H
#define INFORMATIONALDIALOGSCREEN_H

#include <QWidget>
#include <functional>

using OnClose = std::function<void(uint32_t)>;

namespace Ui {
class InformationalDialogScreen;
}

class InformationalDialogScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InformationalDialogScreen(
        QWidget *parent = nullptr,
        uint32_t orderNumber = 0);
    ~InformationalDialogScreen();

    void SetText(const QString& text);

    //! Sets the function called when window is closed.
    void SetOnCloseFunction(OnClose callback) { _onCloseCallback = callback;}

    //! Changes the order number and vertiacal position of dialog.
    void ChangeOrderNumber(uint32_t orderNumber);
private slots:
    void on_buttonHide_clicked();

private:
    Ui::InformationalDialogScreen *ui;

    //! Represents how many dialog windows are shown above this dialog.
    uint32_t _orderNumber;
    OnClose _onCloseCallback = nullptr;
};

#endif // INFORMATIONALDIALOGSCREEN_H
