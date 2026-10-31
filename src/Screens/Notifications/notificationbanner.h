#ifndef NOTIFICATIONBANNER_H
#define NOTIFICATIONBANNER_H

#include "src/Utils/eventhandler.h"

#include <QWidget>

namespace Ui {
class NotificationBanner;
}

class NotificationBanner : public QWidget
{
    Q_OBJECT

public:
    //! Event called when banner is closed.
    using CloseBannerEvent = EventHandler<NotificationBanner*>;

    NotificationBanner(
        QWidget *parent = nullptr,
        uint32_t orderNumber = 0);
    ~NotificationBanner() override;

    void SetText(const QString& text);

    //! Changes position of banner.
    void ChangePosition(uint32_t position);

    CloseBannerEvent::Subscriber& GetCloseBannerEvent()
    {
        return _closeBannerEvent.GetSubscriber();
    }

private slots:
    void on_buttonHide_clicked();

private:
    Ui::NotificationBanner *ui;

    //! Represents how many banner windows are shown above this banner.
    uint32_t _position = 0;

    CloseBannerEvent _closeBannerEvent;
};

#endif // NOTIFICATIONBANNER_H
