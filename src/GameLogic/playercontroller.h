#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QImage>

#include <vector>

class DrawingWidget;
class DataPreloader;

class PlayerController
{
public:
    PlayerController(
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

    void ShowCards();

private:

    void ShowCards(
        const std::vector<std::shared_ptr<QImage>>& cards,
        float startPosX,
        float startPosY,
        float cardWidth,
        float cardHeight,
        float step);

    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // PLAYERCONTROLLER_H
