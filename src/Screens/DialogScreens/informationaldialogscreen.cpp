#include "informationaldialogscreen.h"
#include "ui_informationaldialogscreen.h"

InformationalDialogScreen::InformationalDialogScreen(QWidget *parent, uint32_t orderNumber) :
    QWidget(parent),
    ui(new Ui::InformationalDialogScreen),
    _orderNumber(orderNumber)
{
    ui->setupUi(this);
    const uint32_t verticalSize = height() * orderNumber;
    move(0, verticalSize);
}

InformationalDialogScreen::~InformationalDialogScreen()
{
    delete ui;
}

void InformationalDialogScreen::SetText(const QString &text)
{
    ui->labelText->setText(text);
}

void InformationalDialogScreen::ChangeOrderNumber(uint32_t orderNumber)
{
    _orderNumber = orderNumber;
    move(0, height() * orderNumber);
}

void InformationalDialogScreen::on_buttonHide_clicked()
{
    close();
    if (_onCloseCallback)
        _onCloseCallback(_orderNumber);
}
