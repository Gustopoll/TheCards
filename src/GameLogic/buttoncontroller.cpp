#include "buttoncontroller.h"

#include "src/Drawing/Widgets/drawingwidget.h"
#include "src/Utils/datapreloader.h"

#include "src/Utils/assets.h"

ButtonController::ButtonController(
    DrawingWidget* drawingWidget,
    DataPreloader& dataPreloader)
    : _drawingWidget(drawingWidget)
    , _dataPreloader(dataPreloader)
{
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

void ButtonController::OnEntityPressed(std::shared_ptr<DrawingEntity> entity)
{
    qDebug() << entity->GetId() << " is pressed";
    entity->HighlightBorders(Qt::yellow);
    _drawingWidget->update();
}

void ButtonController::OnEntityReleased(std::shared_ptr<DrawingEntity> entity)
{
    qDebug() << entity->GetId() << " is released";
    entity->ResetHighlightedBorders();
    _drawingWidget->update();
}
