#include "notificationmanager.h"

#include <QDebug>
#include <algorithm>
#include <format>

NotificationManager::NotificationManager(QObject* parent)
    : QObject(parent)
{
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

    const uint32_t currentPosition = static_cast<uint32_t>(_banners.size());
    auto banner = std::make_shared<NotificationBanner>(_parentWidget, currentPosition);
    banner->SetText(text);

    banner->GetCloseBannerEvent().Subscribe(
        [this](NotificationBanner* closedBanner)
        {
            OnBannerClosed(closedBanner);
        });

    const auto style = _styleSheetController.GetStyleSheet(kStyleNotificationBannerPath);
    if (style.isEmpty())
    {
        const QString message = std::format("Unable to load style from:<br>'{}'", kStyleNotificationBannerPath).c_str();
        banner->SetText(message);
    }
    else
    {
        banner->setStyleSheet(style);
    }

    _banners.push_back(banner);
    banner->show();
}

void NotificationManager::OnBannerClosed(NotificationBanner* banner)
{
    std::erase_if(_banners, [banner](const std::shared_ptr<NotificationBanner>& item) {
        return item.get() == banner;
    });

    RepositionBanners();
}

void NotificationManager::RepositionBanners()
{
    for (size_t i = 0; i < _banners.size(); ++i)
    {
        _banners[i]->ChangePosition(static_cast<uint32_t>(i));
    }
}

void NotificationManager::ClearAll()
{
    for (auto& banner : _banners)
    {
        banner->close();
    }
    _banners.clear();
    _initialized = false;
    _parentWidget = nullptr;
}
