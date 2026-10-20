#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace nexo {

struct Vec3 {
    float x{0.0F};
    float y{0.0F};
    float z{0.0F};
};

struct Transform {
    Vec3 position{};
    Vec3 rotationDegrees{};
    Vec3 scale{1.0F, 1.0F, 1.0F};
};

using EntityId = std::uint32_t;

struct Entity {
    EntityId id{};
    std::string name;
    Transform transform{};
    bool active{true};
};

class Scene final {
public:
    Entity& createEntity(std::string name) {
        entities_.push_back(Entity{nextId_++, std::move(name), {}, true});
        return entities_.back();
    }

    [[nodiscard]] Entity* find(EntityId id) noexcept {
        for (auto& entity : entities_) {
            if (entity.id == id) return &entity;
        }
        return nullptr;
    }

    [[nodiscard]] const Entity* find(EntityId id) const noexcept {
        for (const auto& entity : entities_) {
            if (entity.id == id) return &entity;
        }
        return nullptr;
    }

    [[nodiscard]] std::size_t size() const noexcept { return entities_.size(); }
    [[nodiscard]] const std::vector<Entity>& entities() const noexcept { return entities_; }

private:
    EntityId nextId_{1};
    std::vector<Entity> entities_;
};

} // namespace nexo
