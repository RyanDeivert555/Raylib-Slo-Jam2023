#pragma once
#include "entity.h"

class Spaceship : public Entity {
protected:
    bool CanShoot = true;
    float AttackCooldown = DefaultCooldown;
    float CurrentAttackCooldown = AttackCooldown;
    bool Vulnerable = true;
    float InvulerabilityCooldown = DefaultInvulnerabilityCooldown;
    float CurrentInvulerabilityCooldown = InvulerabilityCooldown;
    
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
