#include "screenmanager.h"
#include <QDebug>

ScreenManager::ScreenManager(QObject* parent)
    : QObject(parent)
{
}

void ScreenManager::Initialize(QWidget* mainWidget, QStackedWidget* stackedWidget)
{
    _mainWidget = mainWidget;
    _stackedWidget = stackedWidget;
    _initialized = true;
    _history.clear();
    _currentScreen = std::nullopt;
}

bool ScreenManager::CreateScreen(ScreenState screen, ScreenWidget* widget)
{
    if (!_initialized || !widget || !_stackedWidget)
        return false;

    if (_screenIndexes.contains(screen))
        return false;

    _stackedWidget->addWidget(widget);
    _screenIndexes.emplace(screen, _stackedWidget->indexOf(widget));
    return true;
}

bool ScreenManager::ShowScreen(ScreenState screen, bool recordHistory)
{
    if (!_initialized || !_stackedWidget)
        return false;

    const auto idIter = _screenIndexes.find(screen);
    if (idIter == _screenIndexes.end())
        return false;

    if (_currentScreen.has_value() && recordHistory && *_currentScreen != screen)
    {
        _history.push_back(*_currentScreen);
    }

    if (auto* w = qobject_cast<ScreenWidget*>(_stackedWidget->currentWidget()))
    {
        w->OnScreenInactive();
    }

    _stackedWidget->setCurrentIndex(idIter->second);
    _currentScreen = screen;

    if (auto* w = qobject_cast<ScreenWidget*>(_stackedWidget->currentWidget()))
    {
        w->OnScreenActive();
    }

    return true;
}

bool ScreenManager::GoBack()
{
    if (_history.empty())
        return false;

    const ScreenState previousScreen = _history.back();
    _history.pop_back();

    return ShowScreen(previousScreen, false);
}

void ScreenManager::CleanAll()
{
    if (!_initialized || !_stackedWidget)
        return;

    for (const auto& [_, index] : _screenIndexes)
    {
        auto* widget = _stackedWidget->widget(index);
        _stackedWidget->removeWidget(widget);
        if (widget)
        {
            widget->deleteLater();
        }
    }

    _screenIndexes.clear();
    _history.clear();
    _currentScreen = std::nullopt;
    _initialized = false;
    _mainWidget = nullptr;
    _stackedWidget = nullptr;
}
