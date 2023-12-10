#include "../include/entity.h"
#include "../include/sprite.h"
#include "raylib.h"

Rectangle Entity::GetRect() const {
	Vector2 size = Sprite::Size(TextureId);
	Rectangle rect = Rectangle{
		Position.x,
		Position.y,
		size.x * Scale.x,
		size.y * Scale.y
	};
	return rect;
}

bool Entity::Collide(const Entity& other) const {
	return Alive 
		&& other.Alive 
		&& CheckCollisionRecs(GetRect(), other.GetRect());
}

void Entity::Kill() {
	Alive = false;
}