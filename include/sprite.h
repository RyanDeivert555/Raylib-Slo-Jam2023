#pragma once
#include "raylib.h"
#include <vector>

namespace Sprite {
    // all textures for storage
    extern std::vector<Texture2D> textures;
    // Texture types
    extern std::vector<std::size_t> shipTextures;
    extern std::vector<std::size_t> bulletTextures;
    extern std::vector<std::size_t> asteroidTextures;
    // ship ids
    extern std::size_t redShip1Id;
    extern std::size_t blueShip1Id;
    extern std::size_t greenShip1Id;
    extern std::size_t orangeShip1Id;
    extern std::size_t redShip2Id;
    extern std::size_t blueShip2Id;
    extern std::size_t greenShip2Id;
    extern std::size_t orangeShip2Id;
    extern std::size_t redShip3Id;
    extern std::size_t blueShip3Id;
    extern std::size_t greenShip3Id;
    extern std::size_t orangeShip3Id;
    // projectiles
    extern std::size_t blueProjectileId;
    // asteroids
    extern std::size_t asteroid1Id;
    extern std::size_t asteroid2Id;
    extern std::size_t asteroid3Id;
    extern std::size_t asteroid4Id;
    // scenery
    extern std::size_t backgroundId;

    std::size_t AddTexture(const char* filePath);
    void Init();
    std::size_t GetRandomTexture(const std::vector<size_t>& ids);
    const Texture2D& GetTexture(std::size_t id);
    Vector2 Size(std::size_t id);
    Vector2 Center(std::size_t id, Vector2 scale);
    void Draw(std::size_t id, Vector2 position, Vector2 scale, float rotation, Vector2 origin);
    void DrawBackground();
    void UnloadTextures();
}