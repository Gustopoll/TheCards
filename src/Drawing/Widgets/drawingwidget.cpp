#include "drawingwidget.h"
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include "src/Drawing/Animations/animationmanager.h"

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent)
{
    Initialize(16, 9);
}

void DrawingWidget::Initialize(uint32_t maxSizeX, uint32_t maxSizeY)
{
    _maxSizeX = maxSizeX;
    _maxSizeY = maxSizeY;
    _animationManager = std::make_shared<AnimationManager>(this);
    _isInitialized = true;
}

std::shared_ptr<DrawingEntity> DrawingWidget::CreateEntity(std::shared_ptr<QImage> image, float x, float y)
{
   const auto entity = std::make_shared<DrawingEntity>(image, x, y);

   const auto id = entity->GetId();
   _entities[id] = entity;

   return entity;
}

const std::shared_ptr<DrawingEntity> DrawingWidget::GetEntity(uint32_t id)
{
    auto e = _entities.find(id);
    if (e == _entities.end())
        return nullptr;

    return e->second;
}

void DrawingWidget::MoveEntityTo(uint32_t id, float x, float y)
{
    const auto entity = GetEntity(id);
    if (!entity)
        return;

    entity->SetPosX(x);
    entity->SetPosY(y);
    update();
}

std::shared_ptr<DrawingGroup> DrawingWidget::AddEntityToGroup(uint32_t id, const std::string& groupName)
{
    const auto entity = GetEntity(id);
    if (!entity)
    {
        qDebug() << "[AddEntityToGroup] Error: entity with id" << id << "does not exist";
        return nullptr;
    }

    const auto [groupIt, inserted] = _groups.try_emplace(
        groupName,
        std::make_shared<DrawingGroup>(groupName));

    const auto& group = groupIt->second;
    group->AddEntity(entity);
    return group;
}

void DrawingWidget::RemoveEntityFromGroup(int32_t id, const std::string &groupName)
{
    const auto entity = GetEntity(id);
    if (!entity)
    {
        qDebug() << "[RemoveEntityFromGroup] Error: entity with id" << id << "does not exist";
        return;
    }

    auto group = _groups.find(groupName);
    if (group == _groups.end())
    {
        qDebug() << "[RemoveEntityFromGroup] Error: group with name" << groupName << "does not exist";
        return;
    }

    group->second->RemoveEntity(entity);
}

void DrawingWidget::ShowGrid(bool enable)
{
    _showGrid = enable;
    update();
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    event->accept();

    // Do not render anything until DrawingWidget is initialized.
    if (!_isInitialized)
        return;

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
        const auto [x, y] = ConvertBlockToPixels(item->GetPosX(), item->GetPosY());
        const float sizeX = _currentSizeX * item->GetSizeX();
        const float sizeY = _currentSizeY * item->GetSizeY();
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
    event->accept();

    // Size of one block (in pixels)
    const float x = width()/float(_maxSizeX);
    const float y = height()/float(_maxSizeY);

    const auto oneBlock = std::min(x, y);
    _currentSizeX = oneBlock;
    _currentSizeY = oneBlock;

    _currentOffsetX = (width() - oneBlock * _maxSizeX) * 0.5f;
    _currentOffsetY = (height() - oneBlock * _maxSizeY) * 0.5f;
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    const auto clickedEntity = GetEntityByPosition(event->pos().x(), event->pos().y());

    if (clickedEntity)
    {
        for (const auto& group : clickedEntity->GetGroups())
        {
            //group->TriggerEvent(DrawingEvents::EntityPressed, clickedEntity);
        }

        const auto [clickedBlockX, clickedBlockY] = ConvertPixelsToBlock(event->pos().x(), event->pos().y());

        _clickedEntities.emplace(
            event->button(),
            ClickedData{
                clickedBlockX - clickedEntity->GetPosX(),
                clickedBlockY - clickedEntity->GetPosY(),
                clickedEntity
            });
    }

}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    const auto item = _clickedEntities.find(event->button());
    if (item == _clickedEntities.end())
        return;

    const auto& clickedData = item->second;
    if (clickedData.entity)
    {
        for (const auto& group : clickedData.entity->GetGroups())
        {
            //group->TriggerEvent(DrawingEvents::EntityReleased, clickedData.entity);
        }
    }

    _clickedEntities.erase(event->button());
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Center position of click
    const auto item = _clickedEntities.find(Qt::MouseButton::LeftButton);
    if (item == _clickedEntities.end())
        return;

    auto& clickedData = item->second;
    for (const auto& group : clickedData.entity->GetGroups())
    {
        if (!group->IsMovable())
            continue;

        const auto [posX, posY] = ConvertPixelsToBlock(event->pos().x(), event->pos().y());
        clickedData.entity->SetPosX(posX - clickedData.clickedOffsetX);
        clickedData.entity->SetPosY(posY - clickedData.clickedOffsetY);
        update();
    }
}

std::shared_ptr<DrawingEntity> DrawingWidget::GetEntityByPosition(uint32_t x, uint32_t y)
{
    for (const auto& [groupName, group] : _groups)
    {
        // Only for entities in movable or clickable groups.
        if (!group->IsMovable() && !group->IsClickable())
            continue;

        for (const auto& entity : group->GetEntities())
        {
            if (IsPositionInsideEntity(entity, x, y))
                return entity;
        }
    }

    return nullptr;
}

bool DrawingWidget::IsPositionInsideEntity(const std::shared_ptr<DrawingEntity>& entity, uint32_t x, uint32_t y)
{
    const auto [entityX, entityY] = ConvertBlockToPixels(entity->GetPosX(), entity->GetPosY());
    const float entitySizeX = entityX + _currentSizeX * entity->GetSizeX();
    const float entitySizeY = entityY + _currentSizeY * entity->GetSizeY();

    if (entityX > x || entitySizeX < x)
        return false;

    if (entityY > y || entitySizeY < y)
        return false;

    return true;
}

std::pair<uint32_t, uint32_t> DrawingWidget::ConvertBlockToPixels(float x, float y)
{
    const uint32_t pixelsX = x * _currentSizeX + _currentOffsetX;
    const uint32_t pixelsY = y * _currentSizeY + _currentOffsetY;
    return {pixelsX, pixelsY};
}

std::pair<float, float> DrawingWidget::ConvertPixelsToBlock(uint32_t x, uint32_t y)
{
    const float blockX = (x - _currentOffsetX) / _currentSizeX;
    const float blockY = (y - _currentOffsetY) / _currentSizeY;
    return {blockX, blockY};
}
