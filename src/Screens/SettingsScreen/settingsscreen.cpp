#include "settingsscreen.h"
#include "ui_settingsscreen.h"

SettingsScreen::SettingsScreen(std::vector<Settings>& settings, QWidget *parent) :
    ScreenWidget(parent),
    ui(new Ui::SettingsScreen),
    _settings(settings)
{
    ui->setupUi(this);
    _parent = parent;
}

SettingsScreen::~SettingsScreen()
{
    delete ui;
}

void SettingsScreen::OnScreenActive()
{
    qDebug() << "settings are active";
    ui->serverPort->setText(QString(_settings[1].GetSetting("Network/ServerPort").c_str()));

    const Qt::CheckState fullscreen = _settings[0].GetSetting("General/Fullscreen") == "true"
        ? Qt::CheckState::Checked
        : Qt::CheckState::Unchecked;
    ui->checkBoxFullscreen->setCheckState(fullscreen);
    ui->checkBoxFullscreen->setText(fullscreen == Qt::CheckState::Checked ? "On" : "Off");
}

void SettingsScreen::OnScreenInactive()
{
    qDebug() << "settings are no longer active";
}

void SettingsScreen::on_pushButton_clicked()
{
    ScreenController::Get().ShowScreen(ScreenState::Game);
}

void SettingsScreen::on_serverPort_textChanged()
{
    _settings[1].SetSetting("Network/ServerPort", ui->serverPort->text().toStdString());
}


void SettingsScreen::on_checkBoxFullscreen_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::CheckState::Checked)
    {
        _parent->hide();
        _parent->setWindowFlags(Qt::FramelessWindowHint);
        _parent->show();
        ui->checkBoxFullscreen->setText("On");
        _settings[0].SetSetting("General/Fullscreen", "true");
    }
    else
    {
        _parent->hide();
        _parent->setWindowFlags(Qt::Window);
        _parent->show();
        ui->checkBoxFullscreen->setText("Off");
        _settings[0].SetSetting("General/Fullscreen", "false");
    }
}

