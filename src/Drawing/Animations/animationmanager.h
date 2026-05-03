#ifndef ANIMATION_H
#define ANIMATION_H

#include "src/Drawing/Animations/IAnimation.h"
#include "src/Utils/eventhandler.h"

#include <QDebug>
#include <QObject>

class AnimationScale;
class AnimationRotate;
class DrawingWidget;
class DrawingEntity;

class AnimationManager
{
public:
    using OnAnimationFinishedEvent = EventHandler<
        //! Entity that just finished animation process.
        std::shared_ptr<DrawingEntity>>;

    AnimationManager(DrawingWidget* drawingWidget);
    ~AnimationManager();

    //! Perform the animation process.
    void Start(
        std::shared_ptr<DrawingEntity> entity,
        AnimationType animationIndex);

    OnAnimationFinishedEvent::Subscriber& GetOnAnimationFinishEvent()
    {
        return _onAnimationFinishEvent.GetSubscriber();
    };

private:
    //! Gets the animation based on index for given entity.
    //!
    //! @param drawingEntity Entity to animate.
    //! @param animationIndex Index of animation.
    //! @return Animation or nullptr when given animation does not exist.
    std::optional<std::shared_ptr<IAnimation>> GetAnimation(
        std::shared_ptr<DrawingEntity> drawingEntity,
        AnimationType animationIndex);

    //! Calls when animation ends.
    void RemoveActiveAnimation(IAnimation* animation);

    OnAnimationFinishedEvent _onAnimationFinishEvent;

    DrawingWidget* _drawingWidget;

    //! Contains currently active animations.
    std::vector<std::shared_ptr<IAnimation>> _activeAnimations;
};

#endif // ANIMATION_H
