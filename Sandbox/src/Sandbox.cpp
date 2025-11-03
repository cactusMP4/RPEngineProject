#include <RPEngine.h>

std::shared_ptr<rpe::VertexArray> vertexArray;
std::shared_ptr<rpe::VertexBuffer> vertexBuffer;
std::shared_ptr<rpe::IndexBuffer> indexBuffer;
std::shared_ptr<rpe::Shader> shader;
rpe::Camera camera;

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

        camera = rpe::Camera();
        camera.SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
        camera.SetLookDir(glm::vec3(0.0f, 0.0f, -1.0f));
    }

    void Update() override {
        if (rpe::Input::IsKeyPressed(GLFW_KEY_W)) {
            camera.Move(camera.GetLookDir() * 0.01f);
        }
        if (rpe::Input::IsKeyPressed(GLFW_KEY_A)) {
            camera.Move(
                glm::vec4(camera.GetLookDir(), 1.0f)
                * glm::rotate(glm::mat4(1.0f), static_cast<float>(glm::radians(-90.0f)), glm::vec3(0.0f, 1.0f, 0.0f))
                * 0.01f
            );
        }
        if (rpe::Input::IsKeyPressed(GLFW_KEY_S)) {
            camera.Move(-camera.GetLookDir() * 0.01f);
        }
        if (rpe::Input::IsKeyPressed(GLFW_KEY_D)) {
            camera.Move(
                glm::vec4(camera.GetLookDir(), 1.0f)
                * glm::rotate(glm::mat4(1.0f), static_cast<float>(glm::radians(90.0f)), glm::vec3(0.0f, 1.0f, 0.0f))
                * 0.01f
            );
        }

        if (rpe::Input::IsKeyPressed(GLFW_KEY_LEFT)) {
            camera.SetLookDir(glm::vec4(camera.GetLookDir(), 1.0f) * glm::rotate(glm::mat4(1.0f), -0.01f, glm::vec3(0.0f, 1.0f, 0.0f)));
        }
        if (rpe::Input::IsKeyPressed(GLFW_KEY_RIGHT)) {
            camera.SetLookDir(glm::vec4(camera.GetLookDir(), 1.0f) * glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        rpe::Renderer::BeginScene(camera);

        rpe::Renderer::Submit(vertexArray, shader);

        rpe::Renderer::EndScene();
    }
    void RenderImGui() override {
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

