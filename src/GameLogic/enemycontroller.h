#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "src/Drawing/Widgets/drawingwidget.h"
#include "src/Utils/datapreloader.h"

class EnemyController
{
public:
    struct Enemy
    {
        QString name;
        uint32_t countCards;
    };

    struct Slot
    {
        float x;
        float y;
        bool reverseDirection;
    };

    EnemyController(
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

    void Show(const std::vector<Enemy>& enemies);
private:
    void ShowEnemy(
        const Slot& slot,
        const Enemy& enemy,
        const std::shared_ptr<QImage>& backCardImage);

    void SubscribeToEvents();

    const std::array<Slot, 4> _slots =
    {{
        {1, 3, false},
        {1, 1, false},
        {15, 1, true},
        {15, 3, true}
    }};

    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // ENEMYCONTROLLER_H
