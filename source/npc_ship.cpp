#include "../include/npc_ship.h"
#include "../include/world.h"
#include "raylib.h"
#include "raymath.h"
// debug
#include <iostream>

NpcShip::NpcShip(std::size_t id) : Spaceship(id) {
	// TODO: randomize stats
}

void NpcShip::passiveFlight() {
	_randomDirectionTimer -= GetFrameTime();
	// within 1 degrees
	// FIXME: better checks for when to rotate
	if (std::abs(Rotation - _targetRotation) > 1.0f) {
		// TODO: make it rotate shortest path
		Rotation += RotationSpeed * GetFrameTime();
	}
	if (_randomDirectionTimer <= 0.0f) {
		_randomDirectionTimer = static_cast<float>(GetRandomValue(3, 6));
		_targetRotation = static_cast<float>(GetRandomValue(-150, 150));
	}
}

void NpcShip::avoidPlayer() {
	Speed = DefaultSpeed * 3.0f;
	const Player& player = World::player;
	Vector2 positionDifference = Vector2Subtract(Position, player.Position);
	float angle = std::atan2(positionDifference.y, positionDifference.x) * RAD2DEG;
	// TODO: make 
	Rotation = angle;
}

void NpcShip::findPlayer() {
	const Player& player = World::player;
	Vector2 positionDifference = Vector2Subtract(player.Position, Position);
	float angle = std::atan2(positionDifference.y, positionDifference.x) * RAD2DEG;
	Rotation = angle;
}

void NpcShip::updateState() {
	switch (_state) {
		case State::BrainDead:
		{
			break;
		}
		case State::Passive:
		{
			passiveFlight();
			break;
		}
		case State::Flighty:
		{
			avoidPlayer();
			break;
		}
		case State::Aggresive:
		{
			findPlayer();
			break;
		}
	}
}

void NpcShip::SetState(State newState) {
	_state = newState;
}

void NpcShip::Update() {
	updateState();
	Spaceship::Update();
}