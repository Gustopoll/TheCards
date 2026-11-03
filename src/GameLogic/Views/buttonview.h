#ifndef BUTTONVIEW_H
#define BUTTONVIEW_H

#include <memory>

class DrawingWidget;
class DrawingEntity;
class DataPreloader;

class ButtonView
{
public:
    ButtonView(
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

    void Show();

    void OnEntityPressed(std::shared_ptr<DrawingEntity> entity);
    void OnEntityReleased(std::shared_ptr<DrawingEntity> entity);

private:
    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // BUTTONVIEW_H
