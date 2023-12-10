#include "../include/sprite.h"
#include "raylib.h"
#include <vector>

namespace Sprite {
	std::vector<Texture2D> textures{};
	std::size_t playerShipId = 0;
	std::size_t blueProjectileId = 0;

	std::size_t AddTexture(const char *fileName) {
		Texture2D texture = LoadTexture(fileName);
		textures.push_back(texture);
		return textures.size() - 1;
	}

	void Init() {
		playerShipId = AddTexture("../assets/playerShip.png");
		blueProjectileId = AddTexture("../assets/blueProjectile.png");
	}

	const Texture2D& GetTexture(std::size_t id) {
		return textures.at(id);
	}

	Vector2 Size(std::size_t id) {
		Texture2D texture = GetTexture(id);
		float width = static_cast<float>(texture.width);
		float height = static_cast<float>(texture.height);
		Vector2 size = Vector2{width, height};

		return size;
	}

	Vector2 TextureCenter(std::size_t id) {
		Vector2 center = Size(id);
		center.x /= 2.0f;
		center.y /= 2.0f;

		return center;
	}

	void Draw(std::size_t id, Vector2 position, Vector2 scale, float rotation, Vector2 center) {
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

		DrawTexturePro(texture, sourceRect, destRect, center, rotation, WHITE);
	}

	void UnloadTextures() {
		for (const auto& texture : textures) {
			UnloadTexture(texture);
		}
	}
}
