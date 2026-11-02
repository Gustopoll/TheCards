#ifndef DRAWINGENTITY_H
#define DRAWINGENTITY_H

#include <QColor>
#include <QImage>
#include <algorithm>
#include <memory>

class DrawingEntity
{
public:
    DrawingEntity(
        std::shared_ptr<QImage> image,
        float x,
        float y,
        float sizeX,
        float sizeY);

    ~DrawingEntity() = default;

    //! Gets the image.
    std::shared_ptr<QImage> GetImage() const { return _image; }
    //! Sets the image.
    void SetImage(std::shared_ptr<QImage> image) { _image = std::move(image); }

    //! Gets the position X (block coordinates).
    float GetPosX() const { return _posX; }
    //! Sets the position X (block coordinates).
    void SetPosX(float posX) { _posX = posX; }

    //! Gets the position Y (block coordinates).
    float GetPosY() const { return _posY; }
    //! Sets the position Y (block coordinates).
    void SetPosY(float posY) { _posY = posY; }

    //! Gets the size X (block coordinates).
    float GetSizeX() const { return _sizeX; }
    //! Sets the size X (block coordinates).
    void SetSizeX(float size) { _sizeX = size; }

    //! Gets the size Y (block coordinates).
    float GetSizeY() const { return _sizeY; }
    //! Sets the size Y (block coordinates).
    void SetSizeY(float size) { _sizeY = size; }

    //! Gets the unique ID.
    uint32_t GetId() const { return _id; }

    //! Sets the highlight.
    //! @param color Color of the borders
    void HighlightBorders(const QColor& color);

    //! Resets the highlighted border.
    void ResetHighlightedBorders() { _highlight = false; }

    //! Gets the highlighted color of borders.
    const QColor& GetHighlightColor() const { return _highlightColor; }
    bool IsHighlighted() const { return _highlight; }

    //! Movable property.
    bool IsMovable() const { return _isMovable; }
    void SetMovable(bool movable) { _isMovable = movable; }

    //! Clickable property.
    bool IsClickable() const { return _isClickable; }
    void SetClickable(bool clickable) { _isClickable = clickable; }

    //! Visibility property.
    bool IsVisible() const { return _isVisible; }
    void SetVisible(bool visible) { _isVisible = visible; }

    //! Z-Index (rendering order, higher = on top).
    int GetZIndex() const { return _zIndex; }
    void SetZIndex(int zIndex) { _zIndex = zIndex; }

    //! Gets opacity (0.0f transparent to 1.0f fully opaque).
    float GetOpacity() const { return _opacity; }
    //! Sets opacity (clamped between 0.0f and 1.0f).
    void SetOpacity(float opacity) { _opacity = std::clamp(opacity, 0.0f, 1.0f); }

private:
    //! True if entity has highlighted borders.
    bool _highlight = false;

    //! Color of highlighted borders of entity.
    QColor _highlightColor;

    //! Image of the entity.
    std::shared_ptr<QImage> _image = nullptr;

    //! Position X (block coordinates).
    float _posX = 0.0f;
    //! Position Y (block coordinates).
    float _posY = 0.0f;

    //! Size X of the entity (block coordinates).
    float _sizeX = 1.0f;
    //! Size Y of the entity (block coordinates).
    float _sizeY = 1.0f;

    //! Unique entity ID.
    uint32_t _id = 0;

    //! Whether this entity can be dragged with mouse.
    bool _isMovable = false;
    //! Whether this entity responds to click events.
    bool _isClickable = false;
    //! Whether this entity is rendered and interactive.
    bool _isVisible = true;

    //! Rendering layer index (higher values drawn on top).
    int _zIndex = 0;

    //! Opacity of entity in range [0.0f, 1.0f].
    float _opacity = 1.0f;
};

#endif // DRAWINGENTITY_H
