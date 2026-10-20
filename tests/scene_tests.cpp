#include "nexo/scene.hpp"

#include <cassert>

int main() {
    nexo::Scene scene;
    const auto& first = scene.createEntity("Camera");
    const auto firstId = first.id;
    auto& second = scene.createEntity("Cube");
    second.transform.position = {1.0F, 2.0F, 3.0F};

    assert(scene.size() == 2);
    assert(scene.find(firstId) != nullptr);
    assert(scene.find(firstId)->name == "Camera");
    assert(scene.find(second.id)->transform.position.y == 2.0F);
    assert(scene.find(9999) == nullptr);
    return 0;
}
