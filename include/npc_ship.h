#pragma once
#include "spaceship.h"

enum class State {
    BrainDead,
    Passive,
    Flighty,
    Aggresive,
};

class NpcShip : public Spaceship {
private:
    float _randomDirectionTimer = static_cast<float>(GetRandomValue(3, 6));
    float _targetRotation = 0.0f;
    State _state = State::Passive;

    void rotateToTarget();
    void passiveFlight();
    void avoidPlayer();
    void findPlayer();
    void updateState();

public:
    NpcShip(std::size_t id);
    void SetState(State newState);
    void Update() override;
};