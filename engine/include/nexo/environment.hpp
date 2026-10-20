#pragma once

#include "nexo/scene.hpp"

#include <cstdint>
#include <vector>

namespace nexo {

struct Color3 { float r{1.0F}; float g{1.0F}; float b{1.0F}; };
struct Vertex3D { Vec3 position; Color3 color; };

struct GridSettings {
    float halfExtent{50.0F};
    float spacing{1.0F};
    float majorEvery{5.0F};
    Color3 minorColor{0.20F, 0.24F, 0.30F};
    Color3 majorColor{0.35F, 0.42F, 0.52F};
    Color3 axisXColor{0.85F, 0.22F, 0.20F};
    Color3 axisZColor{0.20F, 0.55F, 0.95F};
};

struct SunSettings {
    Vec3 direction{-0.35F, -0.82F, -0.45F};
    Color3 color{1.0F, 0.91F, 0.76F};
    float intensity{4.0F};
    float angularRadiusDegrees{0.27F};
};

struct SkySettings {
    Color3 zenith{0.10F, 0.24F, 0.48F};
    Color3 horizon{0.64F, 0.76F, 0.88F};
    Color3 cloudColor{0.94F, 0.96F, 1.0F};
    float cloudCoverage{0.42F};
    float cloudDensity{0.65F};
    float atmosphereThickness{1.0F};
    float sunDiskIntensity{12.0F};
};

enum class GraphicsPreset : std::uint8_t { MobileLow, MobileBalanced, MobileHigh, Cinematic };

struct RenderQuality {
    GraphicsPreset preset{GraphicsPreset::MobileBalanced};
    std::uint32_t shadowResolution{1024};
    std::uint32_t msaaSamples{1};
    bool hdr{true};
    bool bloom{false};
    bool ambientOcclusion{false};
    bool volumetricClouds{false};
    bool dynamicResolution{true};
    float renderScale{1.0F};
};

/// Scene-side data for a geometry grid and physically motivated sky lighting.
/// This describes geometry/material inputs; the Vulkan GPU draw pipeline must consume it.
struct EnvironmentSettings {
    GridSettings grid{};
    SunSettings sun{};
    SkySettings sky{};
    RenderQuality quality{};
};

/// Creates actual line-list vertex data for a floor grid. No screen/background color fill.
[[nodiscard]] inline std::vector<Vertex3D> buildGridVertices(const GridSettings& settings) {
    std::vector<Vertex3D> vertices;
    if (settings.spacing <= 0.0F || settings.halfExtent <= 0.0F) return vertices;
    const auto steps = static_cast<int>(settings.halfExtent / settings.spacing);
    vertices.reserve(static_cast<std::size_t>((steps * 2 + 1) * 4));
    for (int i = -steps; i <= steps; ++i) {
        const float p = static_cast<float>(i) * settings.spacing;
        const bool major = settings.majorEvery > 0.0F &&
            (static_cast<int>(i) % static_cast<int>(settings.majorEvery / settings.spacing == 0.0F ? 1.0F : settings.majorEvery / settings.spacing)) == 0;
        const Color3 xLine = (i == 0) ? settings.axisXColor : (major ? settings.majorColor : settings.minorColor);
        const Color3 zLine = (i == 0) ? settings.axisZColor : (major ? settings.majorColor : settings.minorColor);
        vertices.push_back({{-settings.halfExtent, 0.0F, p}, xLine});
        vertices.push_back({{ settings.halfExtent, 0.0F, p}, xLine});
        vertices.push_back({{p, 0.0F, -settings.halfExtent}, zLine});
        vertices.push_back({{p, 0.0F,  settings.halfExtent}, zLine});
    }
    return vertices;
}

} // namespace nexo
