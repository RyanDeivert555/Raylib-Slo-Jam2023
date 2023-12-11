#include "../include/spaceship.h"
#include "../include/sprite.h"
#include "raylib.h"
#include "raymath.h"
//debug
#include <iostream>

Spaceship::Spaceship(std::size_t id) {
	Position = Vector2Zero();
	Velocity = Vector2Zero();
	RotationalVelocity = 0.0f;
	Rotation = 0.0f;
	Scale = Vector2One();
	Alive = true;
	TextureId = id;
	Health = DefaultHealth;
	Shield = DefaultShield;
	AttackCooldown = DefaultCooldown;
	CurrentAttackCooldown = AttackCooldown;
}

void Spaceship::TakeDamage(float damage) {
	Shield -= damage;
	if (Shield <= 0) {
		Health -= damage;
	}
	if (Health <= 0) {
		Kill();
	}
}

void Spaceship::Update() {
	if (Rotation >= 360.0f) {
		Rotation -= 360.0f;
	}
	if (Rotation < 0.0f) {
		Rotation += 360.0f;
	}

	float cosAngle = cos(Rotation * DEG2RAD) * RotationalVelocity * GetFrameTime();
	float sinAngle = sin(Rotation * DEG2RAD) * RotationalVelocity * GetFrameTime();

	Velocity.x = cosAngle;
	Velocity.y = sinAngle;

	Position = Vector2Add(Position, Velocity);
}

void Spaceship::Draw() const {
	// hack to make sure ship is the correct rotation
	Sprite::Draw(TextureId, Position, Scale, Rotation + 90.0f, Sprite::Center(TextureId));
}