#include "game.h"

#include "src/Drawing/Widgets/drawingwidget.h"
#include "src/Utils/datapreloader.h"

Game::Game(
    int numberOfPlayers,
    DrawingWidget* drawingWidget,
    DataPreloader& dataPreloader)
    : _numberOfPlayers(numberOfPlayers)
    , _drawingWidget(drawingWidget)
    , _dataPreloader(dataPreloader)
{
    _buttonView.emplace(_drawingWidget, _dataPreloader);
    _enemyView.emplace(_drawingWidget, _dataPreloader);
    _playerView.emplace(_drawingWidget, _dataPreloader);

    _buttonView->Show();
    _enemyView->Show({ {"Player1", 16}, {"Player2", 20}, {"Player3", 22}, {"Player4", 16}});
    _playerView->ShowCards();

    SubscribeToEvents();
    StartNewRound();
}

void Game::StartNewRound()
{
    _currentRound.emplace();
    _currentRound->Start();
}

void Game::SubscribeToEvents()
{
    _drawingWidget->GetEntityPressedEvent().Subscribe(
        [this](std::shared_ptr<DrawingEntity> entity)
        {
            _buttonView->OnEntityPressed(entity);
        });

    _drawingWidget->GetEntityReleasedEvent().Subscribe(
        [this](std::shared_ptr<DrawingEntity> entity)
        {
            _buttonView->OnEntityReleased(entity);
        });
}
