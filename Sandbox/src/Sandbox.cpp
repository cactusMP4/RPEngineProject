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

