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
    // projectiles
    extern std::size_t projectileId;
    // asteroids
    extern std::size_t asteroid1Id;
    extern std::size_t asteroid2Id;
    extern std::size_t asteroid3Id;
    extern std::size_t asteroid4Id;
    // scenery
    extern std::size_t backgroundId;
    // shields
    extern std::size_t shieldId;
    // font
    extern Font font;
    // ships
    extern std::size_t ship0Id;
    extern std::size_t ship1Id;
    extern std::size_t ship2Id;
    extern std::size_t ship3Id;
    extern std::size_t ship4Id;

    std::size_t AddTexture(const char* filePath);
    void Init();
    std::size_t GetRandomTexture(const std::vector<size_t>& ids);
    const Texture2D& GetTexture(std::size_t id);
    Vector2 Size(std::size_t id);
    Vector2 Center(std::size_t id, Vector2 scale);
    void DrawText(const char* text, Vector2 position, float fontSize, float fontSpacing, Color tint=WHITE);
    void DrawTextCenter(const char* text, Vector2 offset, float fontSize, float fontSpacing, Color tint=WHITE);
    void Draw(std::size_t id, Vector2 position, Vector2 scale, float rotation, Vector2 origin, Color tint=WHITE);
    void DrawBackground();
    void UnloadTextures();
}