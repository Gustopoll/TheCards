#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "src/Screens/screencontroller.h"
#include "src/GameLogic/game.h"
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
        DataPreloader& dataPreloader,
        QWidget *parent = nullptr);
    ~GameScreen();

    void OnScreenActive() override;
    void OnScreenInactive() override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::GameScreen *ui;

    std::optional<Game> _game;

    DataPreloader& _dataPreloader;
    QWidget* _parent;
};

#endif // GAMESCREEN_H
