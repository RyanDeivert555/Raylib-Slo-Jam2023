#include "../include/world.h"
#include <vector>

namespace World {
    std::vector<Spaceship> spaceships{};

    Spaceship& SpawnSpaceship(std::size_t textureId) {
        spaceships.emplace_back(textureId);
        return spaceships.back();
    }

    void UpdateSpaceships() {
        for (auto& ship : spaceships) {
            ship.Update();
        }
        std::erase_if(spaceships, [](const Spaceship& s) { return !s.Alive; });
    }

    void DrawSpaceships() {
        for (const auto& ship : spaceships) {
            ship.Draw();
        }
    }
}