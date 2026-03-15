#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/Screens/Loadings/loadingscreen.h"
#include "src/Utils/datapreloader.h"
#include "src/Settings/settingscontroller.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScreen; }
QT_END_NAMESPACE

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    MainScreen(QWidget *parent = nullptr);
    ~MainScreen();

    void Start();
    void OnLoadingFinished();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainScreen *ui;

    void closeEvent(QCloseEvent *event);

    SettingsController _settingsController;

    DataPreloader _dataPreloader;

    LoadingScreen* _loadingScreen = nullptr;
};
#endif // MAINWINDOW_H
