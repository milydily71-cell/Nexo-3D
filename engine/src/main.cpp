#include "nexo/scene.hpp"
#include "nexo/vulkan_renderer.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

int main() {
    std::cout << "Nexo-3D Engine v0.2.0\n";
    std::cout << "Runtime: C++20\n";
    nexo::Scene scene;
    auto& camera = scene.createEntity("Main Camera");
    const auto cameraId = camera.id;
    auto& cube = scene.createEntity("Starter Cube");
    cube.transform.position = {0.0F, 0.0F, 0.0F};
    std::cout << "Scene: " << scene.size() << " entities initialized\n";
    std::cout << "Camera entity ID: " << cameraId << "\n";
    nexo::VulkanRenderer renderer;
    std::string error;
    if (renderer.initialize(error)) {
        std::cout << "Renderer: Vulkan instance initialized\n";
    } else {
        std::cout << "Renderer: Vulkan bootstrap unavailable: " << error << "\n";
        std::cout << "Note: swapchain, GPU selection, and draw pipeline are not implemented yet.\n";
    }
    return EXIT_SUCCESS;
}
