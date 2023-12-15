#pragma once
#include "spaceship.h"

class NpcShip : public Spaceship {
private:
    void avoidPlayer();
    void findPlayer();

public:
    NpcShip(std::size_t id);
    void Update() override;
};