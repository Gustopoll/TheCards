#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "src/Screens/screenmanager.h"
#include "src/Settings/settingscontroller.h"

#include <QWidget>

namespace Ui {
class SettingsScreen;
}

class SettingsScreen : public ScreenWidget
{
    Q_OBJECT

public:
    SettingsScreen(
        ScreenManager& screenManager,
        SettingsController& settings,
        QWidget *parent = nullptr);
    ~SettingsScreen() override;

    void OnScreenActive() override;
    void OnScreenInactive() override;

private slots:
    void on_pushButton_clicked();

    void on_serverPort_textChanged();

    void on_checkBoxFullscreen_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::SettingsScreen *ui;

    ScreenManager& _screenManager;
    SettingsController& _settings;

    QWidget* _parent = nullptr;
};

#endif // SETTINGSSCREEN_H
