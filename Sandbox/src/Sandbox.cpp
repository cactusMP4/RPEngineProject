#include <RPEngine.h>

class Sandbox : public rpe::Application {
public:
    Sandbox() {};
    ~Sandbox() {};
};

int main() {
    rpe::Logger::Init();
    rpe::Logger::GetClientLogger()->info("salam");

    auto* sandbox = new Sandbox();
    sandbox->run();
    delete sandbox;
    return 0;
}
