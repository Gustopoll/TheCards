#include "mainscreen.h"
#include "ui_mainscreen.h"

#include "src/Utils/assets.h"
#include "src/Screens/screencontroller.h"
#include "src/Screens/SettingsScreen/settingsscreen.h"
#include "src/Screens/GameScreen/gamescreen.h"
#include "src/Screens/Loadings/loadingscreen.h"

#include <QScreen>
#include <QDebug>

MainScreen::MainScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScreen)
{
    ui->setupUi(this);

    std::vector<std::string> cardPaths
    {
        Assets::kCardA0APath,
        Assets::kCardA07Path,
        Assets::kCardA08Path,
        Assets::kCardA09Path,
        Assets::kCardA10Path,
        Assets::kCardAJ1Path,
        Assets::kCardAJ2Path,
        Assets::kCardAKIPath,
        Assets::kCardB0APath,
        Assets::kCardB07Path,
        Assets::kCardB08Path,
        Assets::kCardB09Path,
        Assets::kCardB10Path,
        Assets::kCardBJ1Path,
        Assets::kCardBJ2Path,
        Assets::kCardBKIPath,
        Assets::kCardH0APath,
        Assets::kCardH07Path,
        Assets::kCardH08Path,
        Assets::kCardH09Path,
        Assets::kCardH10Path,
        Assets::kCardHJ1Path,
        Assets::kCardHJ2Path,
        Assets::kCardHKIPath,
        Assets::kCardL0APath,
        Assets::kCardL07Path,
        Assets::kCardL08Path,
        Assets::kCardL09Path,
        Assets::kCardL10Path,
        Assets::kCardLJ1Path,
        Assets::kCardLJ2Path,
        Assets::kCardLKIPath
    };
    _dataPreloader.PreloadImages(Assets::kCardsGroup, cardPaths);

    std::vector<std::string> boardButtonsPaths
    {
        Assets::kButtonEndTurnPath,
        Assets::kButtonNoCardsPath,
        Assets::kButtonBackCardPath
    };
    _dataPreloader.PreloadImages(Assets::kBoardButtonsGroup, boardButtonsPaths);


    ScreenController::Get().Initialize(this, ui->stackedWidget);
    ScreenController::Get().CreateScreen(ScreenState::Game, new GameScreen(_dataPreloader, this));
    ScreenController::Get().CreateScreen(ScreenState::Settings, new SettingsScreen(_settingsController, this));

    _settingsController.GetSettingChangedEvent().Subscribe(
        [this](const std::string& path, const std::string& value)
        {
            if (path != Settings::GeneralFullscreen)
                return;

            if (value == "true")
            {
                // TODO add new setting to select available screen e.g. qDebug() << QGuiApplication::screens();
                hide();
                const auto* screen = QGuiApplication::primaryScreen();
                setGeometry(screen->virtualGeometry());
                setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowStaysOnTopHint*/);

                if (_loadingScreen)
                    show();
            }
            else
            {
                hide();
                setWindowFlags(Qt::Window /*| Qt::WindowStaysOnTopHint*/);

                if (_loadingScreen)
                    show();
            }
        });
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

void MainScreen::OnLoadingFinished()
{
    show();
    _loadingScreen->hide();
    _settingsController.Load();
    ScreenController::Get().ShowScreen(ScreenState::Game);
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
