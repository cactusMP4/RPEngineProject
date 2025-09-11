#include <RPEngine.h>

class Sandbox : public rpe::Application {};

int main() {
    rpe::Logger::Init();

    auto* sandbox = new Sandbox();
    sandbox->run();
    delete sandbox;

    return 0;
}

