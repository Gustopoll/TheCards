#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "src/Drawing/Widgets/drawingwidget.h"
#include "src/Utils/datapreloader.h"

class PlayerController
{
public:
    PlayerController(
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

    void ShowCards();

private:
    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // PLAYERCONTROLLER_H
