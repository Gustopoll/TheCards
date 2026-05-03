#include "animationmanager.h"

#include "src/Drawing/Animations/animationscale.h"
#include "src/Drawing/Animations/animationrotate.h"

AnimationManager::AnimationManager(DrawingWidget* drawingWidget) :
    _drawingWidget(drawingWidget)
{
}

AnimationManager::~AnimationManager()
{
    for (const auto& animation : _activeAnimations)
        animation->Stop();

    _activeAnimations.clear();
}

void AnimationManager::Start(
    std::shared_ptr<DrawingEntity> entity,
    const AnimationType animationIndex)
{
    if (const auto animationOpt = GetAnimation(entity, animationIndex))
    {
        const auto animation = *animationOpt;

        _activeAnimations.emplace_back(animation);
        animation->Start();

        animation->SetFinalFunction(
            [this, entity](IAnimation* item)
            {
                RemoveActiveAnimation(item);
                _onAnimationFinishEvent.Fire(entity);
            });
    }
}

std::optional<std::shared_ptr<IAnimation>> AnimationManager::GetAnimation(
    std::shared_ptr<DrawingEntity> drawingEntity,
    AnimationType animationIndex)
{
    if (!drawingEntity)
        return std::nullopt;

    switch (animationIndex)
    {
        case AnimationType::Scale:
        {
            auto animation = std::make_shared<AnimationScale>(drawingEntity, _drawingWidget);
            animation->SetSpeed(50);
            animation->SetTargetScale(2);
            return animation;
        }
        case AnimationType::Rotate:
        {
        auto animation = std::make_shared<AnimationRotate>(drawingEntity, _drawingWidget);
        animation->SetSpeed(50);
        animation->SetNewImage(std::make_shared<QImage>("Data/face2.png"));
        return animation;
        }
    }

    return std::nullopt;
}

void AnimationManager::RemoveActiveAnimation(IAnimation *animation)
{
    _activeAnimations.erase(
        std::remove_if(
            _activeAnimations.begin(),
            _activeAnimations.end(),
            [animation](const std::shared_ptr<IAnimation>& item)
            {
                return item.get() == animation;
            }));
}
