#include "gamescreen.h"
#include "ui_gamescreen.h"

#include <QDebug>

GameScreen::GameScreen(
    DataPreloader& dataPreloader,
    QWidget *parent)
    : ScreenWidget(parent)
    , ui(new Ui::GameScreen)
    , _dataPreloader(dataPreloader)
    , _parent(parent)
{
    ui->setupUi(this);

    ui->drawingWidget->Initialize(16, 9);
    ui->drawingWidget->ShowGrid(true);

    _playerController.emplace(ui->drawingWidget, _dataPreloader);
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::OnScreenActive()
{
    _playerController->ShowCards();
}

void GameScreen::OnScreenInactive()
{
}

void GameScreen::on_pushButton_clicked()
{
    ScreenController::Get().ShowScreen(ScreenState::Settings);
}
