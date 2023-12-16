#include "../include/npc_ship.h"
#include "../include/world.h"
#include "raylib.h"
#include "raymath.h"
// debug
#include <complex>
#include <iostream>

NpcShip::NpcShip(std::size_t id) : Spaceship(id) {
    // TODO: randomize stats
}

void NpcShip::passiveFlight() {
    _randomDirectionTimer -= GetFrameTime();
    // within 1 degrees
    if (Rotation - _targetRotation <= 1.0f) {
        // TODO: make it rotate shortest path
        Rotation += RotationSpeed * GetFrameTime();
    }
    if (_randomDirectionTimer <= 0.0f) {
        _randomDirectionTimer = static_cast<float>(GetRandomValue(3, 10));
        _targetRotation = static_cast<float>(GetRandomValue(-150, 150));
    }
}

void NpcShip::avoidPlayer() {
    const Player& player = World::player;
    float playerRotation = player.Rotation;
    // FIXME: this sucks
    Rotation = -playerRotation;
}

void NpcShip::findPlayer() {
    const Player& player = World::player;
    float angle = Vector2LineAngle(player.Position, Position) * RAD2DEG;
    std::cout << angle << "\n";
    Rotation = angle;
}

void NpcShip::updateState() {
    switch (_state) {
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

void NpcShip::Update() {
    updateState();
    Spaceship::Update();
}