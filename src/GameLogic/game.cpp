#include "game.h"

#include "src/Drawing/Widgets/drawingwidget.h"
#include "src/Utils/datapreloader.h"

Game::Game(
    int numberOfPlayers,
    DrawingWidget* drawingWidget,
    DataPreloader& dataPreloader)
    : _drawingWidget(drawingWidget)
    , _dataPreloader(dataPreloader)
{
    _buttonController.emplace(_drawingWidget, _dataPreloader);
    _enemyController.emplace(_drawingWidget, _dataPreloader);
    _playerController.emplace(_drawingWidget, _dataPreloader);

    _buttonController->Show();
    _enemyController->Show({ {"Player1", 16}, {"Player2", 20}, {"Player3", 22}, {"Player4", 16}});
    _playerController->ShowCards();

    SubscribeToEvents();
}

void Game::SubscribeToEvents()
{
    _drawingWidget->GetEntityPressedEvent().Subscribe(
        [this](std::shared_ptr<DrawingEntity> entity)
        {
            _buttonController->OnEntityPressed(entity);
        });

    _drawingWidget->GetEntityReleasedEvent().Subscribe(
        [this](std::shared_ptr<DrawingEntity> entity)
        {
            _buttonController->OnEntityReleased(entity);
        });
}
