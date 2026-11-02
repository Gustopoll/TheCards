#include "drawingwidget.h"
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <algorithm>
#include <cassert>

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
    if (!_isInitialized)
    {
        assert(false && "Entity is created before the widget is initialized.");
        return 0;
    }

    const auto entity = std::make_shared<DrawingEntity>(image, x, y, sizeX, sizeY);

    const auto id = entity->GetId();
    _entities[id] = entity;
    _orderedEntities.push_back(entity);
    _isOrderDirty = true;

    return id;
}

bool DrawingWidget::RemoveEntity(const uint32_t id)
{
    auto it = _entities.find(id);
    if (it == _entities.end())
        return false;

    for (auto clickedIt = _clickedEntities.begin(); clickedIt != _clickedEntities.end(); )
    {
        if (clickedIt->second.entity && clickedIt->second.entity->GetId() == id)
            clickedIt = _clickedEntities.erase(clickedIt);
        else
            ++clickedIt;
    }

    _entities.erase(it);

    std::erase_if(
        _orderedEntities,
        [id](const auto& entity)
        {
            return entity->GetId() == id;
        });

    update();
    return true;
}

void DrawingWidget::ClearEntities()
{
    if (!_isInitialized)
        return;

    _clickedEntities.clear();
    _entities.clear();
    _orderedEntities.clear();
    _isOrderDirty = false;
    update();
}

uint32_t DrawingWidget::ShowText(
    const QString& text,
    const float x,
    const float y,
    const float pixelSize,
    const QColor color)
{
    if (!_isInitialized)
        return 0;

    const uint32_t id = _nextTextId++;
    _textEntities.emplace_back(DrawingTextEntity{id, text, x, y, pixelSize, color});
    update();
    return id;
}

bool DrawingWidget::UpdateText(const uint32_t id, const QString& text, const QColor& color)
{
    if (!_isInitialized)
        return false;

    auto it = std::ranges::find_if(_textEntities, [id](const auto& item) {
        return item.id == id;
    });

    if (it == _textEntities.end())
        return false;

    it->text = text;
    it->color = color;
    update();
    return true;
}

bool DrawingWidget::UpdateText(const uint32_t id, const QString& text)
{
    if (!_isInitialized)
        return false;

    auto it = std::ranges::find_if(_textEntities, [id](const auto& item) {
        return item.id == id;
    });

    if (it == _textEntities.end())
        return false;

    it->text = text;
    update();
    return true;
}

bool DrawingWidget::RemoveText(const uint32_t id)
{
    if (!_isInitialized)
        return false;

    const auto count = std::erase_if(_textEntities, [id](const auto& item) {
        return item.id == id;
    });

    if (count > 0)
    {
        update();
        return true;
    }
    return false;
}

void DrawingWidget::ClearText()
{
    if (!_isInitialized)
        return;

    _textEntities.clear();
    update();
}

std::shared_ptr<DrawingEntity> DrawingWidget::GetEntity(const uint32_t id) const
{
    auto e = _entities.find(id);
    if (e == _entities.end())
        return nullptr;

    return e->second;
}

void DrawingWidget::SetEntityAsMovable(const uint32_t id, const bool movable)
{
    const auto entity = GetEntity(id);
    if (!entity)
        return;

    entity->SetMovable(movable);
}

void DrawingWidget::SetEntityAsClickable(const uint32_t id, const bool clickable)
{
    const auto entity = GetEntity(id);
    if (!entity)
        return;

    entity->SetClickable(clickable);
}

void DrawingWidget::SetEntityVisible(const uint32_t id, const bool visible)
{
    const auto entity = GetEntity(id);
    if (!entity)
        return;

    entity->SetVisible(visible);
    update();
}

void DrawingWidget::SetEntityOpacity(const uint32_t id, const float opacity)
{
    const auto entity = GetEntity(id);
    if (!entity)
        return;

    entity->SetOpacity(opacity);
    update();
}

float DrawingWidget::GetEntityOpacity(const uint32_t id) const
{
    const auto entity = GetEntity(id);
    if (entity)
        return entity->GetOpacity();
    return 1.0f;
}

void DrawingWidget::SetEntityZIndex(const uint32_t id, const int zIndex)
{
    const auto entity = GetEntity(id);
    if (!entity)
        return;

    entity->SetZIndex(zIndex);
    _isOrderDirty = true;
    update();
}

int DrawingWidget::GetEntityZIndex(const uint32_t id) const
{
    const auto entity = GetEntity(id);
    if (entity)
        return entity->GetZIndex();
    return 0;
}

void DrawingWidget::BringEntityToFront(const uint32_t id)
{
    const auto entity = GetEntity(id);
    if (!entity || _orderedEntities.empty())
        return;

    int maxZ = 0;
    for (const auto& item : _orderedEntities)
    {
        maxZ = std::max(maxZ, item->GetZIndex());
    }

    entity->SetZIndex(maxZ + 1);
    _isOrderDirty = true;
    update();
}

void DrawingWidget::SendEntityToBack(const uint32_t id)
{
    const auto entity = GetEntity(id);
    if (!entity || _orderedEntities.empty())
        return;

    int minZ = 0;
    for (const auto& item : _orderedEntities)
    {
        minZ = std::min(minZ, item->GetZIndex());
    }

    entity->SetZIndex(minZ - 1);
    _isOrderDirty = true;
    update();
}

void DrawingWidget::EnsureEntitiesSorted()
{
    if (!_isOrderDirty)
        return;

    std::ranges::stable_sort(
        _orderedEntities,
        [](const auto& a, const auto& b) {
            return a->GetZIndex() < b->GetZIndex();
        });

    _isOrderDirty = false;
}

void DrawingWidget::MoveEntityTo(const uint32_t id, const float x, const float y)
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

void DrawingWidget::ShowGrid(const bool enable)
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

    EnsureEntitiesSorted();

    QPen defaultPen;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

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

    for (const auto& item : _orderedEntities)
    {
        if (!item->IsVisible())
            continue;

        const float sizeX = _currentSizeX * item->GetSizeX();
        const float sizeY = _currentSizeY * item->GetSizeY();
        const auto [x, y] = ConvertBlockToPixels(item->GetPosX(), item->GetPosY());
        const auto image = item->GetImage();

        const float opacity = item->GetOpacity();
        const bool hasCustomOpacity = (opacity < 1.0f);
        if (hasCustomOpacity)
        {
            painter.setOpacity(opacity);
        }

        if (image && !image->isNull())
        {
            painter.drawImage(QRectF(x, y, sizeX, sizeY), *image);
        }

        if (item->IsHighlighted())
        {
            QPen pen;
            pen.setColor(item->GetHighlightColor());
            pen.setWidth(_currentSizeX / 10);
            painter.setPen(pen);
            painter.drawRect(x, y, sizeX, sizeY);

            painter.setPen(defaultPen);
        }

        if (hasCustomOpacity)
        {
            painter.setOpacity(1.0f);
        }
    }

    for (const auto& item : _textEntities)
    {
        const auto [x, y] = ConvertBlockToPixels(item.x, item.y);

        QFont font = painter.font();
        font.setPixelSize(item.pixelSize * _currentSizeX);
        painter.setFont(font);

        QPen pen(item.color);
        painter.setPen(pen);
        painter.drawText(x, y, item.text);
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

        _clickedEntities[event->button()] = ClickedData{
            clickedBlockX - clickedEntity->GetPosX(),
            clickedBlockY - clickedEntity->GetPosY(),
            clickedEntity
        };

        if (clickedEntity->IsMovable() && event->button() == Qt::LeftButton)
        {
            BringEntityToFront(clickedEntity->GetId());
            update();
        }

        if (clickedEntity->IsClickable())
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
    if (clickedData.entity && clickedData.entity->IsClickable())
    {
        _entityReleasedEvent.Fire(clickedData.entity);
    }

    _clickedEntities.erase(item);
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!_isInitialized)
        return;

    const auto item = _clickedEntities.find(Qt::MouseButton::LeftButton);
    if (item == _clickedEntities.end())
        return;

    auto& clickedData = item->second;
    if (!clickedData.entity || !clickedData.entity->IsMovable())
        return;

    const auto [posX, posY] = ConvertPixelsToBlock(event->pos());
    clickedData.entity->SetPosX(posX - clickedData.clickedOffsetX);
    clickedData.entity->SetPosY(posY - clickedData.clickedOffsetY);
    update();
}

std::shared_ptr<DrawingEntity> DrawingWidget::GetEntityByPosition(const QPoint& position)
{
    EnsureEntitiesSorted();

    // Iterate backwards (from highest Z-index / top-most to lowest / bottom-most)
    for (auto it = _orderedEntities.rbegin(); it != _orderedEntities.rend(); ++it)
    {
        const auto& entity = *it;
        if (!entity->IsVisible())
            continue;

        if (!entity->IsClickable() && !entity->IsMovable())
            continue;

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
    if (_currentSizeX <= 0.0f || _currentSizeY <= 0.0f)
        return {0.0f, 0.0f};

    const float blockX = (position.x() - _currentOffsetX) / _currentSizeX;
    const float blockY = (position.y() - _currentOffsetY) / _currentSizeY;
    return {blockX, blockY};
}
