#include "settingsscreen.h"
#include "ui_settingsscreen.h"


#include "src/Screens/screencontroller.h"

SettingsScreen::SettingsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsScreen)
{
    ui->setupUi(this);
}

SettingsScreen::~SettingsScreen()
{
    delete ui;
}

void SettingsScreen::on_pushButton_clicked()
{
    ScreenController::Get().ShowScreen(ScreenState::Game);
}
