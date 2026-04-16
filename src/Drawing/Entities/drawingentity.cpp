#include "drawingentity.h"

static uint32_t GlobalID = 0;

DrawingEntity::DrawingEntity(
    const std::shared_ptr<QImage> image,
    const float x,
    const float y,
    const float sizeX,
    const float sizeY)
    : _image(image)
    , _posX(x)
    , _posY(y)
    , _sizeX(sizeX)
    , _sizeY(sizeY)
    , _id(GlobalID++)
{}

void DrawingEntity::HighlightBorders(const QColor &color)
{
    _highlight = true;
    _highlightColor = color;
}
