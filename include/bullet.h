#pragma once
#include "entity.h"

class Bullet : public Entity {
public:
    Bullet(Vector2 position, Vector2 direction, float speed, std::size_t id);
    void Update() override;
    void Draw() const override;
};