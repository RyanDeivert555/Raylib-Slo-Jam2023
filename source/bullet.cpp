#include "../include/bullet.h"
#include "../include/sprite.h"

Bullet::Bullet(Vector2 position, Vector2 direction, float speed, bool fromPlayer, std::size_t id) {
    Position = position;
    Direction = direction;
    Speed = speed;
    FromPlayer = fromPlayer;
    TextureId = id;
    Scale = Vector2Scale(Scale, 0.5f);
}

void Bullet::Update() {
    Position = Vector2Add(Position, Vector2Scale(Direction, Speed * GetFrameTime()));
}

void Bullet::Draw() const {
    Sprite::Draw(TextureId, Position, Scale, Rotation, Sprite::Center(TextureId, Scale));
}