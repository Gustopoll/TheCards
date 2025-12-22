#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "src/Settings/Settings.h"

#include <QWidget>

namespace Ui {
class SettingsScreen;
}

class SettingsScreen : public QWidget
{
    Q_OBJECT

public:
    SettingsScreen(std::vector<Settings>& settings, QWidget *parent = nullptr);
    ~SettingsScreen();

private slots:
    void on_pushButton_clicked();

    void on_serverPort_textChanged();

private:
    Ui::SettingsScreen *ui;

    std::vector<Settings>& _settings;
};

#endif // SETTINGSSCREEN_H
