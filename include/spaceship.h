#pragma once
#include "entity.h"

class Spaceship : public Entity {
private:
    bool _canShoot = true;
    float _attackCooldown = DefaultCooldown;
    float _currentAttackCooldown = _attackCooldown;
    bool _vulnerable = true;
    float _invulerabilityCooldown = DefaultInvulnerabilityCooldown;
    float _currentInvulerabilityCooldown = _invulerabilityCooldown;
    
public:
    static constexpr float DefaultShield = 100.0f;
    static constexpr float DefaultCooldown = 0.2f;
    static constexpr float DefaultInvulnerabilityCooldown = 1.0f;
    float MaxShield = DefaultShield;
    float Shield = MaxShield;
    bool IsPlayer = false;

    Spaceship(std::size_t id);
    void TakeDamage(float damage);
    void Shoot();
    void Update() override;
    void Draw() const override;
};
