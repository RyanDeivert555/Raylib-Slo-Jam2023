#pragma once

constexpr int windowWidth = 1280;
constexpr int windowHeight = 720;

enum class GameState {
	Logo,
	Menu,
	Gameplay,
	Paused,
	GameOver,
};