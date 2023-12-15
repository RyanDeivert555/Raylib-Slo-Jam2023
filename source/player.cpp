#include "../include/player.h"
#include "raylib.h"
#include "raymath.h"
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

void Player::Update() {
    getInput();
    Spaceship::Update();
}