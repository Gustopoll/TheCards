#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include <memory>

class DrawingWidget;
class DrawingEntity;
class DataPreloader;

class ButtonController
{
public:
    ButtonController(
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

    void Show();

    void OnEntityPressed(std::shared_ptr<DrawingEntity> entity);
    void OnEntityReleased(std::shared_ptr<DrawingEntity> entity);
private:

    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // BUTTONCONTROLLER_H
