#pragma once
#include <cstddef>
#include "raylib.h"

class Entity {
protected:
	Vector2 _position{};
	Vector2 _velocity{};
	float _rotationalVelocity{};
	float _rotation{};
	Vector2 _scale{};
	bool _alive{};
	std::size_t _textureId{};

public:
	virtual ~Entity() = default;
	Entity& SetPosition(Vector2 position);
	Entity& SetVelocity(Vector2 velocity);
	Entity& SetRotationalVelocity(float rotationalVelocity);
	Entity& SetRotation(float rotation);
	Entity& SetScale(Vector2 scale);
	Entity& AddPosition(Vector2 position);
	Entity& AddVelocity(Vector2 velocity);
	Entity& AddRotationalVelocity(float rotationalVelocity);
	Entity& AddRotation(float rotation);
	Entity& AddScale(Vector2 scale);
	virtual Rectangle GetRect() const;
	virtual bool Collide(const Entity& other) const;
	void Kill();
	virtual void Update() {}
	virtual void Draw() const {}
};