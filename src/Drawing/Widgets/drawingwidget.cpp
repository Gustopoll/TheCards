#include "drawingwidget.h"
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include "src/Drawing/Animations/animationmanager.h"

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent)
{
}

void DrawingWidget::Initialize(uint32_t maxSizeX, uint32_t maxSizeY)
{
    _maxSizeX = maxSizeX;
    _maxSizeY = maxSizeY;
    _isInitialized = true;
}

uint32_t DrawingWidget::CreateEntity(
    const std::shared_ptr<QImage> image,
    const float x,
    const float y,
    const float sizeX,
    const float sizeY)
{
   const auto entity = std::make_shared<DrawingEntity>(image, x, y, sizeX, sizeY);

   const auto id = entity->GetId();
   _entities[id] = entity;

   return id;
}

const std::shared_ptr<DrawingEntity> DrawingWidget::GetEntity(uint32_t id)
{
    auto e = _entities.find(id);
    if (e == _entities.end())
        return nullptr;

    return e->second;
}

void DrawingWidget::SetEntityAsMovable(uint32_t id)
{
    const auto entity = GetEntity(id);
    if (!entity)
        return;

    _movableEntities.try_emplace(id, entity);
}

void DrawingWidget::SetEntityAsClickable(uint32_t id)
{
    const auto entity = GetEntity(id);
    if (!entity)
        return;

    _clickableEntities.try_emplace(id, entity);
}

void DrawingWidget::MoveEntityTo(uint32_t id, float x, float y)
{
    if (!_isInitialized)
        return;

    const auto entity = GetEntity(id);
    if (!entity)
        return;

    entity->SetPosX(x);
    entity->SetPosY(y);
    update();
}

void DrawingWidget::ShowGrid(bool enable)
{
    if (!_isInitialized)
        return;

    _showGrid = enable;
    update();
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    // Do not render anything until DrawingWidget is initialized.
    if (!_isInitialized)
        return;

    event->accept();

    QPen defaultPen;
    QPainter painter(this);

    if (_showGrid)
    {
        for (uint32_t y = 0; y < _maxSizeY; ++y)
        {
            for (uint32_t x = 0; x < _maxSizeX; ++x)
            {
                const auto [posX, posY] = ConvertBlockToPixels(x, y);
                painter.drawRect(posX, posY, _currentSizeX, _currentSizeY);
            }
        }
    }

    for (const auto& [_, item] : _entities)
    {
        const float sizeX = _currentSizeX * item->GetSizeX();
        const float sizeY = _currentSizeY * item->GetSizeY();
        const auto [x, y] = ConvertBlockToPixels(item->GetPosX(), item->GetPosY());
        painter.drawImage(x, y, item->GetImage()->scaled(sizeX, sizeY/*, Qt::KeepAspectRatio*/));

        if (item->IsHighlighted())
        {
            QPen pen;
            pen.setColor(item->GetHighlightColor());
            pen.setWidth(_currentSizeX / 10);
            painter.setPen(pen);
            painter.drawRect(x, y, sizeX, sizeY);

            painter.setPen(defaultPen);
        }
    }
}

void DrawingWidget::resizeEvent(QResizeEvent *event)
{
    if (!_isInitialized)
        return;

    event->accept();

    // Size of one block (in pixels)
    const float x = width() / static_cast<float>(_maxSizeX);
    const float y = height() / static_cast<float>(_maxSizeY);

    const auto oneBlock = std::min(x, y);
    _currentSizeX = oneBlock;
    _currentSizeY = oneBlock;

    _currentOffsetX = (width() - oneBlock * _maxSizeX) * 0.5f;
    _currentOffsetY = (height() - oneBlock * _maxSizeY) * 0.5f;
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    if (!_isInitialized)
        return;

    const auto clickedEntity = GetEntityByPosition(event->pos());

    if (clickedEntity)
    {
        const auto [clickedBlockX, clickedBlockY] = ConvertPixelsToBlock(event->pos());

        _clickedEntities.emplace(
            event->button(),
            ClickedData{
                clickedBlockX - clickedEntity->GetPosX(),
                clickedBlockY - clickedEntity->GetPosY(),
                clickedEntity
            });

        if (_clickableEntities.contains(clickedEntity->GetId()))
            _entityPressedEvent.Fire(clickedEntity);
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!_isInitialized)
        return;

    const auto item = _clickedEntities.find(event->button());
    if (item == _clickedEntities.end())
        return;

    const auto& clickedData = item->second;
    if (clickedData.entity && _clickableEntities.contains(clickedData.entity->GetId()))
    {
        _entityReleasedEvent.Fire(clickedData.entity);
    }

    _clickedEntities.erase(event->button());
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!_isInitialized)
        return;

    const auto item = _clickedEntities.find(Qt::MouseButton::LeftButton);
    if (item == _clickedEntities.end())
        return;

    auto& clickedData = item->second;
    if (!clickedData.entity || !_movableEntities.contains(clickedData.entity->GetId()))
        return;

    const auto [posX, posY] = ConvertPixelsToBlock(event->pos());
    clickedData.entity->SetPosX(posX - clickedData.clickedOffsetX);
    clickedData.entity->SetPosY(posY - clickedData.clickedOffsetY);
    update();
}

std::shared_ptr<DrawingEntity> DrawingWidget::GetEntityByPosition(const QPoint& position)
{
    for (const auto& [_, entity] : _clickableEntities | std::views::reverse)
    {
        if (IsPositionInsideEntity(entity, position))
            return entity;
    }

    for (const auto& [_, entity] : _movableEntities  | std::views::reverse)
    {
        if (IsPositionInsideEntity(entity, position))
            return entity;
    }

    return nullptr;
}

bool DrawingWidget::IsPositionInsideEntity(const std::shared_ptr<DrawingEntity>& entity, const QPoint& position)
{
    const auto [entityX, entityY] = ConvertBlockToPixels(entity->GetPosX(), entity->GetPosY());
    const float entitySizeX = entityX + _currentSizeX * entity->GetSizeX();
    const float entitySizeY = entityY + _currentSizeY * entity->GetSizeY();

    if (entityX > position.x() || entitySizeX < position.x())
        return false;

    if (entityY > position.y() || entitySizeY < position.y())
        return false;

    return true;
}

QPoint DrawingWidget::ConvertBlockToPixels(float x, float y)
{
    const int pixelsX = x * _currentSizeX + _currentOffsetX;
    const int pixelsY = y * _currentSizeY + _currentOffsetY;
    return {pixelsX, pixelsY};
}

std::pair<float, float> DrawingWidget::ConvertPixelsToBlock(const QPoint& position)
{
    const float blockX = (position.x() - _currentOffsetX) / _currentSizeX;
    const float blockY = (position.y() - _currentOffsetY) / _currentSizeY;
    return {blockX, blockY};
}
