#include "gamescreen.h"
#include "ui_gamescreen.h"

#include <QDebug>

GameScreen::GameScreen(
    ScreenManager& screenManager,
    DataPreloader& dataPreloader,
    QWidget *parent)
    : ScreenWidget(parent)
    , ui(new Ui::GameScreen)
    , _screenManager(screenManager)
    , _dataPreloader(dataPreloader)
    , _parent(parent)
{
    ui->setupUi(this);

    ui->drawingWidget->Initialize(16, 9);
    ui->drawingWidget->ShowGrid(true);
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::OnScreenActive()
{
    _game.emplace(5, ui->drawingWidget, _dataPreloader);
}

void GameScreen::OnScreenInactive()
{
    _game.reset();
}

void GameScreen::on_pushButton_clicked()
{
    _screenManager.ShowScreen(ScreenState::Settings);
}
