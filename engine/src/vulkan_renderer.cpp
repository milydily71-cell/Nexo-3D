#include "nexo/vulkan_renderer.hpp"

#ifdef NEXO_HAS_VULKAN
#include <vulkan/vulkan.h>
#endif

namespace nexo {

VulkanRenderer::~VulkanRenderer() {
#ifdef NEXO_HAS_VULKAN
    if (instance_ != nullptr) {
        vkDestroyInstance(static_cast<VkInstance>(instance_), nullptr);
        instance_ = nullptr;
    }
#endif
}

bool VulkanRenderer::initialize(std::string& error) {
#ifdef NEXO_HAS_VULKAN
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Nexo-3D";
    appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 0, 1, 0);
    appInfo.pEngineName = "Nexo-3D";
    appInfo.engineVersion = VK_MAKE_API_VERSION(0, 0, 1, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkInstance instance = VK_NULL_HANDLE;
    const VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS) {
        error = "vkCreateInstance failed with VkResult " + std::to_string(static_cast<int>(result));
        return false;
    }
    instance_ = instance;
    error.clear();
    return true;
#else
    error = "Vulkan SDK/loader was not found at build time";
    return false;
#endif
}

bool VulkanRenderer::available() const noexcept {
#ifdef NEXO_HAS_VULKAN
    return instance_ != nullptr;
#else
    return false;
#endif
}

const char* VulkanRenderer::backendName() const noexcept {
#ifdef NEXO_HAS_VULKAN
    return "Vulkan";
#else
    return "Vulkan (not built; install Vulkan SDK/loader)";
#endif
}

} // namespace nexo
