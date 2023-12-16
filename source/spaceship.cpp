#include "../include/spaceship.h"
#include "../include/sprite.h"
#include "../include/world.h"
// debug
#include <iostream>

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
	if (_canShoot) {
		Vector2 direction = Vector2Normalize(
			Vector2{
				cosf(Rotation * DEG2RAD), 
				sinf(Rotation * DEG2RAD)
			}
		);
		float speed = Speed * 5.0f;
		World::SpawnBullet(Position, direction, speed, IsPlayer, Sprite::blueProjectileId);
		_canShoot = false;
	}
	else {
		_currentAttackCooldown -= GetFrameTime();
		if (_currentAttackCooldown <= 0.0f) {
			_currentAttackCooldown = _attackCooldown;
			_canShoot = true;
		}
	}
}

void Spaceship::Update() {
	// keep rotation between -180 and 180
	while (Rotation >= 180.0f) {
		Rotation -= 360.0f;
	}
	while (Rotation <= -180.0f) {
		Rotation += 360.0f;
	}

	Direction = Vector2Normalize(
		Vector2{
			cos(Rotation * DEG2RAD),
			sin(Rotation * DEG2RAD)
		}
	);

	Position = Vector2Add(Position, Vector2Scale(Direction, Speed * GetFrameTime()));
}

void Spaceship::Draw() const {
	// accounts for rotation of sprite
	Sprite::Draw(TextureId, Position, Scale, Rotation + 90.0f, Sprite::Center(TextureId, Scale));
}