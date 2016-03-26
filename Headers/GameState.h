#pragma once
#include "SFML/Graphics.hpp"
#include "CScreen.h"
#include "Settings.h"

class GameState {
public:
	GameState();
	bool initGameState();

	// Game Window
	sf::RenderWindow Window;
	
	// Settings Class
	Settings settings;

	// List of screens
	std::vector<cScreen*> Screens;
};
