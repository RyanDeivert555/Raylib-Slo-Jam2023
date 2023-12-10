#include "../include/spaceship.h"
#include "../include/sprite.h"
#include "raylib.h"
#include "raymath.h"
//debug
#include <iostream>

Spaceship::Spaceship(std::size_t id) {
	_position = Vector2Zero();
	_velocity = Vector2Zero();
	_rotationalVelocity = 0.0f;
	_rotation = 0.0f;
	_scale = Vector2One();
	_alive = true;
	_textureId = id;
	_health = DefaultHealth;
	_shield = DefaultShield;
	_attackCooldown = DefaultCooldown;
	_currentAttackCooldown = _attackCooldown;
}

Spaceship& Spaceship::SetHealth(float health) {
	_health = health;
	return *this;
}

Spaceship& Spaceship::SetShield(float shield) {
	_shield = shield;
	return *this;
}

Spaceship& Spaceship::SetAttackCooldown(float attackCooldown) {
	_attackCooldown = attackCooldown;
	_currentAttackCooldown = _attackCooldown;
	return *this;
}

Spaceship& Spaceship::AddHealth(float health) {
	_health += health;
	return *this;
}

Spaceship& Spaceship::AddShield(float shield) {
	_shield += shield;
	return *this;
}

Spaceship& Spaceship::AddAttackCooldown(float attackCooldown) {
	_attackCooldown += attackCooldown;
	_currentAttackCooldown += _attackCooldown;
	return *this;
}

void Spaceship::Update() {
	if (_rotation >= 360.0f) {
		_rotation -= 360.0f;
	}
	if (_rotation < 0.0f) {
		_rotation += 360.0f;
	}

	float cosAngle = cos(_rotation * DEG2RAD) * _rotationalVelocity * GetFrameTime();
	float sinAngle = sin(_rotation * DEG2RAD) * _rotationalVelocity * GetFrameTime();

	_velocity.x = cosAngle;
	_velocity.y = sinAngle;

	_position = Vector2Add(_position, _velocity);
}

void Spaceship::Draw() const {
	// hack to make sure ship is the correct rotation
	Sprite::Draw(_textureId, _position, _scale, _rotation + 90.0f, Sprite::TextureCenter(_textureId));
}