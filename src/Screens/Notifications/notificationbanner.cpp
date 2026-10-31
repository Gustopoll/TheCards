#include "notificationbanner.h"
#include "ui_notificationbanner.h"

NotificationBanner::NotificationBanner(QWidget *parent, uint32_t position) :
    QWidget(parent),
    ui(new Ui::NotificationBanner),
    _position(position)
{
    ui->setupUi(this);
    const uint32_t verticalSize = height() * position;
    move(0, verticalSize);
}

NotificationBanner::~NotificationBanner()
{
    delete ui;
}

void NotificationBanner::SetText(const QString &text)
{
    ui->labelText->setText(text);
}

void NotificationBanner::ChangePosition(const uint32_t position)
{
    _position = position;
    move(0, height() * position);
}

void NotificationBanner::on_buttonHide_clicked()
{
    close();
    _closeBannerEvent.Fire(this);
}
