#include "Headers/GameState.h"
#include "Headers/Constants.h"
#include "Headers/Screen0.h"
#include "Headers/Screen1.h"
#include "Headers/Screen2.h"
#include "Headers/Screen3.h"
#include "Headers/Screen4.h"
#include "Headers/Screen5.h"
#include <iostream>

// GameState constructor
GameState::GameState() {
	Window.create(sf::VideoMode(WINDOW_X, WINDOW_Y), "Number Wizard", sf::Style::Close);
	Window.setKeyRepeatEnabled(false);
}

bool GameState::initGameState() {
	// Creates icon used in top left of window
	sf::Image icon;
	if (!icon.loadFromFile("Resources/gameIcon.png")) {
		return false;
	}
	Window.setIcon(128, 128, icon.getPixelsPtr());

	// Creates settings file if it doesn't exist and loads the settings from file
	settings.initSettings();

	// Setup of new screens
	Screens.push_back(new screen0); // Adding Main Menu
	Screens.push_back(new screen1); // Adding Options Menu
	Screens.push_back(new screen2); // Adding Game Screen
	Screens.push_back(new screen3); // Adding Help Screen
	Screens.push_back(new screen4); // Adding Score Screen
	Screens.push_back(new screen5); // Adding Retry Screen

	// Initialises all screens
	for (unsigned int i = 0; i < Screens.size(); i++) {
		if (!Screens[i]->Init()) {
			return false;
		}
		Screens[i]->setCurrentScreen(i);
	}
	return true;
}