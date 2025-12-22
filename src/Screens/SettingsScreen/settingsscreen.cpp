#include "settingsscreen.h"
#include "ui_settingsscreen.h"

#include "src/Screens/screencontroller.h"

SettingsScreen::SettingsScreen(std::vector<Settings>& settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsScreen),
    _settings(settings)
{
    ui->setupUi(this);
    ui->serverPort->setText(QString(_settings[0].GetSetting("Network/ServerPort").c_str()));
}

SettingsScreen::~SettingsScreen()
{
    delete ui;
}

void SettingsScreen::on_pushButton_clicked()
{
    ScreenController::Get().ShowScreen(ScreenState::Game);
}

void SettingsScreen::on_serverPort_textChanged()
{
    _settings[0].SetSetting("Network/ServerPort", ui->serverPort->text().toStdString());
}

