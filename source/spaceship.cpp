#include "../include/spaceship.h"
#include "../include/sprite.h"
#include "../include/world.h"
#include "raymath.h"

Spaceship::Spaceship(std::size_t id) {
	TextureId = id;
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

void Spaceship::Shoot() {
	if (CurrentAttackCooldown >= 0.0f) {
		CurrentAttackCooldown -= GetFrameTime();
		return;
	}
	CurrentAttackCooldown = AttackCooldown;

	Vector2 direction = Vector2Normalize(
		Vector2{
			cosf(Rotation * DEG2RAD), 
			sinf(Rotation * DEG2RAD)
		}
	);
	// TODO: remove magic number
	float speed = 700.0f;
	World::SpawnBullet(Position, direction, speed, Sprite::blueProjectileId);
}

void Spaceship::Update() {
	if (Rotation >= 360.0f) {
		Rotation -= 360.0f;
	}
	if (Rotation < 0.0f) {
		Rotation += 360.0f;
	}

	float cosAngle = cos(Rotation * DEG2RAD);
	float sinAngle = sin(Rotation * DEG2RAD);

	Direction.x = cosAngle;
	Direction.y = sinAngle;

	Position = Vector2Add(Position, Vector2Scale(Direction, Speed * GetFrameTime()));
}

void Spaceship::Draw() const {
	// hack to make sure ship is the correct rotation
	Sprite::Draw(TextureId, Position, Scale, Rotation + 90.0f, Sprite::Center(TextureId, Scale));
}