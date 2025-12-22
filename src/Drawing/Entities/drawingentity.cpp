#include "drawingentity.h"

static uint32_t GlobalID = 0;

DrawingEntity::DrawingEntity(std::shared_ptr<QImage> image, float x, float y)
    : _image(image), _posX(x), _posY(y), _id(GlobalID++) {}

void DrawingEntity::HighlightBorders(const QColor &color)
{
    _highlight = true;
    _highlightColor = color;
}
