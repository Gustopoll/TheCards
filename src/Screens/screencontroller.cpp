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
            _warningDialogWindow.erase(_warningDialogWindow.begin() + orderNumber);
            for (size_t i = orderNumber; i < _warningDialogWindow.size(); ++i)
                _warningDialogWindow[i]->ChangeOrderNumber(i);
        });

    QString styleSheet = "QWidget {"
                             "    background-color: #FFEC8B;"  // Svetlo žltá farba pozadia
                             "    border: 1px solid #F0E68C;"   // Jemný olivovo žltý okraj
                             "    border-radius: 5px;"  // Zaoblené rohy
                             "    padding: 15px;"  // Väčší padding
                             "} "

                             "QLabel#labelText {"
                             "    color: #8B4513;"  // Tmavo hnedý text (dobrá kontrastná farba pre žltú)
                             "    font-size: 14px;"  // Nastavenie veľkosti písma
                             "    font-weight: bold;"  // Tučné písmo pre lepšiu viditeľnosť
                             "} "

                             "QPushButton#buttonHide {"
                             "    background-color: #F0E68C;"  // Tmavšie žlté pozadie tlačidla
                             "    color: #8B4513;"  // Tmavo hnedý text na tlačidlo
                             "    border: 1px solid #F0E68C;"  // Žltý okraj
                             "    padding: 5px 10px;"  // Padding na tlačidle
                             "    border-radius: 3px;"  // Zaoblené rohy tlačidla
                             "} "

                             "QPushButton#buttonHide:hover {"
                             "    background-color: #FFD700;"  // Zlatožltá farba tlačidla pri hover
                             "    color: #8B4513;"  // Tmavo hnedý text pri hover
                             "} "

                             "QPushButton#buttonHide:pressed {"
                             "    background-color: #FF8C00;"  // Oranžová farba pri stlačení
                             "}";

    item->setStyleSheet(styleSheet);
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

    _initialized = false;
}

