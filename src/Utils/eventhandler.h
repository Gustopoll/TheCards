#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <functional>

template<typename... Args>
class EventHandler
{
public:
    using Callback = std::function<void(Args...)>;

    EventHandler() : _subscriber(*this) {}

    class Subscriber
    {
    public:
        Subscriber(EventHandler& handler) : parent(handler)
        {
        }

        void Subscribe(Callback cb)
        {
            parent._callbacks.push_back(cb);
        }

    private:
        EventHandler& parent;
    };

    Subscriber& GetSubscriber()
    {
        return _subscriber;
    }

    void Fire(Args... args)
    {
        for (auto& cb : _callbacks)
        {
            cb(args...);
        }
    }

private:
    Subscriber _subscriber;

    std::vector<Callback> _callbacks;
};

#endif // EVENTHANDLER_H
