#include "Application.h"

#include <memory>

namespace rpe {
    Application* Application::instance = nullptr;

    Application::Application() {
        RPE_CORE_INFO("Creating application");

        if (instance) {
            RPE_CORE_WARN("Application already exists");
            return;
        }
        instance = this;

        window = std::make_unique<Window>();
        window->Init();
        window->SetEventCallback(RPE_BIND_EVENT_FN(Application::onEvent));

        imguiLayer = new ImGuiLayer();
        PushOverlay(imguiLayer);

        //VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        //VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        static float vertices[] = {
            -0.2f, -0.2f, 0.0f,
            0.0f,  0.2f,  0.0f,
            0.2f,  -0.2f, 0.0f,
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        //Index Buffer
        unsigned int indices[] = {0, 1, 2};

        glGenBuffers(1, &IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        shader = std::make_unique<Shader>("assets/shaders/default.glsl");
        shader->Bind();
    }
    Application::~Application() {
        running = false;
    }

    void Application::onEvent(Event& event) {
        RPE_CORE_TRACE("Event: {0}", event.ToString());

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(RPE_BIND_EVENT_FN(Application::onWindowClosed));

        for (auto it = layers.end(); it != layers.begin(); ) {
            (*--it)->OnEvent(event);
            if (event.Handled) {
                //do not continue
                //(we don't want to shoot in FPS when we press a UI button for example)
                break;
            }
        }
    }

    void Application::run() {
        RPE_CORE_INFO("Running app...");

        running = true;
        while (running) {
            glClearColor(0.11f, 0.11f, 0.18f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            imguiLayer->Begin();
            for (Layer* layer : layers) {
                layer->Update();
                layer->RenderImGui();
            }
            imguiLayer->End();

            window->Update();
        }
    }
    bool Application::onWindowClosed(WindowCloseEvent &event) {
        RPE_CORE_INFO("Closing window. ");

        running = false;
        return true;
    }

    void Application::PushLayer(Layer *layer) {
        layers.PushLayer(layer);
    }
    void Application::PushOverlay(Layer *overlay) {
        layers.PushLayer(overlay);
    }
}
