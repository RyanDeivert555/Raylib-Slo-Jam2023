#pragma once
#include <cstddef>
#include "raylib.h"

class Entity {
public:
	Vector2 Position{};
	Vector2 Velocity{};
	float RotationalVelocity{};
	float Rotation{};
	Vector2 Scale{};
	bool Alive{};
	std::size_t TextureId{};

	virtual ~Entity() = default;
	virtual Rectangle GetRect() const;
	virtual bool Collide(const Entity& other) const;
	void Kill();
	virtual void Update() {}
	virtual void Draw() const {}
};