#include "enemycontroller.h"

#include "src/Utils/assets.h"

EnemyController::EnemyController(
    DrawingWidget* drawingWidget,
    DataPreloader& dataPreloader)
    : _drawingWidget(drawingWidget)
    , _dataPreloader(dataPreloader)
{
    SubscribeToEvents();
}

void EnemyController::Show(const std::vector<Enemy>& enemies)
{
    const size_t count = std::min(enemies.size(), _slots.size());
    if (count <= 0)
        return;

    const auto buttonsImages = _dataPreloader.GetPreloadedImages(Assets::kButtonsGroup);
    if (buttonsImages.empty())
        return;

    const auto& backCardImage = buttonsImages[2];

    for (size_t i = 0; i < count; ++i)
    {
        const auto& slot = _slots[i];
        const auto& enemy = enemies[i];
        ShowEnemy(slot, enemy, backCardImage);
    }
}

void EnemyController::ShowEnemy(
    const Slot& slot,
    const Enemy& enemy,
    const std::shared_ptr<QImage>& backCardImage)
{
    const float slotWidth = 4;
    const auto backgrounds = _dataPreloader.GetPreloadedImages(Assets::kBackgroundsGroup);
    if (!backgrounds.empty())
    {
        float posX = slot.reverseDirection
            ? slot.x - slotWidth
            : slot.x - 0.6;
        float posY = slot.y - 0.75;

        _drawingWidget->CreateEntity(backgrounds[0], posX, posY, 5, 2);
    }

    float cardWidth = 0.5f;
    float cardHeight = 0.75f;
    float spacing = 0.25f;
    float rowSpacing = 0.37f;

    float step = slot.reverseDirection
         ? (cardWidth - spacing) * -1.0f
         : spacing;

    const uint32_t cardsPerRow = 16;

    for (uint32_t i = 0; i < enemy.countCards; ++i)
    {
        uint32_t row = i / cardsPerRow;
        uint32_t col = i % cardsPerRow;

        float x = slot.x + col * step;
        float y = slot.y + row * rowSpacing;

        _drawingWidget->CreateEntity(
            backCardImage,
            x,
            y,
            cardWidth,
            cardHeight);
    }

    float textPosX = slot.reverseDirection
        ? slot.x - slotWidth + 0.3
        : slot.x;

    _drawingWidget->ShowText(enemy.name, textPosX, slot.y - 0.3, 0.25, Qt::blue);
}

void EnemyController::SubscribeToEvents()
{
    _drawingWidget->GetEntityPressedEvent().Subscribe(
        [this](const std::shared_ptr<DrawingEntity> pressedEntity)
        {
        });

    _drawingWidget->GetEntityReleasedEvent().Subscribe(
        [this](const std::shared_ptr<DrawingEntity> pressedEntity)
        {
        });
}
