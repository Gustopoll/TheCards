#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent, uint32_t position) :
    QWidget(parent),
    ui(new Ui::InfoDialog),
    _position(position)
{
    ui->setupUi(this);
    const uint32_t verticalSize = height() * position;
    move(0, verticalSize);
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::SetText(const QString &text)
{
    ui->labelText->setText(text);
}

void InfoDialog::ChangePosition(const uint32_t position)
{
    _position = position;
    move(0, height() * position);
}

void InfoDialog::on_buttonHide_clicked()
{
    close();
    _closeDialogEvent.Fire(_position);
}
