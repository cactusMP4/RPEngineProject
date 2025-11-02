#include <RPEngine.h>

class CloseWarnOverlay : public rpe::Layer {
public:
    CloseWarnOverlay() : Layer("CloseWarnOverlay") {}

    void Attach() override {
        RPE_INFO("Attaching close warn overlay");
    }

    void OnEvent(rpe::Event& e) override {
        rpe::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<rpe::WindowCloseEvent>(RPE_BIND_EVENT_FN(CloseWarnOverlay::onWindowClosed));
    }

    bool onWindowClosed(rpe::WindowCloseEvent &event) {
        RPE_CORE_INFO("Imagine popup");

        return true;
    }
};

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
        PushOverlay(new CloseWarnOverlay());
    }
};

int main() {
    rpe::Logger::Init();

    auto* sandbox = new Sandbox();
    sandbox->run();
    delete sandbox;

    return 0;
}

