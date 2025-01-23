#include "mainscreen.h"
#include "ui_mainwindow.h"

#include "src/Screens/screencontroller.h"
#include "src/Screens/GameScreen/gamescreen.h"
#include "src/Screens/SettingsScreen/settingsscreen.h"

#include <QDebug>

MainScreen::MainScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    ScreenController::Get().Initialize(this, ui->stackedWidget);
    ScreenController::Get().CreateScreen(ScreenState::Game, new GameScreen());
    ScreenController::Get().CreateScreen(ScreenState::Settings, new SettingsScreen());
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::closeEvent(QCloseEvent *event)
{
    qDebug() << "closeEvent";
    ScreenController::Get().CleanAll();
}

void MainScreen::on_pushButton_clicked()
{
    ScreenController::Get().ShowWarningDialog("Dominik je boss");
    //ScreenController::Get().ShowScreen(ScreenState::Game);
}

void MainScreen::on_pushButton_2_clicked()
{
    ScreenController::Get().ShowScreen(ScreenState::Settings);
}
