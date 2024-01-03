#include "../include/npc_ship.h"
#include "../include/world.h"
#include "../include/sound.h"
#include "raylib.h"
// debug
#include <iostream>

NpcShip::NpcShip(std::size_t id) : Spaceship(id) {
    Position = GetSpawnPoint();
    Rotation = GetRandomValueF(-180.0f, 180.0f);
    Speed = GetRandomValueF(300.0f, 500.0f);
    RotationSpeed = GetRandomValueF(50.0f, 150.0f);
    MaxShield = GetRandomValueF(50.0f, 150.0f);
    Shield = MaxShield;
    // TODO: get random floats
    AttackCooldown = GetRandomValueF(0.2f, 0.5f);
    CurrentAttackCooldown = AttackCooldown;
    InvulerabilityCooldown = 0.5f;
    CurrentInvulerabilityCooldown = InvulerabilityCooldown;
}

void NpcShip::rotateToTarget() {
    // within 1 degrees
    if (std::abs(Rotation - _targetRotation) > 1.0f) {
        float rotationDelta = _targetRotation - Rotation;
        // ensure rotationDir is within -180 and 180 degrees
        rotationDelta = fmod(rotationDelta + 180.0f, 360.0f) - 180.0f;
        float rotationDir = (rotationDelta > 0.0f) ? 1.0f : -1.0f;
        Rotation += RotationSpeed * rotationDir * GetFrameTime();
    }
}

void NpcShip::passiveFlight() {
    _randomDirectionTimer -= GetFrameTime();
    rotateToTarget();
    if (_randomDirectionTimer <= 0.0f) {
        _randomDirectionTimer = GetRandomValueF(5.0f, 10.0f);
        _targetRotation = GetRandomValueF(-180.0f, 180.0f);
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
            if (std::abs(Rotation - _targetRotation) <= 1.0f && ShouldDraw) {
                Shoot();
            }
            break;
        }
    }
}

void NpcShip::ReactToDamage() {
    if (_state == State::Passive) {
        _state = GetRandomValue(0, 1) ? State::Flighty : State::Aggresive;
        if (_state == State::Flighty) {
            SFX::PlaySound(SFX::flightyAiId);
        }
        else {
            SFX::PlaySound(SFX::aggressiveAiId);
        }
    }
}

void NpcShip::Update() {
    updateState();
    Spaceship::Update();
}
