#include "../include/player.h"
#include "../include/sprite.h"
#include "../include/sound.h"
#include "raylib.h"

Player::Player(std::size_t id) : Spaceship(id) {
    IsPlayer = true;
    Speed = 500.0f;
    RotationSpeed = 200.0f;
}

void Player::getInput() {
    if (IsKeyDown(KEY_D) || static_cast<int>(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X)) == 1) {
        Rotation += RotationSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A) || static_cast<int>(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X)) == -1) {
        Rotation -= RotationSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_W) || static_cast<int>(GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)) == -1) {
        Speed += Acceleration * GetFrameTime();
        Speed = Clamp(Speed, MinSpeed, MaxSpeed);
    }
    if (IsKeyDown(KEY_S) || static_cast<int>(GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)) == 1) {
        Speed -= Acceleration * GetFrameTime();
        Speed = Clamp(Speed, MinSpeed, MaxSpeed);
    }
    if (IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) {
        Shoot();
    }
}

void Player::warnNoShields() {
    // so that sound only plays once
    if (Shield <= 0.0f && !_warnNoShield && _warningTimer > 0.0f) {
        SFX::PlaySound(SFX::shieldBreakId);
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
    _warningTimer = _maxWarningTimer;
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
