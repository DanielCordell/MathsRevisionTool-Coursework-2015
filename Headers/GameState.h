#pragma once
#include "SFML/Graphics.hpp"
#include "CScreen.h"
#include "Settings.h"

class GameState {
public: // Public Members
	
	// GameState Constructor, runs when an instance of GameState is created.
	GameState();
	
	// This function initialises all game variables and functions. Returns false there is an error, true otherwise.
	bool initGameState();

	// The class that refers to the game window.
	sf::RenderWindow Window;

	// The class that refers to the user's settings. The members of this class are changed via the settings menu.
	Settings settings;

	// A list of all screens (technically a list of pointers to cScreen classes, and as all screen classes inherit from 
	// cScreen they can all be stored in this list).
	std::vector<cScreen*> Screens;
};
