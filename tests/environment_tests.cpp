#include "nexo/environment.hpp"
#include "nexo/render_presets.hpp"

#include <cassert>
#include <cstddef>

int main() {
    nexo::GridSettings settings;
    const auto vertices = nexo::buildGridVertices(settings);
    assert(!vertices.empty());
    assert(vertices.size() % 2 == 0);
    assert(vertices.front().position.y == 0.0F);

    auto low = nexo::qualityPreset(nexo::GraphicsPreset::MobileLow);
    auto balanced = nexo::qualityPreset(nexo::GraphicsPreset::MobileBalanced);
    auto high = nexo::qualityPreset(nexo::GraphicsPreset::MobileHigh);
    auto cinematic = nexo::qualityPreset(nexo::GraphicsPreset::Cinematic);
    assert(low.shadowResolution < balanced.shadowResolution);
    assert(balanced.shadowResolution < high.shadowResolution);
    assert(high.shadowResolution < cinematic.shadowResolution);
    assert(!low.hdr && balanced.hdr);
    assert(cinematic.volumetricClouds);

    settings.spacing = 0.0F;
    assert(nexo::buildGridVertices(settings).empty());
    return 0;
}
