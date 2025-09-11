#pragma once

#include <functional>

namespace rpe {

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyRepeat,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    class Event {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
    protected:
        bool handled = false;
    };

    class EventDispatcher {
        template<typename T> using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) : event(event) {}

        template<typename T> bool Dispatch(EventFn<T> func) {
            if (event.GetEventType() == T::GetStaticType()) {
                event.handled = func(static_cast<T>(&event));
                return true;
            }
            return false;
        }
    private:
        Event& event;
    };
}