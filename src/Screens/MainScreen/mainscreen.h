#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/Utils/datapreloader.h"
#include "src/Settings/Settings.h"

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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void LoadData();

    Ui::MainScreen *ui;

    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

    std::vector<Settings> _allSettings;

    DataPreloader _dataPreloader;

};
#endif // MAINWINDOW_H
