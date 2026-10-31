#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/Screens/Loadings/loadingscreen.h"
#include "src/Screens/Notifications/notificationmanager.h"
#include "src/Screens/screenmanager.h"
#include "src/Settings/settingscontroller.h"
#include "src/Utils/datapreloader.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScreen; }
QT_END_NAMESPACE

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    MainScreen(QWidget *parent = nullptr);
    ~MainScreen() override;

    void Start();
    void OnLoadingFinished();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainScreen *ui;

    void closeEvent(QCloseEvent *event) override;

    SettingsController _settingsController;

    DataPreloader _dataPreloader;

    ScreenManager _screenManager;

    NotificationManager _notificationManager;

    LoadingScreen* _loadingScreen = nullptr;
};
#endif // MAINWINDOW_H
