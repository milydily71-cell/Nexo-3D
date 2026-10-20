#include <cstdlib>
#include <iostream>
#include <string_view>

namespace nexo {

class Engine final {
public:
    int run() const {
        std::cout << "Nexo-3D Engine v0.1.0 (scaffold)\n";
        std::cout << "Runtime: C++20\n";
        std::cout << "Renderer: not initialized yet\n";
        std::cout << "Next milestone: scene graph + Vulkan bootstrap\n";
        return EXIT_SUCCESS;
    }
};

} // namespace nexo

int main() {
    return nexo::Engine{}.run();
}
