#pragma once
#include "entity.h"

class Spaceship : public Entity {
private:    
	float _health{};
	float _shield{};
	float _attackCooldown{};
	float _currentAttackCooldown{};

public:
	static constexpr float DefaultHealth = 100.0f;
	static constexpr float DefaultShield = 50.0f;
	static constexpr float DefaultCooldown = 0.4f;

	Spaceship(std::size_t id);
	Spaceship& SetHealth(float health);
	Spaceship& SetShield(float shield);
	Spaceship& SetAttackCooldown(float attackCooldown);
	Spaceship& AddHealth(float health);
	Spaceship& AddShield(float shield);
	Spaceship& AddAttackCooldown(float attackCooldown);
	void Update() override;
	void Draw() const override;
};