#ifndef DRAWINGENTITY_H
#define DRAWINGENTITY_H

#include <QImage>

class DrawingGroup;

class DrawingEntity
{
public:
    DrawingEntity(std::shared_ptr<QImage> image, float x, float y);
    ~DrawingEntity() = default;

    //! Gets the image.
    std::shared_ptr<QImage> GetImage() const { return _image;}

    //! Sets the image.
    void SetImage(std::shared_ptr<QImage> image) {_image = image;}

    //! Gets the position X  (block coordinates).
    float GetPosX() const { return _posX;}

    //! Sets the position X  (block coordinates).
    void SetPosX(float posX) { _posX = posX;}

    //! Gets the position Y  (block coordinates).
    float GetPosY() const { return _posY;}

    //! Sets the position Y (block coordinates).
    void SetPosY(float posY) { _posY = posY;}

    //! Gets the size X (block coordinates).
    float GetSizeX() const { return _sizeX;}

    //! Sets the size (block coordinates).
    void SetSizeX(float size) { _sizeX = size;}

    //! Gets the size X (block coordinates).
    float GetSizeY() const { return _sizeY;}

    //! Sets Y the size (block coordinates).
    void SetSizeY(float size) { _sizeY = size;}

    //! Gets the unique ID.
    uint32_t GetId() const { return _id;}

    //! Sets the highlight.
    //!
    //! @param color Color of the borders
    void HighlightBorders(const QColor& color);

    //! Resets the highlighted border.
    void ResetHighlightedBorders() {_highlight = false;}

    //! Gets the highlighted color of borders.
    const QColor& GetHighlightColor() { return _highlightColor;}
    bool IsHighlighted() { return _highlight;}

    //! Gets all groups where entity belongs to.
    const std::vector<std::shared_ptr<DrawingGroup>>& GetGroups() { return _groups;}
private:
    //! True if entity has highlighted borders.
    bool _highlight = false;

    //! Color of lighlighted borders of entity.
    QColor _highlightColor;

    //! Image of the entity.
    std::shared_ptr<QImage> _image = nullptr;

    //! Position X (block coordinates).
    float _posX = 0.0f;

    //! Position Y (block coordinates).
    float _posY = 0.0f;

    //! Size X of the entity (block coordinates).
    float _sizeX = 1;

    //! Size Y of the entity (block coordinates).
    float _sizeY = 1;

    //! Unique entity ID.
    uint32_t _id = 0;

    //! All groups where entity belongs to.
    std::vector<std::shared_ptr<DrawingGroup>> _groups;

    friend DrawingGroup;
};

#endif // DRAWINGENTITY_H
