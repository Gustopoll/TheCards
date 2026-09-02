#include "playercontroller.h"

#include "src/Utils/assets.h"

PlayerController::PlayerController(
    DrawingWidget* drawingWidget,
    DataPreloader& dataPreloader)
    : _drawingWidget(drawingWidget)
    , _dataPreloader(dataPreloader)
{
}

void PlayerController::ShowCards()
{
    const auto cardImages = _dataPreloader.GetPreloadedImages(Assets::kCardsGroup);
    if (cardImages.empty())
        return;

    if (!_drawingWidget)
        return;

    const auto blockCount = _drawingWidget->GetBlockCount();

    uint32_t countCards = 16;
    float cardWidth = 2.0f;
    float cardHeight = 3.0f;
    float spacing = -1.2f;
    float centerX = blockCount.first / 2.0f;

    float step = cardWidth + spacing;
    float totalWidth = countCards * step - spacing;

    float startX = centerX + totalWidth / 2.0f - cardWidth;
    float startY = blockCount.second - 4;

    auto cards = std::vector<std::shared_ptr<QImage>>(cardImages.begin(), cardImages.begin() + 16);
    ShowCards(cards, startX, startY, cardWidth, cardHeight, step);

    cards = std::vector<std::shared_ptr<QImage>>(cardImages.begin() + 16, cardImages.begin() + 32);
    ShowCards(cards, startX, startY + 1, cardWidth, cardHeight, step);
}

void PlayerController::ShowCards(
    const std::vector<std::shared_ptr<QImage>>& cards,
    const float startPosX,
    const float startPosY,
    const float cardWidth,
    const float cardHeight,
    const float step)
{
    if (!_drawingWidget)
        return;

    for (uint32_t i = 0; i < cards.size(); ++i)
    {
        float x = startPosX - i * step;
        const auto id = _drawingWidget->CreateEntity(cards[i], x, startPosY, cardWidth, cardHeight);
        _drawingWidget->SetEntityAsMovable(id);
    }
}

void PlayerController::OnCardPressed(
    std::shared_ptr<DrawingEntity> entity,
    const Qt::MouseButton button)
{
    if (button == Qt::MouseButton::LeftButton)
    {
        _cardPositions.insert({
            entity->GetId(),
            QPointF(entity->GetPosX(), entity->GetPosY())});
    }
}

void PlayerController::OnCardReleased(
    std::shared_ptr<DrawingEntity> entity,
    const Qt::MouseButton button)
{
    if (button == Qt::MouseButton::LeftButton)
    {
        auto foundEntity = _drawingWidget->GetOverlappingEntity(entity->GetId());
        if (foundEntity)
        {
            //if (foundEntity->GetId())
        }

    }
}
