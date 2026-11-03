#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "src/Screens/screenmanager.h"
#include "src/GameLogic/Core/game.h"
#include "src/Utils/datapreloader.h"

#include <QWidget>

namespace Ui {
class GameScreen;
}

class GameScreen : public ScreenWidget
{
    Q_OBJECT

public:
    GameScreen(
        ScreenManager& screenManager,
        DataPreloader& dataPreloader,
        QWidget *parent = nullptr);
    ~GameScreen() override;

    void OnScreenActive() override;
    void OnScreenInactive() override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::GameScreen *ui;

    ScreenManager& _screenManager;
    std::optional<Game> _game;

    DataPreloader& _dataPreloader;
    QWidget* _parent;
};

#endif // GAMESCREEN_H
