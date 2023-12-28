#include "../include/spaceship.h"
#include "../include/sprite.h"
#include "../include/world.h"
#include "../include/sound.h"
// debug
#include <iostream>

Spaceship::Spaceship(std::size_t id) {
    TextureId = id;
    Scale = Vector2{1.5f, 1.5f};
}

void Spaceship::TakeDamage(float damage) {
    if (!_vulnerable) {
        return;
    }
    SFX::PlaySound(SFX::hitId);
    if (Shield >= 0.0f) {
        Shield -= damage;
    }
    else {
        SFX::PlaySound(SFX::shipExplosionId);
        Kill();
    }
    _vulnerable = false;
}

void Spaceship::Shoot() {
    if (_canShoot) {
        SFX::PlaySound(SFX::projectileShootId);
        Vector2 direction = Vector2{
            cosf(Rotation * DEG2RAD), 
            sinf(Rotation * DEG2RAD)
        };
        float speed = Speed * 5.0f;
        if (IsPlayer) {
            World::SpawnPlayerBullet(Position, direction, speed, Sprite::projectileId);
        }
        else {
            World::SpawnBullet(Position, direction, speed, Sprite::projectileId);
        }
        _canShoot = false;
    }
    else {
        _currentAttackCooldown -= GetFrameTime();
        if (_currentAttackCooldown <= 0.0f) {
            _currentAttackCooldown = _attackCooldown;
            _canShoot = true;
        }
    }
}

void Spaceship::Update() {
    // vulnerability countdown
    if (!_vulnerable) {
        _currentInvulerabilityCooldown -= GetFrameTime();
        if (_currentInvulerabilityCooldown <= 0.0f) {
            _currentInvulerabilityCooldown = _invulerabilityCooldown;
            _vulnerable = true;
        }
    }
    // keep rotation between -180 and 180
    while (Rotation >= 180.0f) {
        Rotation -= 360.0f;
    }
    while (Rotation <= -180.0f) {
        Rotation += 360.0f;
    }

    Direction = Vector2{
        cos(Rotation * DEG2RAD),
        sin(Rotation * DEG2RAD)
    };

    Position = Vector2Add(Position, Vector2Scale(Direction, Speed * GetFrameTime()));
}

void Spaceship::Draw() const {
    Vector2 center = Sprite::Center(TextureId, Scale);
    // accounts for rotation of sprite
    Sprite::Draw(TextureId, Position, Scale, Rotation + 90.0f, center);
    // draw shield
    static const Vector2 shieldScale{2.0f, 2.0f};
    float shieldRange = Normalize(Shield / MaxShield, 0.0f, 1.0f);
    Vector2 shieldCenter = Sprite::Center(Sprite::shieldId, shieldScale);
    Sprite::Draw(Sprite::shieldId, Position, shieldScale, Rotation + 90.0f, shieldCenter, ColorAlpha(BLUE, shieldRange)); 
}
