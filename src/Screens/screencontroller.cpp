#include "screencontroller.h"
#include <QDebug>

ScreenController& ScreenController::Get()
{
    static ScreenController instancePtr;
    return instancePtr;
}

void ScreenController::Initialize(QWidget* mainWidget, QStackedWidget* stackedWidget)
{
    _mainWidget = mainWidget;
    _stackedWidget = stackedWidget;
    _initialized = true;

    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &ScreenController::OnUpdate);
    _timer->start(50);
}

bool ScreenController::CreateScreen(ScreenState screen, ScreenWidget* widget)
{
   if (!_initialized)
        return false;

   if (!widget)
       return false;

   if (_screenIndexes.find(screen) != _screenIndexes.end())
        return false;

    _stackedWidget->addWidget(widget);
    _screenIndexes.emplace(screen, _stackedWidget->indexOf(widget));
    return true;
}

bool ScreenController::ShowScreen(ScreenState screen)
{
    if (!_initialized)
        return false;

    const auto idIter = _screenIndexes.find(screen);
    if (idIter == _screenIndexes.end())
        return false;

    if (ScreenWidget* w =  dynamic_cast<ScreenWidget*>(_stackedWidget->currentWidget()))
    {
        w->OnScreenInactive();
    }

    _stackedWidget->setCurrentIndex(idIter->second);

    if (ScreenWidget* w = dynamic_cast<ScreenWidget*>(_stackedWidget->currentWidget()))
    {
        w->OnScreenActive();
    }

    return true;
}

void ScreenController::ShowWarningDialog(const QString &text)
{
    auto& item = _infoDialog.emplace_back(std::make_shared<InfoDialog>(_mainWidget, _infoDialog.size()));
    item->SetText(text);

    item->GetCloseDialogEvent().Subscribe(
        [this](uint32_t orderNumber)
        {
            _infoDialogToDelete.push_back(orderNumber);
        });

    const auto style = _styleSheetController.GetStyleSheet(kStyleInfoDialogPath);
    if (style.isEmpty())
    {
        QString message = std::format("Unable to load a style from:<br>'{}'", kStyleInfoDialogPath).c_str();
        item->SetText(message);
    }
    else
    {
        item->setStyleSheet(style);
    }

    item->show();
}

void ScreenController::CleanAll()
{
    if (!_initialized)
        return;

    for (const auto screenIter : _screenIndexes)
    {
        _stackedWidget->removeWidget(_stackedWidget->widget(screenIter.second));
    }

    _infoDialog.clear();

    delete _timer;
    _initialized = false;
}

void ScreenController::OnUpdate()
{
    for (const auto position : _infoDialogToDelete)
    {
        _infoDialog.erase(_infoDialog.begin() + position);
        for (uint32_t newPosition = position; newPosition < _infoDialog.size(); ++newPosition)
        {
            _infoDialog[newPosition]->ChangePosition(newPosition);
        }
    }
    _infoDialogToDelete.clear();
}
