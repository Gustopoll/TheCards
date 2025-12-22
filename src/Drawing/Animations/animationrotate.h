#ifndef ANIMATIONROTATE_H
#define ANIMATIONROTATE_H

#include "src/Drawing/Entities/drawingentity.h"
#include "src/Drawing/Widgets/drawingwidget.h"
#include "IAnimation.h"

#include <QObject>
#include <QTimer>

class AnimationRotate : public QObject, public IAnimation
{
    Q_OBJECT
public:
    enum RotationAxis
    {
        X,
        Y
    };

    enum State
    {
        Idle,
        Shrining,
        Expanding,
        End
    };

    AnimationRotate(std::shared_ptr<DrawingEntity> entity, DrawingWidget* drawingWidget, QObject *parent = nullptr);
    ~AnimationRotate() = default;

    void Start() override;
    void Stop() override;

    //! Sets the orientation of rotation.
    void SetRotation(RotationAxis rotation);

    //! Sets the new iamge that will be changed during animation.
    void SetNewImage(std::shared_ptr<QImage> image) {_image = image;}
private:
    //! The entity being animated.
    std::shared_ptr<DrawingEntity> _entity;

    //! Widget to draw animation.
    DrawingWidget* _drawingWidget;

    QTimer* _timer;

    RotationAxis _rotation = RotationAxis::X;

    //! Current state of the state machine.
    State _state = State::Idle;

    //! Initial values sets when animation starts.
    float _initialSize = 0;
    float _initialPosition = 0;

    std::shared_ptr<QImage> _image;

    void SetSize(float size);
    float GetSize();
    void SetPosition(float position);
    float GetPosition();

    //! Timer callback that updates the entity's size.
    void OnUpdateTimer();
};

#endif // ANIMATIONROTATE_H
