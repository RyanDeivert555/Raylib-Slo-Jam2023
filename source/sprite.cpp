#include "../include/sprite.h"
#include "raymath.h"
#include <vector>

namespace Sprite {
	std::vector<Texture2D> textures{};
	std::vector<std::size_t> shipTextures{};
	std::vector<std::size_t> bulletTextures{};
	std::vector<std::size_t> asteroidTextures{};
	std::size_t redShipId{};
	std::size_t blueProjectileId{};
	std::size_t asteroid1Id{};
	std::size_t asteroid2Id{};
	std::size_t asteroid3Id{};
	std::size_t asteroid4Id{};

	std::size_t AddTexture(const char *fileName) {
		Texture2D texture = LoadTexture(fileName);
		textures.push_back(texture);
		return textures.size() - 1;
	}

	void Init() {
		redShipId = AddTexture("../assets/redShip.png");
		shipTextures.push_back(redShipId);
		blueProjectileId = AddTexture("../assets/blueProjectile.png");
		bulletTextures.push_back(blueProjectileId);
		asteroid1Id = AddTexture("../assets/asteroid1.png");
		asteroid2Id = AddTexture("../assets/asteroid2.png");
		asteroid3Id = AddTexture("../assets/asteroid3.png");
		asteroid4Id = AddTexture("../assets/asteroid4.png");
		asteroidTextures.push_back(asteroid1Id);
		asteroidTextures.push_back(asteroid2Id);
		asteroidTextures.push_back(asteroid3Id);
		asteroidTextures.push_back(asteroid4Id);
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
