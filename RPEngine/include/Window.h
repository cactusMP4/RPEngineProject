#pragma once
#include "Event.h"
#include "Logger.h"

#include "GLFW/glfw3.h"

namespace rpe {
    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(std::string title = "Rainbow powered app", unsigned int width = 800, unsigned int height = 600) : title(std::move(title)), width(width), height(height) {};

        void Init();
        void Update() const;
        void Destroy() const;

        GLFWwindow* getWindow() const { return window; }

        int GetWidth() const { return width; }
        void SetWidth(const unsigned int newWidth) { this->width = newWidth; }
        int GetHeight() const { return height; }
        void SetHeight(const unsigned int newHeight) { this->height = newHeight; }

        std::string GetTitle() const { return title; }
        void SetTitle(const std::string& newTitle) { this->title = newTitle; }

        EventCallbackFn getEventCallBack() {return eventCallback;}
        void SetEventCallback(const EventCallbackFn& newCallback) { eventCallback = newCallback; }
    private:
        GLFWwindow* window;
        std::string title;
        int width, height;
        bool inited = false;
        EventCallbackFn eventCallback;
    };
}
