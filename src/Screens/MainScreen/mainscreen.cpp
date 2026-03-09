#include "mainscreen.h"
#include "ui_mainscreen.h"

#include "src/Screens/screencontroller.h"
#include "src/Screens/SettingsScreen/settingsscreen.h"
#include "src/Screens/GameScreen/gamescreen.h"
#include "src/Screens/Loadings/loadingscreen.h"

#include <QDebug>

MainScreen::MainScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScreen)
{
    ui->setupUi(this);

    _allSettings.emplace_back("Data/Settings/General");
    _allSettings.emplace_back("Data/Settings/Network");
    _allSettings[0].SetSettingDefault("General/Fullscreen", "false");
    _allSettings[1].SetSettingDefault("Network/ServerPort", "3652");
    _allSettings[0].ReadSettings();
    _allSettings[1].ReadSettings();

    std::vector<std::string> cardPaths
    {
        "Data/Cards/A-0A.png",
        "Data/Cards/A-07.png",
        "Data/Cards/A-08.png",
        "Data/Cards/A-09.png",
        "Data/Cards/A-10.png",
        "Data/Cards/A-J1.png",
        "Data/Cards/A-J2.png",
        "Data/Cards/A-KI.png",
        "Data/Cards/B-0A.png",
        "Data/Cards/B-07.png",
        "Data/Cards/B-08.png",
        "Data/Cards/B-09.png",
        "Data/Cards/B-10.png",
        "Data/Cards/B-J1.png",
        "Data/Cards/B-J2.png",
        "Data/Cards/B-KI.png",
        "Data/Cards/H-0A.png",
        "Data/Cards/H-07.png",
        "Data/Cards/H-08.png",
        "Data/Cards/H-09.png",
        "Data/Cards/H-10.png",
        "Data/Cards/H-J1.png",
        "Data/Cards/H-J2.png",
        "Data/Cards/H-KI.png",
        "Data/Cards/L-0A.png",
        "Data/Cards/L-07.png",
        "Data/Cards/L-08.png",
        "Data/Cards/L-09.png",
        "Data/Cards/L-10.png",
        "Data/Cards/L-J1.png",
        "Data/Cards/L-J2.png",
        "Data/Cards/L-KI.png"
    };
    _dataPreloader.PreloadImages("CardGroup", cardPaths);

    ScreenController::Get().Initialize(this, ui->stackedWidget);
    ScreenController::Get().CreateScreen(ScreenState::Game, new GameScreen(this));
    ScreenController::Get().CreateScreen(ScreenState::Settings, new SettingsScreen(_allSettings, this));
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::Start()
{
    _loadingScreen = new LoadingScreen(_dataPreloader, this);
    _loadingScreen->show();
}

void MainScreen::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
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
    //hide();
    //ScreenController::Get().ShowScreen(ScreenState::Settings);
    //setWindowFlags(Qt::FramelessWindowHint);
    //show();
    //setGeometry(g);
}

void MainScreen::LoadData()
{
}
