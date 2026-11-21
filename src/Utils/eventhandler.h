#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <functional>
#include <map>

template<typename... Args>
class EventHandler
{
public:
    using Callback = std::function<void(Args...)>;
    using SubscriptionId = size_t;

    EventHandler() : _subscriber(*this) {}

    class Subscriber
    {
    public:
        Subscriber(EventHandler& handler) : parent(handler)
        {
        }

        //! Subscribes a callback and returns its subscription ID.
        //! Store the ID if you need to unsubscribe later.
        SubscriptionId Subscribe(Callback cb)
        {
            return parent.Subscribe(std::move(cb));
        }

        //! Removes the callback with the given subscription ID.
        void Unsubscribe(SubscriptionId id)
        {
            parent.Unsubscribe(id);
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
        for (auto& [id, cb] : _callbacks)
        {
            cb(args...);
        }
    }

private:
    SubscriptionId Subscribe(Callback cb)
    {
        const SubscriptionId id = _nextId++;
        _callbacks[id] = std::move(cb);
        return id;
    }

    void Unsubscribe(SubscriptionId id)
    {
        _callbacks.erase(id);
    }

    Subscriber _subscriber;

    std::map<SubscriptionId, Callback> _callbacks;
    SubscriptionId _nextId = 0;
};

#endif // EVENTHANDLER_H
