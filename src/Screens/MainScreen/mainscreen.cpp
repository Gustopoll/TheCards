#include "mainscreen.h"
#include "ui_mainscreen.h"

#include "src/Screens/screencontroller.h"
#include "src/Screens/SettingsScreen/settingsscreen.h"
#include "src/Screens/GameScreen/gamescreen.h"
#include "src/Screens/Loadings/initloading.h"

#include <QDebug>

MainScreen::MainScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScreen)
{
    ui->setupUi(this);

    _allSettings.emplace_back("Data/Settings/Network");
    _allSettings[0].SetSettingDefault("Network/ServerPort", "3652");
    _allSettings[0].ReadSettings();

    ScreenController::Get().Initialize(this, ui->stackedWidget);
    ScreenController::Get().CreateScreen(ScreenState::InitLoading, new InitLoading(_dataPreloader));
    ScreenController::Get().CreateScreen(ScreenState::Game, new GameScreen());
    ScreenController::Get().CreateScreen(ScreenState::Settings, new SettingsScreen(_allSettings));

    //ScreenController::Get().ShowScreen(ScreenState::InitLoading);
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

void MainScreen::LoadData()
{
}
