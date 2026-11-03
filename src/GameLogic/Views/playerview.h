#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QImage>

#include <memory>
#include <vector>

class DrawingWidget;
class DataPreloader;

class PlayerView
{
public:
    PlayerView(
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

#endif // PLAYERVIEW_H
