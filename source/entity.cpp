#include "../include/entity.h"
#include "../include/sprite.h"
#include "raylib.h"
#include "raymath.h"

Entity& Entity::SetPosition(Vector2 position) {
	_position = position;
	return *this;
}

Entity& Entity::SetVelocity(Vector2 velocity) {
	_velocity = velocity;
	return *this;
}

Entity& Entity::SetRotationalVelocity(float rotationalVelocity) {
	_rotationalVelocity = rotationalVelocity;
	return *this;
}

Entity& Entity::SetRotation(float rotation) {
	_rotation = rotation;
	return *this;
}

Entity& Entity::SetScale(Vector2 scale) {
	_scale = scale;
	return *this;
}

Entity& Entity::AddPosition(Vector2 position) {
	_position = Vector2Add(_position, position);
	return *this;
}

Entity& Entity::AddVelocity(Vector2 velocity) {
	_velocity = Vector2Add(_velocity, velocity);
	return *this;
}

Entity& Entity::AddRotationalVelocity(float rotationalVelocity) {
	_rotationalVelocity += rotationalVelocity;
	return *this;
}

Entity& Entity::AddRotation(float rotation) {
	_rotation += rotation;
	return *this;
}

Entity& Entity::AddScale(Vector2 scale) {
	_scale = Vector2Add(_scale, scale);
	return *this;
}

Rectangle Entity::GetRect() const {
	Vector2 size = Sprite::Size(_textureId);
	Rectangle rect = Rectangle{
		_position.x,
		_position.y,
		size.x * _scale.x,
		size.y * _scale.y
	};
	return rect;
}

bool Entity::Collide(const Entity& other) const {
	return _alive 
		&& other._alive 
		&& CheckCollisionRecs(GetRect(), other.GetRect());
}

void Entity::Kill() {
	_alive = false;
}