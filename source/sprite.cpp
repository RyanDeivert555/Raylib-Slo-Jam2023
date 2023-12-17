#include "../include/sprite.h"
#include "raylib.h"
#include "raymath.h"

namespace Sprite {
	std::vector<Texture2D> textures{};
	std::vector<std::size_t> shipTextures{};
	std::vector<std::size_t> bulletTextures{};
	std::vector<std::size_t> asteroidTextures{};
	std::size_t redShip1Id{};
	std::size_t blueShip1Id{};
	std::size_t greenShip1Id{};
	std::size_t orangeShip1Id{};
	std::size_t redShip2Id{};
	std::size_t blueShip2Id{};
	std::size_t greenShip2Id{};
	std::size_t orangeShip2Id{};
	std::size_t redShip3Id{};
	std::size_t blueShip3Id{};
	std::size_t greenShip3Id{};
	std::size_t orangeShip3Id{};
	std::size_t blueProjectileId{};
	std::size_t asteroid1Id{};
	std::size_t asteroid2Id{};
	std::size_t asteroid3Id{};
	std::size_t asteroid4Id{};
	std::size_t backgroundId{};

	std::size_t AddTexture(const char *fileName) {
		Texture2D texture = LoadTexture(fileName);
		textures.push_back(texture);
		return textures.size() - 1;
	}

	void Init() {
		// ships
		redShip1Id = AddTexture("../assets/redShip1.png");
		blueShip1Id = AddTexture("../assets/blueShip1.png");
		greenShip1Id = AddTexture("../assets/greenShip1.png");
		orangeShip1Id = AddTexture("../assets/orangeShip1.png");
		redShip2Id = AddTexture("../assets/redShip2.png");
		blueShip2Id = AddTexture("../assets/blueShip2.png");
		greenShip2Id = AddTexture("../assets/greenShip2.png");
		orangeShip2Id = AddTexture("../assets/orangeShip2.png");
		redShip3Id = AddTexture("../assets/redShip3.png");
		blueShip3Id = AddTexture("../assets/blueShip3.png");
		greenShip3Id = AddTexture("../assets/greenShip3.png");
		orangeShip3Id = AddTexture("../assets/orangeShip3.png");
		shipTextures.push_back(redShip1Id);
		shipTextures.push_back(blueShip1Id);
		shipTextures.push_back(greenShip1Id);
		shipTextures.push_back(orangeShip1Id);
		shipTextures.push_back(redShip2Id);
		shipTextures.push_back(blueShip2Id);
		shipTextures.push_back(greenShip2Id);
		shipTextures.push_back(orangeShip2Id);
		shipTextures.push_back(redShip3Id);
		shipTextures.push_back(blueShip3Id);
		shipTextures.push_back(greenShip3Id);
		shipTextures.push_back(orangeShip3Id);
		// projectiles
		blueProjectileId = AddTexture("../assets/blueProjectile.png");
		bulletTextures.push_back(blueProjectileId);
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

	void Draw(std::size_t id, Vector2 position, Vector2 scale, float rotation, Vector2 origin) {
		Texture2D texture = GetTexture(id);
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

		DrawTexturePro(texture, sourceRect, destRect, origin, rotation, WHITE);
	}

	void UnloadTextures() {
		for (const auto& texture : textures) {
			UnloadTexture(texture);
		}
	}
}
