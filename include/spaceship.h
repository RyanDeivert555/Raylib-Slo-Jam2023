#pragma once
#include "entity.h"

class Spaceship : public Entity {
private:
	bool _canShoot = true;
	float _attackCooldown = DefaultCooldown;
	float _currentAttackCooldown = _attackCooldown;
	
public:
	static constexpr float DefaultHealth = 100.0f;
	static constexpr float DefaultShield = 50.0f;
	static constexpr float DefaultCooldown = 0.2f;
	static constexpr float DefaultRotationSpeed = 150.f;
	float Health = DefaultHealth;
	float Shield = DefaultShield;
	bool IsPlayer = false;
	float RotationSpeed = DefaultRotationSpeed;

	Spaceship(std::size_t id);
	void TakeDamage(float damage);
	void Shoot();
	void Update() override;
	void Draw() const override;
};
