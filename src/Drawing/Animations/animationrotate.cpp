#include "animationrotate.h"

AnimationRotate::AnimationRotate(std::shared_ptr<DrawingEntity> entity, DrawingWidget *drawingWidget, QObject *parent) :
    QObject(parent),
    _entity(entity),
    _drawingWidget(drawingWidget)
{
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &AnimationRotate::OnUpdateTimer);
}

void AnimationRotate::Start()
{
    if (_timer->isActive())
        return;

    if (_speed == 0)
    {
        Stop();
        return;
    }

    _initialSize = GetSize();
    _initialPosition = GetPosition();
    _state = State::Shrining;
    _timer->start(_speed);
}

void AnimationRotate::Stop()
{
    _timer->stop();
    Finish();
}

void AnimationRotate::SetRotation(AnimationRotate::RotationAxis rotation)
{
   if (_timer->isActive())
       return;

   _rotation = rotation;
}

float AnimationRotate::GetSize()
{
    if (_rotation == RotationAxis::X)
        return _entity->GetSizeX();
    if (_rotation == RotationAxis::Y)
        return _entity->GetSizeY();

    return 0.0f;
}

void AnimationRotate::SetSize(const float size)
{
    if (_rotation == RotationAxis::X)
        _entity->SetSizeX(size);
    if (_rotation == RotationAxis::Y)
        _entity->SetSizeY(size);
}

float AnimationRotate::GetPosition()
{
    if (_rotation == RotationAxis::X)
        return _entity->GetPosX();
    if (_rotation == RotationAxis::Y)
        return _entity->GetPosY();

    return 0.0f;
}

void AnimationRotate::SetPosition(const float position)
{
    if (_rotation == RotationAxis::X)
        _entity->SetPosX(position);
    if (_rotation == RotationAxis::Y)
        _entity->SetPosY(position);
}

void AnimationRotate::OnUpdateTimer()
{
    const float step = 0.1f;

    switch (_state) {
        case State::Idle:
        {
            _state = State::Shrining;
            break;
        }
        case State::Shrining:
        {
            const auto size = GetSize();
            if (size <= 0)
            {
                SetSize(0);
                _state = State::Expanding;
                if (_image)
                    _entity->SetImage(_image);
                break;
            }

            SetSize(size - step);
            SetPosition(GetPosition() + step * 0.5f);
            break;
        }
        case State::Expanding:
        {
            const auto size = GetSize();
            if (size >= _initialSize)
            {
                SetSize(_initialSize);
                SetPosition(_initialPosition);
                _state = State::End;
                break;
            }

            SetSize(size + step);
            SetPosition(GetPosition() - step * 0.5f);
            break;
        }
        case State::End:
        {
            Stop();
            _state = State::Idle;
            break;
        }
    }


    _drawingWidget->update();
}
