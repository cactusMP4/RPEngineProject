#include <RPEngine.h>

class Sandbox : public rpe::Application {
public:
    Sandbox() {};
    ~Sandbox() {};
};

int main() {
    auto* sandbox = new Sandbox();
    sandbox->run();
    delete sandbox;
    return 0;
}
