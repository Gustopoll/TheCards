#include "animationscale.h"
#include <QDebug>

AnimationScale::AnimationScale(
    std::shared_ptr<DrawingEntity> entity, DrawingWidget* drawingWidget, QObject *parent) :
    QObject(parent),
    _entity(entity),
    _drawingWidget(drawingWidget)
{
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &AnimationScale::OnUpdateTimer);
}

void AnimationScale::Start()
{
    if (_timer->isActive())
        return;

    _currentSizeX = _entity->GetSizeX();
    _currentSizeY = _entity->GetSizeY();
    _destinationSizeX = _entity->GetSizeX() * _targetScale;
    _destinationSizeY = _entity->GetSizeY() * _targetScale;

    if (_speed == 0)
    {   
        _entity->SetSizeX(_destinationSizeX);
        _entity->SetSizeY(_destinationSizeY);
        SetFinalPosition();
        Stop();
        return;
    }

    _timer->start(_speed);
}

void AnimationScale::Stop()
{
    _timer->stop();
    Finish();
}

void AnimationScale::SetFinalPosition()
{
    _entity->SetPosX(_entity->GetPosX() - (_destinationSizeX - _currentSizeX) / 2.0f);
    _entity->SetPosY(_entity->GetPosY() - (_destinationSizeY - _currentSizeY) / 2.0f);
}

void AnimationScale::OnUpdateTimer()
{
    // If the current size is very close to the destination size, stop the timer and return.
    if (std::fabs(_currentSizeX - _destinationSizeX) < 0.2)
    {
        _entity->SetSizeX(_destinationSizeX);
        _entity->SetSizeY(_destinationSizeY);
        SetFinalPosition();

        _drawingWidget->update();
        Stop();
        return;
    }

    // Smoothly adjust size towards destination.
    float stepX = (_destinationSizeX - _currentSizeX) * 0.1f; // Adjust 10% of the difference each time
    float stepY = (_destinationSizeY - _currentSizeY) * 0.1f; // Adjust 10% of the difference each time
    _currentSizeX += stepX;
    _currentSizeY += stepY;
    _entity->SetSizeX(_currentSizeX);
    _entity->SetSizeY(_currentSizeY);

    // Adjust position to be centered when size is changed.
    _entity->SetPosX(_entity->GetPosX() - stepX/2);
    _entity->SetPosY(_entity->GetPosY() - stepY/2);

    // Refresh screen
    _drawingWidget->update();
}
