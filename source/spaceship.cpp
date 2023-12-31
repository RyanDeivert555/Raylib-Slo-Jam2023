#include "../include/spaceship.h"
#include "../include/sprite.h"
#include "../include/world.h"
#include "../include/sound.h"

Spaceship::Spaceship(std::size_t id) {
    TextureId = id;
    Scale = Vector2{1.5f, 1.5f};
}

void Spaceship::TakeDamage(float damage) {
    if (!Vulnerable) {
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
    Vulnerable = false;
}

void Spaceship::Shoot() {
    if (CanShoot) {
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
        CanShoot = false;
    }
    else {
        CurrentAttackCooldown -= GetFrameTime();
        if (CurrentAttackCooldown <= 0.0f) {
            CurrentAttackCooldown = AttackCooldown;
            CanShoot = true;
        }
    }
}

void Spaceship::Update() {
    // vulnerability countdown
    if (!Vulnerable) {
        CurrentInvulerabilityCooldown -= GetFrameTime();
        if (CurrentInvulerabilityCooldown <= 0.0f) {
            CurrentInvulerabilityCooldown = InvulerabilityCooldown;
            Vulnerable = true;
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
        cosf(Rotation * DEG2RAD),
        sinf(Rotation * DEG2RAD)
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
