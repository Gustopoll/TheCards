#ifndef ANIMATION_H
#define ANIMATION_H

#include "src/Drawing/Animations/animationscale.h"
#include "src/Drawing/Animations/animationrotate.h"
#include "src/Drawing/Constants.h"
#include "src/Drawing/Entities/drawingentity.h"

#include <functional>
#include <QDebug>
#include <QObject>

class DrawingWidget;

using OnAnimationFinished = std::function<void(std::shared_ptr<DrawingEntity>)>;

class AnimationManager
{
public:    
    AnimationManager(DrawingWidget* drawingWidget);
    ~AnimationManager();

    //! Perform the animation process.
    void Start(
        std::shared_ptr<DrawingEntity> entity,
        AnimationType animationIndex,
        OnAnimationFinished callback = nullptr);

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
    void OnAnimationEnds(IAnimation* animation);

    DrawingWidget* _drawingWidget;

    //! Contains currently active animations.
    std::vector<std::shared_ptr<IAnimation>> _activeAnimations;
};

#endif // ANIMATION_H
