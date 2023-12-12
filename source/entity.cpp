#include "../include/entity.h"
#include "../include/sprite.h"
#include "raylib.h"

Rectangle Entity::GetRect() const {
	Vector2 size = Sprite::Size(TextureId);
	// get center rect
	Rectangle rect = Rectangle{
		Position.x - size.x / 2.0f,
		Position.y - size.y / 2.0f,
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
	ShouldDraw = false;
}