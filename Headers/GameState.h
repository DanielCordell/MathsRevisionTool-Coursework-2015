#pragma once
#include "SFML/Graphics.hpp"
#include "CScreen.h"
#include "Settings.h"

class GameState {
public:
	GameState();
	bool initGameState();

	// Game Objects
	sf::RenderWindow Window;
	Settings settings;
	std::vector<cScreen*> Screens;
};
