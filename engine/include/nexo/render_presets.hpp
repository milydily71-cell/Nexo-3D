#pragma once
#include "nexo/environment.hpp"

namespace nexo {

[[nodiscard]] inline RenderQuality qualityPreset(GraphicsPreset preset) {
    switch (preset) {
    case GraphicsPreset::MobileLow:
        return {preset, 512, 1, false, false, false, false, true, 0.70F};
    case GraphicsPreset::MobileBalanced:
        return {preset, 1024, 1, true, false, false, false, true, 1.0F};
    case GraphicsPreset::MobileHigh:
        return {preset, 2048, 2, true, true, true, false, true, 1.0F};
    case GraphicsPreset::Cinematic:
        return {preset, 4096, 4, true, true, true, true, true, 1.0F};
    }
    return {};
}

} // namespace nexo
