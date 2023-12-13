#pragma once
#include "spaceship.h"

class Player : public Spaceship {
private:
    void getInput();
public:
    static constexpr float Acceleration = 200.0f;
    static constexpr float MaxSpeed = 500.0f;
    static constexpr float MinSpeed = 100.0f;

    Player(std::size_t id);
    void Update() override;
};