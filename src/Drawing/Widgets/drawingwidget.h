#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include "src/Drawing/Entities/drawingentity.h"
#include "src/Utils/eventhandler.h"

#include <QWidget>
#include <QMouseEvent>

#include <map>
#include <unordered_map>
#include <vector>

struct ClickedData
{
    //! X distance (block coordinations) between top-left point and clicked point.
    float clickedOffsetX = 0;

    //! Y distance (block coordinations) between top-left point and clicked point.
    float clickedOffsetY = 0;

    //! Clicked entity
    std::shared_ptr<DrawingEntity> entity;
};

struct DrawingTextEntity
{
    //! Unique ID of text entity.
    uint32_t id = 0;
    //! Text to draw.
    QString text;
    //! X position of text in range [0, maxSizeX]
    float x = 0.0f;
    //! Y position of text in range [0, maxSizeY].
    float y = 0.0f;
    //! Size of text.
    float pixelSize = 1.0f;
    //! Color of text.
    QColor color;
};

class DrawingWidget : public QWidget
{
    Q_OBJECT
public:
    using EntityPressedEvent = EventHandler<std::shared_ptr<DrawingEntity>>;
    using EntityReleasedEvent = EventHandler<std::shared_ptr<DrawingEntity>>;

    DrawingWidget(QWidget *parent = nullptr);

    //! Initialize the screen for drawing entities.
    //! This method sets up the drawing area with a coordinate system
    //! that is independent of the screen resolution. The coordinate system
    //! will map the values from the range [0, maxSizeX] and [0, maxSizeY] to
    //! the actual pixel values, maintaining the aspect ratio.
    //! @param maxSizeX maximum X value.
    //! @param maxSizeY maximum Y value.
    void Initialize(uint32_t maxSizeX, uint32_t maxSizeY);

    //! Creates the entity.
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

    //! Removes an entity by ID.
    bool RemoveEntity(uint32_t id);

    //! Clears all entities.
    void ClearEntities();

    //! Shows the text.
    //! @param text Text to show.
    //! @param x X position of text in range [0, maxSizeX].
    //! @param y Y position of text in range [0, maxSizeY].
    //! @param pixelSize Pixel size of text.
    //! @param color Color of text.
    //! @return Id of the created text entity.
    uint32_t ShowText(
        const QString& text,
        float x,
        float y,
        float pixelSize,
        QColor color);

    //! Updates existing text and color by ID.
    bool UpdateText(uint32_t id, const QString& text, const QColor& color);

    //! Updates existing text content by ID.
    bool UpdateText(uint32_t id, const QString& text);

    //! Removes a text entity by ID.
    bool RemoveText(uint32_t id);

    //! Clears all text entities.
    void ClearText();

    std::shared_ptr<DrawingEntity> GetEntity(uint32_t id) const;

    void SetEntityAsMovable(uint32_t id, bool movable = true);
    void SetEntityAsClickable(uint32_t id, bool clickable = true);
    void SetEntityVisible(uint32_t id, bool visible = true);

    //! Sets the opacity of an entity (0.0f transparent to 1.0f opaque).
    void SetEntityOpacity(uint32_t id, float opacity);

    //! Gets the opacity of an entity.
    float GetEntityOpacity(uint32_t id) const;

    //! Z-Index and Layering methods.
    void SetEntityZIndex(uint32_t id, int zIndex);
    int GetEntityZIndex(uint32_t id) const;
    void BringEntityToFront(uint32_t id);
    void SendEntityToBack(uint32_t id);

    //! Moves entity to position.
    //! @param id Id of entity to move.
    //! @param x X position of entity in range [0, maxSizeX].
    //! @param y Y position of entity in range [0, maxSizeY].
    void MoveEntityTo(uint32_t id, float x, float y);

    //! Shows grid inside drawing area.
    void ShowGrid(bool enable);

    //! Gets the X and Y position of initialized max block size.
    std::pair<uint32_t, uint32_t> GetBlockCount() const { return std::make_pair(_maxSizeX, _maxSizeY); }

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
    //! Ensures entities in _orderedEntities are sorted by Z-index.
    void EnsureEntitiesSorted();

    //! Gets the entity based on position.
    //! Checks visible clickable/movable entities from top to bottom (highest Z to lowest Z).
    //! @param position Pixel position.
    //! @return Entity or nullptr.
    std::shared_ptr<DrawingEntity> GetEntityByPosition(const QPoint& position);

    //! True when given position is inside the entity, otherwise false.
    bool IsPositionInsideEntity(const std::shared_ptr<DrawingEntity>& entity, const QPoint& position);

    //! Converts position (in block coordinates) to pixel coordinates.
    QPoint ConvertBlockToPixels(float x, float y);

    //! Converts position (in pixel coordinates) to block coordinates.
    std::pair<float, float> ConvertPixelsToBlock(const QPoint& position);

    bool _isInitialized = false;
    bool _showGrid = false;
    bool _isOrderDirty = false;

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

    //! Fast lookup by ID.
    std::unordered_map<uint32_t, std::shared_ptr<DrawingEntity>> _entities;

    //! Render and hit-test order (sorted by Z-index).
    std::vector<std::shared_ptr<DrawingEntity>> _orderedEntities;

    uint32_t _nextTextId = 1;
    std::vector<DrawingTextEntity> _textEntities;

    EntityPressedEvent _entityPressedEvent;
    EntityReleasedEvent _entityReleasedEvent;
};

#endif // DRAWINGWIDGET_H
