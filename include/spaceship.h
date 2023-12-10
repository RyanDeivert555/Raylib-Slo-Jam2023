#pragma once
#include "entity.h"

class Spaceship : public Entity {
public:
	float Health{};
	float Shield{};
	float AttackCooldown{};
	float CurrentAttackCooldown{};
	static constexpr float DefaultHealth = 100.0f;
	static constexpr float DefaultShield = 50.0f;
	static constexpr float DefaultCooldown = 0.4f;

	Spaceship(std::size_t id);
	void Update() override;
	void Draw() const override;
};