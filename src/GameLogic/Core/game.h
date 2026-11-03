#ifndef GAME_H
#define GAME_H

#include "src/GameLogic/Core/round.h"
#include "src/GameLogic/Views/buttonview.h"
#include "src/GameLogic/Views/enemyview.h"
#include "src/GameLogic/Views/playerview.h"

#include <optional>

class DrawingWidget;
class DataPreloader;

class Game
{
public:
    Game(
        int numberOfPlayers,
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

    void StartNewRound();

private:
    void SubscribeToEvents();

    int _numberOfPlayers;
    std::optional<Round> _currentRound;

    std::optional<ButtonView> _buttonView;
    std::optional<EnemyView> _enemyView;
    std::optional<PlayerView> _playerView;

    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // GAME_H
