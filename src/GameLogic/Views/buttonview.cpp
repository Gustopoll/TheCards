#include "buttonview.h"

#include "src/Drawing/Widgets/drawingwidget.h"
#include "src/Drawing/Entities/drawingentity.h"
#include "src/Utils/datapreloader.h"
#include "src/Utils/assets.h"

#include <QDebug>

ButtonView::ButtonView(
    DrawingWidget* drawingWidget,
    DataPreloader& dataPreloader)
    : _drawingWidget(drawingWidget)
    , _dataPreloader(dataPreloader)
{
}

void ButtonView::Show()
{
    const auto buttonsImages = _dataPreloader.GetPreloadedImages(Assets::Buttons::kGroup);
    if (buttonsImages.empty())
        return;

    const auto endTurnImage = buttonsImages[Assets::Buttons::kEndTurn];
    const auto noCardsImage = buttonsImages[Assets::Buttons::kNoCards];
    const auto backCardImage = buttonsImages[Assets::Buttons::kBackCard];

    auto buttonId = _drawingWidget->CreateEntity(endTurnImage, 0, 5, 1, 1);
    _drawingWidget->SetEntityAsClickable(buttonId);

    buttonId = _drawingWidget->CreateEntity(noCardsImage, 8.5, 1, 2, 3);
    _drawingWidget->SetEntityAsClickable(buttonId);

    buttonId = _drawingWidget->CreateEntity(backCardImage, 5.5, 1, 2, 3);
    _drawingWidget->SetEntityAsClickable(buttonId);
}

void ButtonView::OnEntityPressed(std::shared_ptr<DrawingEntity> entity)
{
    qDebug() << entity->GetId() << " is pressed";
    entity->HighlightBorders(Qt::yellow);
    _drawingWidget->update();
}

void ButtonView::OnEntityReleased(std::shared_ptr<DrawingEntity> entity)
{
    qDebug() << entity->GetId() << " is released";
    entity->ResetHighlightedBorders();
    _drawingWidget->update();
}
