#pragma once
#include "raylib.h"
#include <vector>

namespace Sprite {
	// all textures for storage
	extern std::vector<Texture2D> textures;
	extern std::vector<std::size_t> shipTextures;
	extern std::vector<std::size_t> bulletTextures;
	extern std::vector<std::size_t> asteroidTextures;
	extern std::size_t redShipId;
	extern std::size_t blueProjectileId;
	extern std::size_t asteroid1Id;
	extern std::size_t asteroid2Id;
	extern std::size_t asteroid3Id;
	extern std::size_t asteroid4Id;

	std::size_t AddTexture(const char* filePath);
	void Init();
	const Texture2D& GetTexture(std::size_t id);
	Vector2 Size(std::size_t id);
	Vector2 Center(std::size_t id, Vector2 scale);
	void Draw(std::size_t id, Vector2 position, Vector2 scale, float rotation, Vector2 origin);
	void UnloadTextures();
}