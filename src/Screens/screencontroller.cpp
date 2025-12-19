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

bool ScreenController::CreateScreen(ScreenState screen, QWidget *widget)
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

    _stackedWidget->setCurrentIndex(idIter->second);
    return true;
}

void ScreenController::ShowWarningDialog(const QString &text)
{
    auto item = std::make_shared<InformationalDialogScreen>(_mainWidget, _warningDialogWindow.size());
    _warningDialogWindow.emplace_back(item);
    item->SetText(text);
    item->SetOnCloseFunction(
        [this](uint32_t orderNumber)
        {
            _warningDialogToDelete.push_back(orderNumber);
        });

    const auto style = styleSheetController.GetStyleSheet(kStyleInformationalDialogPath);
    item->setStyleSheet(style);
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

    _warningDialogWindow.clear();

    delete _timer;
    _initialized = false;
}

void ScreenController::OnUpdate()
{
    for (const auto index : _warningDialogToDelete)
    {
        _warningDialogWindow.erase(_warningDialogWindow.begin() + index);
        for (size_t i = index; i < _warningDialogWindow.size(); ++i)
            _warningDialogWindow[i]->ChangeOrderNumber(i);
    }
    _warningDialogToDelete.clear();
}
