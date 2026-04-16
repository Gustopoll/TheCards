#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include "src/Drawing/Entities/drawingentity.h"
#include "src/Utils/eventhandler.h"

#include <QWidget>
#include <QMouseEvent>

#include <map>

struct ClickedData
{
    //! X distance (block coordinations) between top-left point and clicked point.
    float clickedOffsetX = 0;

    //! Y distance (block coordinations) between top-left point and clicked point.
    float clickedOffsetY = 0;

    //! Clicked entity
    std::shared_ptr<DrawingEntity> entity;
};

class DrawingWidget : public QWidget
{
    Q_OBJECT
public:
    using EntityPressedEvent = EventHandler<std::shared_ptr<DrawingEntity>>;
    using EntityReleasedEvent = EventHandler<std::shared_ptr<DrawingEntity>>;

    DrawingWidget(QWidget *parent = nullptr);

    //! Initialize the screen for drawing entities.
    //!
    //! This method sets up the drawing area with a coordinate system
    //! that is independent of the screen resolution. The coordinate system
    //! will map the values from the range [0, maxSizeX] and [0, maxSizeY] to
    //! the actual pixel values, maintaining the aspect ratio.
    //! @param maxSizeX maximum X value.
    //! @param maxSizeY maximum Y value.
    void Initialize(uint32_t maxSizeX, uint32_t maxSizeY);

    //! Creates the entity.
    //!
    //! @param image Image of the entity with default properties and size.
    //! @param x X position of entity in range [0, maxSizeX].
    //! @param y Y position of entity in range [0, maxSizeY].
    //! @param sizeX X size of entity.
    //! @param sizeY Y size of entity.
    //! @return Id of the created entity.
    uint32_t CreateEntity(
        std::shared_ptr<QImage> image,
        float x,
        float y,
        float sizeX,
        float sizeY);

    const std::shared_ptr<DrawingEntity> GetEntity(uint32_t id);

    void SetEntityAsMovable(uint32_t id);
    void SetEntityAsClickable(uint32_t id);

    //! Moves entity to position.
    //!
    //! @param Id of entity to move.
    //! @param x X position of entity in range [0, maxSizeX].
    //! @param y Y position of entity in range [0, maxSizeY].
    void MoveEntityTo(uint32_t id, float x, float y);

    //! Shows gird inside drawing area.
    void ShowGrid(bool enable);

    //! Gets the X and Y position of initialized max block size.
    std::pair<uint32_t, uint32_t> GetBlockCount() { return std::make_pair(_maxSizeX, _maxSizeY); }

    EntityPressedEvent::Subscriber& GetEntityPressedEvent()
    {
        return _entityPressedEvent.GetSubscriber();
    }

    EntityReleasedEvent::Subscriber& GetEntityReleasedEvent()
    {
        return _entityReleasedEvent.GetSubscriber();
    }

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:

    //! Gets the entity based on position.
    //!
    //! It works only for enitites in moving group or in clickable group.
    //! @param x X position.
    //! @param y Y position.
    //! @return Entity.
    std::shared_ptr<DrawingEntity> GetEntityByPosition(const QPoint& position);

    //! True when given position is inside the entity, otherwise false.
    bool IsPositionInsideEntity(const std::shared_ptr<DrawingEntity>& entity, const QPoint& position);

    //! Converts position (in block coordinates) to pixel coordinates.
    QPoint ConvertBlockToPixels(float x, float y);

    //! Converts position (in pixel coordinates) to block coordinates.
    std::pair<float, float> ConvertPixelsToBlock(const QPoint& position);

    bool _isInitialized = false;

    bool _showGrid = false;

    //! Size of drawing area.
    uint32_t _maxSizeX = 0;
    uint32_t _maxSizeY = 0;

    //! Current size of one block of drawing area (in pixels).
    float _currentSizeX = 0;
    float _currentSizeY = 0;

    //! Offset of the drawing area X/Y (in pixels).
    //! Because we want to have drawing area in the middle of the screen.
    float _currentOffsetX = 0;
    float _currentOffsetY = 0;

    //! Holds data for clicked entities.
    std::map<Qt::MouseButton, ClickedData> _clickedEntities;

    //! Map of all movable entities <id, object>..
    std::map<uint32_t, std::shared_ptr<DrawingEntity>> _movableEntities;

    //! Map of all clickable entities <id, object>.
    std::map<uint32_t, std::shared_ptr<DrawingEntity>> _clickableEntities;

    //! Map of all entities <id, object>.
    std::map<uint32_t, std::shared_ptr<DrawingEntity>> _entities;

    EntityPressedEvent _entityPressedEvent;
    EntityReleasedEvent _entityReleasedEvent;
};

#endif // DRAWINGWIDGET_H
