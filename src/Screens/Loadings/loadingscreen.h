#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "src/Utils/datapreloader.h"
#include <QFutureWatcher>
#include <QMainWindow>

namespace Ui {
class LoadingScreen;
}

class MainScreen;

class LoadingScreen : public QMainWindow
{
    Q_OBJECT

public:
    LoadingScreen(DataPreloader& dataPreloader, MainScreen *parent = nullptr);
    ~LoadingScreen();

private slots:
    void on_closeButton_clicked();

private:
    Ui::LoadingScreen *ui;

    QFutureWatcher<void>* watcher;

    size_t _countPreloadedData = 0;
    size_t _countDataToPreload = 0;

    DataPreloader& _dataPreloader;
};

#endif // LOADINGSCREEN_H
