#include "../include/npc_ship.h"
#include "../include/world.h"
// debug
#include <iostream>

NpcShip::NpcShip(std::size_t id) : Spaceship(id) {
    // TODO: randomize stats
}

void NpcShip::avoidPlayer() {
    const Player& player = World::player;
    float playerRotation = player.Rotation;
    // TODO: make this ai better...
    Rotation = -playerRotation;
}

void NpcShip::findPlayer() {
    const Player& player = World::player;
    float angle = Vector2LineAngle(player.Position, Position) * RAD2DEG;
    std::cout << angle << "\n";
    Rotation = angle;
}

void NpcShip::Update() {
    avoidPlayer();
    Spaceship::Update();
}