#include "gamescreen.h"
#include "ui_gamescreen.h"

#include "src/Screens/screencontroller.h"

GameScreen::GameScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameScreen)
{
    ui->setupUi(this);
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::on_pushButton_clicked()
{
    ScreenController::Get().ShowScreen(ScreenState::Settings);
}
