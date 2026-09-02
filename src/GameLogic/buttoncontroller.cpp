#include "buttoncontroller.h"

#include "src/Utils/assets.h"

ButtonController::ButtonController(
    DrawingWidget* drawingWidget,
    DataPreloader& dataPreloader)
    : _drawingWidget(drawingWidget)
    , _dataPreloader(dataPreloader)
{
    SubscribeToEvents();
}

void ButtonController::Show()
{
    const auto buttonsImages = _dataPreloader.GetPreloadedImages(Assets::kButtonsGroup);
    if (buttonsImages.empty())
        return;

    const auto endTurnImage = buttonsImages[0];
    const auto noCardsImage = buttonsImages[1];
    const auto backCardImage = buttonsImages[2];

    auto buttonId = _drawingWidget->CreateEntity(endTurnImage, 0, 5, 1, 1);
    _drawingWidget->SetEntityAsClickable(buttonId);

    buttonId = _drawingWidget->CreateEntity(noCardsImage, 8.5, 1, 2, 3);
    _drawingWidget->SetEntityAsClickable(buttonId);

    buttonId = _drawingWidget->CreateEntity(backCardImage, 5.5, 1, 2, 3);
    _drawingWidget->SetEntityAsClickable(buttonId);
}


void ButtonController::SubscribeToEvents()
{
    _drawingWidget->GetEntityPressedEvent().Subscribe(
        [this](const std::shared_ptr<DrawingEntity> pressedEntity)
        {
            qDebug() << pressedEntity->GetId() << " is pressed";
            pressedEntity->HighlightBorders(Qt::yellow);
            _drawingWidget->update();
        });

    _drawingWidget->GetEntityReleasedEvent().Subscribe(
        [this](const std::shared_ptr<DrawingEntity> pressedEntity)
        {
            qDebug() << pressedEntity->GetId() << " is released";
            pressedEntity->ResetHighlightedBorders();
            _drawingWidget->update();
        });
}
