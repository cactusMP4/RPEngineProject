#include "Application.h"

#include <memory>

#include "Input.h"
#include "Render/Camera.h"
#include "Render/Renderer.h"

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
		vertexArray = std::make_unique<VertexArray>();

        //VBO
        float vertices[] = {
            //positon               //color
            -0.2f, -0.2f,  0.0f,    1.0f, 0.0f, 0.0f, 0.0f,
            -0.2f,  0.2f,  0.0f,    0.0f, 1.0f, 0.0f, 0.0f,
             0.2f,  0.2f,  0.0f,    0.0f, 0.0f, 1.0f, 0.0f,
             0.2f, -0.2f,  0.0f,    1.0f, 0.0f, 1.0f, 0.0f,
        };

        vertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

		BufferLayout layout = {
            {ShaderDataType::Float3, "a_Pos"},
            {ShaderDataType::Float4, "a_Color"},
		};

        vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

        //Index Buffer
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        indexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices)/sizeof(unsigned int));
		vertexArray->SetIndexBuffer(indexBuffer);

        shader = std::make_unique<Shader>("assets/shaders/default.glsl");

        camera = Camera();
        camera.SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
        camera.SetLookDir(glm::vec3(0.0f, 0.0f, -1.0f));
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

            if (Input::IsKeyPressed(GLFW_KEY_W)) {
                camera.Move(camera.GetLookDir() * 0.01f);
            }
            if (Input::IsKeyPressed(GLFW_KEY_A)) {
                camera.Move(glm::vec4(camera.GetLookDir(), 1.0f) * glm::rotate(glm::mat4(1.0f), -static_cast<float>(M_PI_2), glm::vec3(0.0f, 1.0f, 0.0f)) * 0.01f);
            }
            if (Input::IsKeyPressed(GLFW_KEY_S)) {
                camera.Move(-camera.GetLookDir() * 0.01f);
            }
            if (Input::IsKeyPressed(GLFW_KEY_D)) {
                camera.Move(glm::vec4(camera.GetLookDir(), 1.0f) * glm::rotate(glm::mat4(1.0f), static_cast<float>(M_PI_2), glm::vec3(0.0f, 1.0f, 0.0f)) * 0.01f);
            }

            if (Input::IsKeyPressed(GLFW_KEY_LEFT)) {
                camera.SetLookDir(glm::vec4(camera.GetLookDir(), 1.0f) * glm::rotate(glm::mat4(1.0f), -0.01f, glm::vec3(0.0f, 1.0f, 0.0f)));
            }
            if (Input::IsKeyPressed(GLFW_KEY_RIGHT)) {
                camera.SetLookDir(glm::vec4(camera.GetLookDir(), 1.0f) * glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0.0f, 1.0f, 0.0f)));
            }


            Renderer::BeginScene(camera);

            Renderer::Submit(vertexArray, shader);

            Renderer::EndScene();

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
