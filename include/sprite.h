#pragma once
#include "raylib.h"
#include <vector>

namespace Sprite {
	// all textures for storage
	extern std::vector<Texture2D> textures;
	extern std::size_t playerShipId;
	extern std::size_t blueProjectileId;

	std::size_t AddTexture(const char* filePath);
	void Init();
	const Texture2D& GetTexture(std::size_t id);
	Vector2 Size(std::size_t id);
	Vector2 TextureCenter(std::size_t id);
	void Draw(std::size_t id, Vector2 position, Vector2 scale, float rotation, Vector2 centerOffset);
	void UnloadTextures();
}