#ifndef DRAWINGGROUP_H
#define DRAWINGGROUP_H

#include "src/Drawing/Entities/drawingentity.h"
#include "src/Utils/eventhandler.h"

enum class DrawingEvents
{
    EntityPressed,
    EntityReleased
};

class DrawingGroup : public std::enable_shared_from_this<DrawingGroup>
{
public:
    using EntityPressedEvent = EventHandler<std::shared_ptr<DrawingEntity>>;
    using EntityReleasedEvent = EventHandler<std::shared_ptr<DrawingEntity>>;

    DrawingGroup(const std::string& groupName);

    //! Gets the name of the group.
    const std::string& GetGroupName() const noexcept { return _groupName;}

    //! Gets all the entities in group.
    const std::vector<std::shared_ptr<DrawingEntity>>& GetEntities() const noexcept { return _entities;}

    //! Adds the entity to the group.
    void AddEntity(std::shared_ptr<DrawingEntity> entity);

    //! Removes an entity from the group.
    void RemoveEntity(const std::shared_ptr<DrawingEntity>& entity);

    //! Sets whether the group is movable.
    //! When enabled, entities in the group can be moved via drag-and-drop actions.
    //! @param enable True to enable movability, false to disable.
    void SetMovable(bool enable) { _movable = enable; }

    //! Sets whether the group is clickable.
    void SetClickable(bool enable) { _clickable = enable; }

    //! Checks whether the group is movable.
    bool IsMovable() const noexcept { return _movable;}

    //! Checks whether the group is clickable.
    bool IsClickable() const noexcept { return _clickable;}

    EntityPressedEvent::Subscriber& GetEntityPressedEvent()
    {
        return _entityPressedEvent.GetSubscriber();
    }

    EntityReleasedEvent::Subscriber& GetEntityReleasedEvent()
    {
        return _entityReleasedEvent.GetSubscriber();
    }

private:
    std::string _groupName;
    bool _movable = false;
    bool _clickable = false;

    //! Entities in this group.
    std::vector<std::shared_ptr<DrawingEntity>> _entities;

    EntityPressedEvent _entityPressedEvent;
    EntityReleasedEvent _entityReleasedEvent;

};

#endif // DRAWINGGROUP_H
