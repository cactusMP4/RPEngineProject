#pragma once
#include "Event.h"
#include "Logger.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace rpe {
    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        explicit Window(std::string title = "Rainbow powered app", int width = 800, int height = 600);

        void Init();
        void Update() const;
        void Destroy() const;

        GLFWwindow* getWindow() const { return window; }

        int GetWidth() const { return data.width; }
        void SetWidth(const int newWidth) { data.width = newWidth; }
        int GetHeight() const { return data.height; }
        void SetHeight(const int newHeight) { data.height = newHeight; }

        std::string GetTitle() const { return data.title; }
        void SetTitle(const std::string& newTitle) { data.title = newTitle; }

        EventCallbackFn getEventCallBack() {return data.eventCallback;}
        void SetEventCallback(const EventCallbackFn& newCallback) { data.eventCallback = newCallback; }
    private:
        GLFWwindow* window;

        struct windowData {
            std::string title;
            int width, height;
            bool inited = false;
            EventCallbackFn eventCallback;
        };

        windowData data;
    };
}
