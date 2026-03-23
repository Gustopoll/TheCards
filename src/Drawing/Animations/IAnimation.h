#ifndef IANIMATION_H
#define IANIMATION_H

#include <cstdint>
#include <functional>

enum class AnimationType
{
    Scale,
    Rotate
};

class IAnimation
{
public:
    virtual ~IAnimation() = default;

    virtual void Start() = 0;
    virtual void Stop() = 0;

    //! Sets the speed of the animation (ms).
    virtual void SetSpeed(uint32_t speed)
    {
        _speed = speed;
    }

    //! Set callback called when animation ends.
    virtual void SetFinalFunction(std::function<void(IAnimation*)> callback)
    {
        _finalCallback = callback;
    }

protected:
    std::function<void(IAnimation*)> _finalCallback;

    //! Animation speed (ms), frequency of timer updates.
    uint32_t _speed = 0;

    void Finish()
    {
        if (_finalCallback)
        {
            _finalCallback(this);

            // Clear callback to ensure that callback is called only once
            //_finalCallback = nullptr;
        }
    }
};

#endif // IANIMATION_H
