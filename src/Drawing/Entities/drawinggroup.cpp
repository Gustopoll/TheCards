#include "drawinggroup.h"

#include <QDebug>

DrawingGroup::DrawingGroup(const std::string& groupName)
    : _groupName(groupName)
{
}

void DrawingGroup::AddEntity(std::shared_ptr<DrawingEntity> entity)
{
    // Check if entity is not in group
    bool find = false;
    for (const auto& item : _entities)
    {
        if (item == entity)
        {
            find = true;
            qDebug() << "[AddEntity] Error: entity with id" << entity->GetId() << "is already in group" << _groupName;
        }
    }

    if (find)
        return;

    entity->_groups.emplace_back(shared_from_this());
    _entities.emplace_back(entity);
    qDebug() << "[AddEntity] Success: entity with id" << entity->GetId() << "was added to group" << _groupName;
}

void DrawingGroup::RemoveEntity(const std::shared_ptr<DrawingEntity> &entity)
{
    std::remove_if(
        _entities.begin(),
        _entities.end(),
        [&entity](auto e){ return e == entity;});

    std::remove_if(
        entity->_groups.begin(),
        entity->_groups.end(),
        [this](auto g){return g.get() == this;});
}

void DrawingGroup::SubscribeOnEvent(DrawingEvents event, const OnEntityEvent &callback)
{
    switch (event) {
        case DrawingEvents::EntityPressed:
            _entityPressed.emplace_back(callback);
        break;
        case DrawingEvents::EntityReleased:
            _entityReleased.emplace_back(callback);
        break;
    }
}

void DrawingGroup::TriggerEvent(DrawingEvents event, const std::shared_ptr<DrawingEntity> &entity)
{
    switch (event) {
        case DrawingEvents::EntityPressed:
            for (const auto& fire : _entityPressed)
                fire(entity);
        break;
        case DrawingEvents::EntityReleased:
            for (const auto& fire : _entityReleased)
                fire(entity);
        break;
    }
}
