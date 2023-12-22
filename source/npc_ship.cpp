#include "../include/npc_ship.h"
#include "../include/world.h"
#include "raylib.h"
// debug
#include <iostream>

NpcShip::NpcShip(std::size_t id) : Spaceship(id) {
    Position = GetSpawnPoint();
    Rotation = static_cast<float>(GetRandomValue(-180, 180));
    Speed = static_cast<float>(GetRandomValue(200, 700));
    RotationSpeed = static_cast<float>(GetRandomValue(50, 200));
    MaxShield = static_cast<float>(GetRandomValue(50, 150));
    Shield = MaxShield;
}

void NpcShip::rotateToTarget() {
    // within 1 degrees
    if (std::abs(Rotation - _targetRotation) > 1.0f) {
        float rotationDelta = _targetRotation - Rotation;
        rotationDelta = fmod(rotationDelta + 180.0f, 360.0f) - 180.0f;
        // ensure rotationDir is within -180 and 180 degrees
        float rotationDir = (rotationDelta > 0.0f) ? 1.0f : -1.0f;
        Rotation += RotationSpeed * rotationDir * GetFrameTime();
    }
}

void NpcShip::passiveFlight() {
    _randomDirectionTimer -= GetFrameTime();
    rotateToTarget();
    if (_randomDirectionTimer <= 0.0f) {
        _randomDirectionTimer = static_cast<float>(GetRandomValue(5, 10));
        _targetRotation = static_cast<float>(GetRandomValue(-180, 180));
    }
}

void NpcShip::avoidPlayer() {
    const Player& player = World::player;
    Vector2 positionDifference = Vector2Subtract(Position, player.Position);
    float angle = std::atan2(positionDifference.y, positionDifference.x) * RAD2DEG;
    _targetRotation = angle;
    rotateToTarget();
}

void NpcShip::findPlayer() {
    const Player& player = World::player;
    Vector2 positionDifference = Vector2Subtract(player.Position, Position);
    float angle = std::atan2(positionDifference.y, positionDifference.x) * RAD2DEG;
    _targetRotation = angle;
    rotateToTarget();
}

void NpcShip::updateState() {
    switch (_state) {
        case State::BrainDead:
        {
            break;
        }
        case State::Passive:
        {
            passiveFlight();
            break;
        }
        case State::Flighty:
        {
            avoidPlayer();
            break;
        }
        case State::Aggresive:
        {
            findPlayer();
            break;
        }
    }
}

void NpcShip::ReactToDamage() {
    _state = GetRandomValue(0, 1) ? State::Flighty : State::Aggresive;
}

void NpcShip::Update() {
    updateState();
    Spaceship::Update();
}