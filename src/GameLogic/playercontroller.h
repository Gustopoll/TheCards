#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "src/Drawing/Widgets/drawingwidget.h"
#include "src/Utils/datapreloader.h"

#include <unordered_map>

class PlayerController
{
public:
    using OnTurnEndEvent = EventHandler<
        //! Name of the action that player performed.
        const std::string&>;

    PlayerController(
        DrawingWidget* drawingWidget,
        DataPreloader& dataPreloader);

    void ShowCards();

    OnTurnEndEvent::Subscriber& GetOnTurnEndEvent()
    {
        return _onTurnEndEvent.GetSubscriber();
    }

    void OnCardPressed(std::shared_ptr<DrawingEntity> entity, Qt::MouseButton button);
    void OnCardReleased(std::shared_ptr<DrawingEntity> entity, Qt::MouseButton button);
private:

    void ShowCards(
        const std::vector<std::shared_ptr<QImage>>& cards,
        float startPosX,
        float startPosY,
        float cardWidth,
        float cardHeight,
        float step);

    //! Posistions of the cards at the time of pressing them.
    std::unordered_map<uint32_t, QPointF> _cardPositions;

    OnTurnEndEvent _onTurnEndEvent;

    DrawingWidget* _drawingWidget;
    DataPreloader& _dataPreloader;
};

#endif // PLAYERCONTROLLER_H
