#pragma once
#include "spaceship.h"

enum class State {
    Passive,
    Flighty,
    Aggresive,
};

class NpcShip : public Spaceship {
private:
    float _randomDirectionTimer = static_cast<float>(GetRandomValue(3, 10));
    float _targetRotation = 0.0f;
    State _state = State::Passive;

    void passiveFlight();
    void avoidPlayer();
    void findPlayer();
    void updateState();

public:
    NpcShip(std::size_t id);
    void Update() override;
};