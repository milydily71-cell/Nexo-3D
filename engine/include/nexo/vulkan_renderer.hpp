#pragma once

#include <string>

namespace nexo {

class VulkanRenderer final {
public:
    VulkanRenderer() = default;
    ~VulkanRenderer();

    VulkanRenderer(const VulkanRenderer&) = delete;
    VulkanRenderer& operator=(const VulkanRenderer&) = delete;

    [[nodiscard]] bool initialize(std::string& error);
    [[nodiscard]] bool available() const noexcept;
    [[nodiscard]] const char* backendName() const noexcept;

private:
    void* instance_{nullptr};
};

} // namespace nexo
