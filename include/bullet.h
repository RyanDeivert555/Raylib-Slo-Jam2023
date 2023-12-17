#pragma once
#include "entity.h"

class Bullet : public Entity {
public:
    bool FromPlayer{};

    Bullet(Vector2 position, Vector2 direction, float speed, bool fromPlayer, std::size_t id);
    void Update() override;
    void Draw() const override;
};