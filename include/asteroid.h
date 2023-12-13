#pragma once
#include "entity.h"

class Asteroid : public Entity {
private:
	int _level{};

public:
	static constexpr int MaxLevel = 3;
	float RotationSpeed{};
	
	Asteroid(int level, std::size_t id);
	void Split();
	void Update() override;
	void Draw() const override;
};