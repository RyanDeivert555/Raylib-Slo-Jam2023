#include "../include/player.h"
#include "../include/sprite.h"
// debug
#include <iostream>

Player::Player(std::size_t id) : Spaceship(id) {
    IsPlayer = true;
}

void Player::getInput() {
    if (IsKeyDown(KEY_D)) {
        Rotation += RotationSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A)) {
        Rotation -= RotationSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_W)) {
        Speed += Acceleration * GetFrameTime();
        Speed = Clamp(Speed, MinSpeed, MaxSpeed);
    }
    if (IsKeyDown(KEY_S)) {
        Speed -= Acceleration * GetFrameTime();
        Speed = Clamp(Speed, MinSpeed, MaxSpeed);
    }
    if (IsKeyDown(KEY_SPACE)) {
        Shoot();
    }
}

void Player::warnNoShields() {
    if (Shield <= 0.0f) {
        _warnNoShield = true;
    }
    if (_warnNoShield) {
        _warningTimer -= GetFrameTime();
        if (_warningTimer <= 0.0f) {
            _warnNoShield = false;
        }
    }
}

void Player::Reset() {
    Position = Vector2Zero();
    Alive = true;
    Shield = MaxShield;
    _warnNoShield = false;
}

void Player::Update() {
    getInput();
    warnNoShields();
    Spaceship::Update();
}

void Player::DrawShieldWarning() const {
    if (_warnNoShield) {
        Sprite::DrawTextCenter("WARNING: SHIELDS ARE OFFLINE!", Vector2{0.0f, 100.0f}, 50.0f, 10.0f, RED);
    }
}