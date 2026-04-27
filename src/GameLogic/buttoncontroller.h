#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include "src/Drawing/Widgets/drawingwidget.h"
#include "src/Utils/datapreloader.h"

class ButtonController
{
public:
    ButtonController(
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

    void Show();

private:
    void SubscribeToEvents();

    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // BUTTONCONTROLLER_H
