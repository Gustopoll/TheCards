#ifndef GAME_H
#define GAME_H

#include "src/GameLogic/buttoncontroller.h"
#include "src/GameLogic/enemycontroller.h"
#include "src/GameLogic/playercontroller.h"

#include <QString>

class DrawingWidget;
class DataPreloader;

class Game
{
public:
    Game(
        int numberOfPlayers,
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

private:

    void SubscribeToEvents();

    std::optional<ButtonController> _buttonController;
    std::optional<EnemyController> _enemyController;
    std::optional<PlayerController> _playerController;

    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // GAME_H
