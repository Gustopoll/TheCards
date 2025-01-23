#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsScreen;
}

class SettingsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsScreen(QWidget *parent = nullptr);
    ~SettingsScreen();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SettingsScreen *ui;
};

#endif // SETTINGSSCREEN_H
