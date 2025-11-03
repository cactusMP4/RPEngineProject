#include <RPEngine.h>

std::shared_ptr<rpe::VertexArray> vertexArray;
std::shared_ptr<rpe::VertexBuffer> vertexBuffer;
std::shared_ptr<rpe::IndexBuffer> indexBuffer;
std::shared_ptr<rpe::Shader> shader;
std::shared_ptr<rpe::Camera> camera;

rpe::Transform squareTransform;

class ExampleLayer : public rpe::Layer {
public:
    ExampleLayer() : Layer("ExampleLayer") {}

    void Attach() override {
        RPE_INFO("Attaching example layer");

        //VAO
        vertexArray = std::make_unique<rpe::VertexArray>();

        //VBO
        float vertices[] = {
            //positon               //color
            -0.2f, -0.2f,  0.0f,    1.0f, 0.0f, 0.0f, 0.0f,
            -0.2f,  0.2f,  0.0f,    0.0f, 1.0f, 0.0f, 0.0f,
             0.2f,  0.2f,  0.0f,    0.0f, 0.0f, 1.0f, 0.0f,
             0.2f, -0.2f,  0.0f,    1.0f, 0.0f, 1.0f, 0.0f,
        };

        vertexBuffer = std::make_unique<rpe::VertexBuffer>(vertices, sizeof(vertices));

        rpe::BufferLayout layout = {
            {rpe::ShaderDataType::Float3, "a_Pos"},
            {rpe::ShaderDataType::Float4, "a_Color"},
        };

        vertexBuffer->SetLayout(layout);
        vertexArray->AddVertexBuffer(vertexBuffer);

        //Index Buffer
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        indexBuffer = std::make_unique<rpe::IndexBuffer>(indices, sizeof(indices)/sizeof(unsigned int));
        vertexArray->SetIndexBuffer(indexBuffer);

        shader = std::make_unique<rpe::Shader>("assets/shaders/default.glsl");

        camera = std::make_unique<rpe::Camera>();
        camera->GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
        camera->GetTransform().SetLookDir(glm::vec3(0.0f, 0.0f, -1.0f));
    }

    void Update(rpe::TimeStep dt) override {
        if (rpe::Input::IsKeyPressed(GLFW_KEY_W)) {
            camera->GetTransform().Move(camera->GetTransform().GetLookDir() * 0.01f);
        }
        if (rpe::Input::IsKeyPressed(GLFW_KEY_A)) {
            camera->GetTransform().Move(
                glm::vec4(camera->GetTransform().GetLookDir(), 1.0f)
                * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                * dt.GetTimeS()
            );
        }
        if (rpe::Input::IsKeyPressed(GLFW_KEY_S)) {
            camera->GetTransform().Move(-camera->GetTransform().GetLookDir() * 0.01f);
        }
        if (rpe::Input::IsKeyPressed(GLFW_KEY_D)) {
            camera->GetTransform().Move(
                glm::vec4(camera->GetTransform().GetLookDir(), 1.0f)
                * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                * dt.GetTimeS()
            );
        }

        if (rpe::Input::IsKeyPressed(GLFW_KEY_LEFT)) {
            camera->GetTransform().SetLookDir(
                glm::vec4(camera->GetTransform().GetLookDir(), 1.0f)
                * glm::rotate(glm::mat4(1.0f), -0.01f, glm::vec3(0.0f, 1.0f, 0.0f))
            );
        }
        if (rpe::Input::IsKeyPressed(GLFW_KEY_RIGHT)) {
            camera->GetTransform().SetLookDir(
                glm::vec4(camera->GetTransform().GetLookDir(), 1.0f)
                * glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0.0f, 1.0f, 0.0f))
            );
        }

        rpe::Renderer::BeginScene(*camera);

        squareTransform.SetPosition(glm::vec3(0.0f, sin(glfwGetTime()) * 0.2f, 0.0f));
        rpe::Renderer::Submit(vertexArray, shader, squareTransform);

        rpe::Renderer::EndScene();
    }
    void RenderImGui(rpe::TimeStep dt) override {
		ImGui::Begin("Hello, RPEngine!");
		ImGui::LabelText("", "XD");
		ImGui::End();
    };
    void OnEvent(rpe::Event& e) override {
    }
};

class Sandbox : public rpe::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
};

int main() {
    rpe::Logger::Init();

    auto* sandbox = new Sandbox();
    sandbox->run();
    delete sandbox;

    return 0;
}

