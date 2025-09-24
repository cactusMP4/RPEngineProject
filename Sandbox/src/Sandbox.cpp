#include <RPEngine.h>

class ExampleLayer : public rpe::Layer {
public:
    ExampleLayer() : Layer("ExampleLayer") {}

    void Attach() override {
        RPE_INFO("Attaching example layer");
    }

    void Update() override {
    }
    void RenderImGui() override {
        ImGui::Begin("test");
        ImGui::Text("Hello World!");
        ImGui::End();
    };
    void OnEvent(rpe::Event& e) override {
        RPE_TRACE("ExampleLayer::OnEvent ({0})", e.ToString());
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

