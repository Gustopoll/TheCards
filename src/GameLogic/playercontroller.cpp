#include "playercontroller.h"

PlayerController::PlayerController(
    DrawingWidget* drawingWidget,
    DataPreloader& dataPreloader)
    : _drawingWidget(drawingWidget)
    , _dataPreloader(dataPreloader)
{
}

void PlayerController::ShowCards()
{
    const auto cardImages = _dataPreloader.GetPreloadedImages("CardGroup");
    if (cardImages.empty())
        return;

    if (!_drawingWidget)
        return;

    const auto blockCount = _drawingWidget->GetBlockCount();

    const float pointY = blockCount.second - 4;

    uint32_t countCards = 16;
    float cardWidth = 2.0f;
    float spacing = -1.2f;
    float centerX = blockCount.first / 2.0f;

    float step = cardWidth + spacing;
    float totalWidth = countCards * step - spacing;

    float startX = centerX + totalWidth / 2.0f - cardWidth;

    for (uint32_t i = 0; i < countCards; ++i)
    {
        float x = startX - i * step;
        auto entity = _drawingWidget->CreateEntity(cardImages[i], x, pointY);
        entity->SetSizeX(cardWidth);
        entity->SetSizeY(3);
        auto group = _drawingWidget->AddEntityToGroup(entity->GetId(), "playerCards");
        group->SetMovable(true);
    }
}
