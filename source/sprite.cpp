#include "../include/sprite.h"
#include "raylib.h"
#include "raymath.h"
// debug
#include <iostream>

namespace Sprite {
    std::vector<Texture2D> textures{};
    std::vector<std::size_t> shipTextures{};
    std::vector<std::size_t> bulletTextures{};
    std::vector<std::size_t> asteroidTextures{};
    std::size_t projectileId{};
    std::size_t asteroid1Id{};
    std::size_t asteroid2Id{};
    std::size_t asteroid3Id{};
    std::size_t asteroid4Id{};
    std::size_t backgroundId{};
    std::size_t shieldId{};
    Font font{};
    std::size_t ship0Id{};
    std::size_t ship1Id{};
    std::size_t ship2Id{};
    std::size_t ship3Id{};
    std::size_t ship4Id{};

    std::size_t AddTexture(const char *fileName) {
        Texture2D texture = LoadTexture(fileName);
        textures.push_back(texture);
        return textures.size() - 1;
    }

    void Init() {
        // projectiles
        projectileId = AddTexture("../assets/projectile.png");
        bulletTextures.push_back(projectileId);
        // asteroids
        asteroid1Id = AddTexture("../assets/asteroid1.png");
        asteroid2Id = AddTexture("../assets/asteroid2.png");
        asteroid3Id = AddTexture("../assets/asteroid3.png");
        asteroid4Id = AddTexture("../assets/asteroid4.png");
        asteroidTextures.push_back(asteroid1Id);
        asteroidTextures.push_back(asteroid2Id);
        asteroidTextures.push_back(asteroid3Id);
        asteroidTextures.push_back(asteroid4Id);
        // scenery
        backgroundId = AddTexture("../assets/background.png");
        shieldId = AddTexture("../assets/shield.png");
        font = LoadFontEx("../assets/font.ttf", 32, nullptr, 250);
        // test
        ship0Id = AddTexture("../assets/ship0.png");
        ship1Id = AddTexture("../assets/ship1.png");
        ship2Id = AddTexture("../assets/ship2.png");
        ship3Id = AddTexture("../assets/ship3.png");
        ship4Id = AddTexture("../assets/ship4.png");
        shipTextures.push_back(ship0Id);
        shipTextures.push_back(ship1Id);
        shipTextures.push_back(ship2Id);
        shipTextures.push_back(ship3Id);
        shipTextures.push_back(ship4Id);
    }

    std::size_t GetRandomTexture(const std::vector<size_t>& ids) {
        int index = GetRandomValue(0, ids.size() - 1);
        return ids[index];
    }

    const Texture2D& GetTexture(std::size_t id) {
        return textures.at(id);
    }

    Vector2 Size(std::size_t id) {
        const Texture2D& texture = GetTexture(id);
        float width = static_cast<float>(texture.width);
        float height = static_cast<float>(texture.height);
        Vector2 size = Vector2{width, height};

        return size;
    }

    Vector2 Center(std::size_t id, Vector2 scale) {
        Vector2 center = Size(id);
        center = Vector2Scale(center, 0.5f);
        center = Vector2Multiply(center, scale);

        return center;
    }

    void DrawBackground() {
        static const Vector2 windowScale{
            static_cast<float>(GetScreenWidth()),
            static_cast<float>(GetScreenHeight())
        };
        static const Vector2 backgroundScale = Size(backgroundId);
        static const Vector2 scale = Vector2Divide(windowScale, backgroundScale);

        Draw(backgroundId, Vector2Zero(), scale, 0.0f, Vector2Zero());
    }

    void DrawText(const char* text, Vector2 position, float fontSize, float fontSpacing, Color tint) {
        DrawTextEx(font, text, position, fontSize, fontSpacing, tint);
    }

    void DrawTextCenter(const char* text, Vector2 offset, float fontSize, float fontSpacing, Color tint) {
        float screenWidth = static_cast<float>(GetScreenWidth());
        float screenHeight = static_cast<float>(GetScreenHeight());
        Vector2 screenSize{screenWidth, screenHeight};
        Vector2 centerScreen = Vector2Scale(screenSize, 0.5f);
        Vector2 size = MeasureTextEx(font, text, fontSize, fontSpacing);
        Vector2 centerSize = Vector2Scale(size, 0.5f);
        Vector2 centerPosition = Vector2Subtract(centerScreen, centerSize);
        centerPosition = Vector2Add(centerPosition, offset); 
        Sprite::DrawText(text, centerPosition, fontSize, fontSpacing, tint);
    }

    void Draw(std::size_t id, Vector2 position, Vector2 scale, float rotation, Vector2 origin, Color tint) {
        const Texture2D& texture = GetTexture(id);
        float width = static_cast<float>(texture.width);
        float height = static_cast<float>(texture.height);

        Rectangle sourceRect = {
            0.0f,
            0.0f,
            width,
            height
        };

        Rectangle destRect = Rectangle{
            position.x,
            position.y,
            width * scale.x,
            height * scale.y
        };
        DrawTexturePro(texture, sourceRect, destRect, origin, rotation, tint);
    }

    void UnloadTextures() {
        for (const auto& texture : textures) {
            UnloadTexture(texture);
        }
        UnloadFont(font);
    }
}
