#pragma once

#include "nexo/scene.hpp"

#include <iomanip>
#include <istream>
#include <optional>
#include <ostream>
#include <string>

namespace nexo {

inline constexpr unsigned kSceneFormatVersion = 1;

struct SceneLoadResult {
    std::optional<Scene> scene;
    std::string error;
    [[nodiscard]] explicit operator bool() const noexcept { return scene.has_value(); }
};

/// Writes a deterministic, versioned, line-oriented scene document.
/// Format: NEXO_SCENE <version>, then one ENTITY record per scene entity.
inline bool saveScene(std::ostream& output, const Scene& scene, std::string& error) {
    output << "NEXO_SCENE " << kSceneFormatVersion << '\n';
    for (const auto& entity : scene.entities()) {
        const auto& t = entity.transform;
        output << "ENTITY " << entity.id << ' ' << std::quoted(entity.name) << ' '
               << (entity.active ? 1 : 0) << ' '
               << std::setprecision(9)
               << t.position.x << ' ' << t.position.y << ' ' << t.position.z << ' '
               << t.rotationDegrees.x << ' ' << t.rotationDegrees.y << ' ' << t.rotationDegrees.z << ' '
               << t.scale.x << ' ' << t.scale.y << ' ' << t.scale.z << '\n';
    }
    if (!output.good()) {
        error = "Failed while writing Nexo scene document";
        return false;
    }
    error.clear();
    return true;
}

inline SceneLoadResult loadScene(std::istream& input) {
    std::string magic;
    unsigned version = 0;
    if (!(input >> magic >> version) || magic != "NEXO_SCENE") {
        return {std::nullopt, "Invalid scene header"};
    }
    if (version != kSceneFormatVersion) {
        return {std::nullopt, "Unsupported Nexo scene format version: " + std::to_string(version)};
    }

    Scene scene;
    std::string record;
    while (input >> record) {
        if (record != "ENTITY") return {std::nullopt, "Unknown scene record: " + record};
        EntityId savedId = 0;
        std::string name;
        int active = 1;
        Transform transform{};
        if (!(input >> savedId >> std::quoted(name) >> active
                    >> transform.position.x >> transform.position.y >> transform.position.z
                    >> transform.rotationDegrees.x >> transform.rotationDegrees.y >> transform.rotationDegrees.z
                    >> transform.scale.x >> transform.scale.y >> transform.scale.z)) {
            return {std::nullopt, "Malformed ENTITY record"};
        }
        if (name.empty() || (active != 0 && active != 1)) {
            return {std::nullopt, "Invalid ENTITY name or active flag"};
        }
        auto& entity = scene.createEntity(name);
        if (entity.id != savedId) {
            return {std::nullopt, "Entity IDs must be contiguous and ordered in format version 1"};
        }
        entity.active = active != 0;
        entity.transform = transform;
    }
    if (input.bad()) return {std::nullopt, "I/O error while reading scene"};
    return {std::move(scene), {}};
}

} // namespace nexo
