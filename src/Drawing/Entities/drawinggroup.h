#ifndef DRAWINGGROUP_H
#define DRAWINGGROUP_H

#include "src/Drawing/Entities/drawingentity.h"

enum class DrawingEvents
{
    EntityPressed,
    EntityReleased
};

using OnEntityEvent = std::function<void(std::shared_ptr<DrawingEntity>)>;

class DrawingGroup : public std::enable_shared_from_this<DrawingGroup>
{
public:
    DrawingGroup(const std::string& groupName);

    //! Gets the name of the group.
    const std::string& GetGroupName() const noexcept { return _groupName;}

    //! Gets all the entities in group.
    const std::vector<std::shared_ptr<DrawingEntity>>& GetEntities() const noexcept { return _entities;}

    //! Adds the entity to the group.
    void AddEntity(std::shared_ptr<DrawingEntity> entity);

    //! Removes an entity from the group.
    void RemoveEntity(const std::shared_ptr<DrawingEntity>& entity);

    //! Subscribes a callback to a specific event.
    void SubscribeOnEvent(DrawingEvents event, const OnEntityEvent& callback);

    //! Triggers all callbacks associated with a specific event.
    //! @param event The type of event to trigger.
    //! @param entity The entity associated with the event.
    void TriggerEvent(DrawingEvents event, const std::shared_ptr<DrawingEntity>& entity);

    //! Sets whether the group is movable.
    //! When enabled, entities in the group can be moved via drag-and-drop actions.
    //! @param enable True to enable movability, false to disable.
    void SetMovable(bool enable) { _movable = enable;}

    //! Checks whether the group is movable.
    bool IsMovable() const noexcept { return _movable;}

    //! Checks whether the group is clickable.
    bool IsClickable() const noexcept { return !_entityPressed.empty() || !_entityReleased.empty();}
private:
    std::string _groupName;
    bool _movable = false;

    //! Entities in this group.
    std::vector<std::shared_ptr<DrawingEntity>> _entities;

    //! Vectors of callbacks.
    std::vector<OnEntityEvent> _entityPressed;
    std::vector<OnEntityEvent> _entityReleased;
};

#endif // DRAWINGGROUP_H
