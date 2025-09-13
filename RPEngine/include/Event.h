#pragma once

#include "rpepch.h"

namespace rpe {

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    class Event {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual std::string GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }

    protected:
        bool handled = false;
    };

    class EventDispatcher {
        template<typename T> using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) : event(event) {}

        template<typename T> bool Dispatch(EventFn<T> func) {
            if (event.GetEventType() == T::GetStaticType()) {
                event.handled = func(*static_cast<T *>(&event));
                return true;
            }
            return false;
        }
    private:
        Event& event;
    };


    // WINDOW EVENTS
    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {}

        EventType GetEventType() const override { return EventType::WindowClose; }
        static EventType GetStaticType() { return EventType::WindowClose; }
        std::string GetName() const override { return "WindowCloseEvent"; }
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(const int width, const int height) : width(width), height(height) {}

        EventType GetEventType() const override { return EventType::WindowResize; }
        static EventType GetStaticType() { return EventType::WindowResize; }
        std::string GetName() const override { return "WindowResizeEvent"; }
        std::string ToString() const override { return "WindowResizeEvent: (" + std::to_string(width) + ", " + std::to_string(height) + ")"; }

        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
    private:
        int width, height;
    };

    //KEY EVENTS

    //abstract
    class KeyEvent : public Event {
    public:
        int GetKeyCode() const { return KeyCode; }

    protected:
        KeyEvent(const int keyCode) : KeyCode(keyCode) {}

        int KeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(const int keycode, const int repeatCount) : KeyEvent(keycode), repeatCount(repeatCount) {}

        int GetRepeatCount() const { return repeatCount; }

        std::string ToString() const override { return "KeyPressedEvent: (" + std::to_string(KeyCode) + ") (" + std::to_string(repeatCount) + " repeats)"; }

        EventType GetEventType() const override { return EventType::KeyPressed; }
        static EventType GetStaticType() { return EventType::KeyPressed; }
        std::string GetName() const override { return "KeyPressedEvent"; }
    private:
        int repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(const int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override { return "KeyReleasedEvent: (" + std::to_string(KeyCode) + ")"; }

        EventType GetEventType() const override { return EventType::KeyReleased; }
        static EventType GetStaticType() { return EventType::KeyReleased; }
        std::string GetName() const override { return "KeyReleasedEvent"; }
    };

    //MOUSE EVENTS
    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(const double x, const double y) : x(x), y(y) {}

        double GetX() const { return x; }
        double GetY() const { return y; }

        EventType GetEventType() const override { return EventType::MouseMoved; }
        static EventType GetStaticType() { return EventType::MouseMoved; }
        std::string GetName() const override { return "MouseMovedEvent"; }
        std::string ToString() const override {
            return "MouseMovedEvent: (" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }
    private:
        double x, y;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(double xOffset, double yOffset) : xOffset(xOffset), yOffset(yOffset) {}

        double GetXOffset() const { return xOffset; }
        double GetYOffset() const { return yOffset; }

        EventType GetEventType() const override { return EventType::MouseScrolled; }
        static EventType GetStaticType() { return EventType::MouseScrolled; }
        std::string GetName() const override { return "MouseScrolledEvent"; }
        std::string ToString() const override {
            return "MouseScrolledEvent: (" + std::to_string(xOffset) + ", " + std::to_string(yOffset) + ")";
        }
    private:
        double xOffset, yOffset;
    };

    //abstract
    class MouseButtonEvent : public Event {
    public:
        int GetMouseButton() const { return button; }
        std::string ToString() const override { return GetName() + ": (" + std::to_string(button) + ")"; }
    protected:
        MouseButtonEvent(const int button) : button(button) {}

        int button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(const int button) : MouseButtonEvent(button) {}

        EventType GetEventType() const override { return EventType::MouseButtonPressed; }
        static EventType GetStaticType() { return EventType::MouseButtonPressed; }
        std::string GetName() const override { return "MouseButtonPressedEvent"; }
    };
    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(const int button) : MouseButtonEvent(button) {}

        EventType GetEventType() const override { return EventType::MouseButtonReleased; }
        static EventType GetStaticType() { return EventType::MouseButtonReleased; }
        std::string GetName() const override { return "MouseButtonReleasedEvent"; }
    };
}