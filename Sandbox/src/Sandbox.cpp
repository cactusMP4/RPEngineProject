#include <RPEngine.h>

class ExampleLayer : public rpe::Layer {
public:
    ExampleLayer() : Layer("ExampleLayer") {}

    void Update() override {
        RPE_TRACE("ExampleLayer::Update");
    }
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

