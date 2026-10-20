#include "nexo/environment.hpp"
#include "nexo/render_presets.hpp"
#include "nexo/scene.hpp"
#include "nexo/vulkan_renderer.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

int main() {
    std::cout << "Nexo-3D Engine v0.3.0\n";
    std::cout << "Runtime: C++20 | Target: native Android + Vulkan\n";

    nexo::Scene scene;
    auto& camera = scene.createEntity("Main Camera");
    const auto cameraId = camera.id;
    auto& cube = scene.createEntity("Starter Cube");
    cube.transform.position = {0.0F, 0.0F, 0.0F};
    std::cout << "Scene: " << scene.size() << " entities initialized\n";
    std::cout << "Camera entity ID: " << cameraId << "\n";

    nexo::EnvironmentSettings environment;
    environment.quality = nexo::qualityPreset(nexo::GraphicsPreset::MobileBalanced);
    const auto gridVertices = nexo::buildGridVertices(environment.grid);
    std::cout << "Environment: " << gridVertices.size()
              << " CPU grid line vertices prepared; sun/sky/cloud settings loaded\n";
    std::cout << "Graphics preset: Mobile Balanced (configuration only; GPU passes pending)\n";

    nexo::VulkanRenderer renderer;
    std::string error;
    if (renderer.initialize(error)) {
        std::cout << "Renderer: Vulkan instance initialized\n";
        std::cout << "Renderer note: Android surface, swapchain, shaders, and geometry draw pipeline are not implemented yet.\n";
    } else {
        std::cout << "Renderer: Vulkan bootstrap unavailable: " << error << "\n";
    }
    return EXIT_SUCCESS;
}
