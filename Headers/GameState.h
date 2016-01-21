#pragma once
#include "SFML/Graphics.hpp"
#include "CScreen.h"
#include "Settings.h"

class GameState {
public:
	GameState();

	// Game Objects
	sf::RenderWindow Window;
	Settings settings;
	std::vector<cScreen*> Screens;
};
