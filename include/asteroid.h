#pragma once
#include "entity.h"

class Asteroid : public Entity {
private:
	int _level{};

public:
	static constexpr int MaxLevel = 3;
	float RotationSpeed = static_cast<float>(GetRandomValue(-50, 50));
	
	Asteroid(int level, std::size_t id);
	static int GetRandomLevel() {
		return GetRandomValue(0, MaxLevel);
	}
	void Split();
	void Update() override;
	void Draw() const override;
};