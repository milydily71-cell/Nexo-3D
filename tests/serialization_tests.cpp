#include "nexo/scene.hpp"
#include "nexo/scene_serialization.hpp"

#include <cassert>
#include <sstream>

int main() {
    nexo::Scene original;
    auto& camera = original.createEntity("Main \"Camera\"");
    camera.transform.position = {1.25F, 2.5F, -3.75F};
    camera.transform.rotationDegrees = {0.0F, 90.0F, 0.0F};
    camera.transform.scale = {1.0F, 1.0F, 1.0F};
    auto& hidden = original.createEntity("Hidden");
    hidden.active = false;

    std::stringstream document;
    std::string error;
    assert(nexo::saveScene(document, original, error));
    auto loaded = nexo::loadScene(document);
    assert(loaded);
    assert(loaded.scene->size() == 2);
    assert(loaded.scene->find(1)->name == "Main \"Camera\"");
    assert(loaded.scene->find(1)->transform.position.y == 2.5F);
    assert(!loaded.scene->find(2)->active);

    std::stringstream badVersion("NEXO_SCENE 999\n");
    auto rejected = nexo::loadScene(badVersion);
    assert(!rejected);
    assert(!rejected.error.empty());
    return 0;
}
