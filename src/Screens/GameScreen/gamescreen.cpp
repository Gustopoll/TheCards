#include "gamescreen.h"
#include "ui_gamescreen.h"

#include <QDebug>

GameScreen::GameScreen(QWidget *parent) :
    ScreenWidget(parent),
    ui(new Ui::GameScreen)
{
    ui->setupUi(this);
    _parent = parent;
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::OnScreenActive()
{
    qDebug() << "game are active";
    if (!_game)
    {
        qDebug() << "init game started";
        _game.emplace();
        qDebug() << "inint game ended";
    }
}

void GameScreen::OnScreenInactive()
{
    qDebug() << "game are no longer active";
}

void GameScreen::on_pushButton_clicked()
{
    ScreenController::Get().ShowScreen(ScreenState::Settings);
}
