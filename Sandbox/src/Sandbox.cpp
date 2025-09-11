#include <RPEngine.h>

class Sandbox : public rpe::Application {};

int main() {
    rpe::Logger::Init();
    RPE_INFO("zdarov");

    auto window = rpe::Window();
    window.Init();

    auto* sandbox = new Sandbox();
    sandbox->run();
    delete sandbox;
    return 0;
}
