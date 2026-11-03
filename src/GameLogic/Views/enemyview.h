#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include <QImage>
#include <QString>

#include <array>
#include <memory>
#include <vector>

class DrawingWidget;
class DataPreloader;

class EnemyView
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

    EnemyView(
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

    void Show(const std::vector<Enemy>& enemies);

private:
    void ShowEnemy(
        const Slot& slot,
        const Enemy& enemy,
        const std::shared_ptr<QImage>& backCardImage);

    const std::array<Slot, 4> _slots =
    {{
        {1, 3.1, false},
        {15, 3.1, true},
        {1, 1, false},
        {15, 1, true}
    }};

    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // ENEMYVIEW_H
