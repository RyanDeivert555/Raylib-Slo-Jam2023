#include "../include/npc_ship.h"
#include "../include/world.h"
#include "raylib.h"
// debug
#include <iostream>

NpcShip::NpcShip(std::size_t id) : Spaceship(id) {
    // TODO: randomvalues
    Vector2 screenOrigin = GetScreenToWorld2D(Vector2Zero(), World::camera);
    Vector2 screenBounds = GetScreenToWorld2D(Vector2{windowWidth, windowHeight}, World::camera);
    
    const Vector2 PossibleSpawnPoints[] = {
        // top
        GetRandomVector2(-SpawnOffset + screenOrigin.x, screenBounds.x + SpawnOffset, -SpawnOffset + screenOrigin.y, screenOrigin.y),
        // bottom
        GetRandomVector2(-SpawnOffset + screenOrigin.x, screenBounds.x + SpawnOffset, screenBounds.y, screenBounds.y + SpawnOffset),
        // left
        GetRandomVector2(-SpawnOffset + screenOrigin.x, screenOrigin.x, -SpawnOffset + screenBounds.y, screenBounds.y + SpawnOffset),
        // right
        GetRandomVector2(screenBounds.x, screenBounds.x + SpawnOffset, -SpawnOffset + screenOrigin.y, screenBounds.y),
    };
    int randIndex = GetRandomValue(0, 3);
    Position = PossibleSpawnPoints[randIndex];
    Rotation = static_cast<float>(GetRandomValue(-180, 180));
    Speed = static_cast<float>(GetRandomValue(150, 400));
    RotationSpeed = static_cast<float>(GetRandomValue(50, 200));
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

void NpcShip::SetState(State newState) {
    _state = newState;
}

void NpcShip::Update() {
    updateState();
    Spaceship::Update();
}