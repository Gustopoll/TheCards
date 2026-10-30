#include "settingsscreen.h"
#include "ui_settingsscreen.h"

#include <QScreen>

SettingsScreen::SettingsScreen(
    ScreenController& screenController,
    SettingsController& settings,
    QWidget *parent)
    : ScreenWidget(parent)
    , ui(new Ui::SettingsScreen)
    , _screenController(screenController)
    , _settings(settings)
    , _parent(parent)
{
    ui->setupUi(this);
}

SettingsScreen::~SettingsScreen()
{
    delete ui;
}

void SettingsScreen::OnScreenActive()
{
    ui->serverPort->setText(QString(_settings.GetSettingValue(Settings::NetworkServerPort).c_str()));
    ui->checkBoxFullscreen->setChecked(_settings.GetSettingValue(Settings::GeneralFullscreen) == "true");
}

void SettingsScreen::OnScreenInactive()
{
    qDebug() << "settings are no longer active";
}

void SettingsScreen::on_pushButton_clicked()
{
    if (!_screenController.GoBack())
    {
        _screenController.ShowScreen(ScreenState::Game);
    }
}

void SettingsScreen::on_serverPort_textChanged()
{
    _settings.SetSettingValue(Settings::NetworkServerPort, ui->serverPort->text().toStdString());
}

void SettingsScreen::on_checkBoxFullscreen_checkStateChanged(const Qt::CheckState &arg1)
{
    qDebug() << "checkbox clicked" << arg1;
    if (arg1 == Qt::CheckState::Checked)
    {
        qDebug() << "on";
        ui->checkBoxFullscreen->setText("On");
        _settings.SetSettingValue(Settings::GeneralFullscreen, "true");
    }
    else
    {
        qDebug() << "off";
        ui->checkBoxFullscreen->setText("Off");
        _settings.SetSettingValue(Settings::GeneralFullscreen, "false");
    }
}
