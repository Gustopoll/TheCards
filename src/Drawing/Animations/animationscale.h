#ifndef ANIMATIONSCALE_H
#define ANIMATIONSCALE_H

#include "src/Drawing/Entities/drawingentity.h"
#include "src/Drawing/Widgets/drawingwidget.h"
#include "IAnimation.h"
#include <QObject>
#include <QTimer>

class AnimationScale : public QObject, public IAnimation
{
    Q_OBJECT
public:
    AnimationScale(std::shared_ptr<DrawingEntity> entity, DrawingWidget* drawingWidget, QObject *parent = nullptr);
    ~AnimationScale() = default;

    void Start() override;
    void Stop() override;

    //! Sets the final scaling factor of the entity.
    void SetTargetScale(float scale) {_targetScale = scale;};
private:
    //! The entity being animated.
    std::shared_ptr<DrawingEntity> _entity;

    //! Widget to draw animation.
    DrawingWidget* _drawingWidget;

    QTimer* _timer;

    //! Final scale of the entity. scale of the entity.
    float _targetScale = 0;

    //! Current size of the entity.
    float _currentSizeX = 0;
    float _currentSizeY = 0;

    //! Target size based on the initial size and final scale.
    float _destinationSizeX = 0;
    float _destinationSizeY = 0;

    //! Sets the final position of the entity based on target scale.
    void SetFinalPosition();

    //! Timer callback that updates the entity's size.
    //! Gradually scales the entity towards _destinationSize,
    //! based on the speed set by the timer, until the target size is reached.
    void OnUpdateTimer();
};

#endif // ANIMATIONSCALE_H
