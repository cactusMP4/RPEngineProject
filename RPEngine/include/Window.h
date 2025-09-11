#pragma once
#include "RPEngine.h"

#include "GLFW/glfw3.h"

namespace rpe {
    class Window {
    public:
        Window(std::string title = "Rainbow powered app", unsigned int width = 800, unsigned int height = 600) : title(std::move(title)), width(width), height(height) {};

        bool Init();
        void Update() const;

        GLFWwindow* getWindow() const { return window; }

        unsigned int GetWidth() const { return width; }
        void SetWidth(const unsigned int newWidth) { this->width = newWidth; }
        unsigned int GetHeight() const { return height; }
        void SetHeight(const unsigned int newHeight) { this->height = newHeight; }

        std::string GetTitle() const { return title; }
        void SetTitle(const std::string& newTitle) { this->title = newTitle; }
    private:
        GLFWwindow* window;
        std::string title;
        unsigned int width, height;
        bool inited = false;
        bool running = true;
    };
}
