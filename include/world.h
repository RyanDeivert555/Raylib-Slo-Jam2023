#pragma once
#include "spaceship.h"
#include <vector>

namespace World {
    extern std::vector<Spaceship> spaceships;

    Spaceship& SpawnSpaceship(std::size_t textureId);
    void UpdateSpaceships();
    void DrawSpaceships();
}