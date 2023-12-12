#pragma once
#include "entity.h"

class Spaceship : public Entity {
public:
	static constexpr float DefaultHealth = 100.0f;
	static constexpr float DefaultShield = 50.0f;
	static constexpr float DefaultCooldown = 0.2f;
	float Health = DefaultHealth;
	float Shield = DefaultShield;
	float AttackCooldown = DefaultCooldown;
	float CurrentAttackCooldown = AttackCooldown;

	Spaceship(std::size_t id);
	void TakeDamage(float damage);
	void Shoot();
	void Update() override;
	void Draw() const override;
};