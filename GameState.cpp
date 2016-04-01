#include "Headers/GameState.h"
#include "Headers/Constants.h"
#include "Headers/Screen0.h"
#include "Headers/Screen1.h"
#include "Headers/Screen2.h"
#include "Headers/Screen3.h"
#include "Headers/Screen4.h"
#include "Headers/Screen5.h"
#include <iostream>

// GameState Constructor, runs when an instance of GameState is created.
GameState::GameState() {
	// Creates the window where the game will be displayed. It's size in pixels is WINDOW_X and WINDOW_Y define in the constants
	// header, the title of the window is "Number Wizard", and sf:Style::Close, which gives the window a titlebar and an exit
	// button.
	Window.create(sf::VideoMode(WINDOW_X, WINDOW_Y), "Number Wizard", sf::Style::Close);
	// This means that all keypresses will be counted as only one press, even if the button is held down.
	Window.setKeyRepeatEnabled(false);
}

// This function initialises all game variables and functions. Returns false there is an error, true otherwise.
bool GameState::initGameState() {
	// Creates an image class which will store the game icon (shown in the top left of the screen, and in the taskbar).
	sf::Image icon;
	
	// Loads the icon from the icon file. If the icon does not exist, the initGameState function will return false, letting
	// the program know that there has been an error.
	if (!icon.loadFromFile("Resources/gameIcon.png")) {
		return false;
	}
	// Sets the icon of the window to the pixel data of the icon. The icon class can now be discarded.
	Window.setIcon(128, 128, icon.getPixelsPtr());

	// Creates settings file if it doesn't exist and loads the settings from file.
	settings.initSettings();

	// Setup of the list of screens.
	Screens.push_back(new screen0); // Adding Main Menu to the list
	Screens.push_back(new screen1); // Adding Options Menu to the list
	Screens.push_back(new screen2); // Adding Game Screen to the list
	Screens.push_back(new screen3); // Adding Help Screen to the list
	Screens.push_back(new screen4); // Adding Score Screen to the list 
	Screens.push_back(new screen5); // Adding Retry Screen to the list

	// Initialises all screens using a for loop. If any of the initialisation functions fails, the initGameState function returns
	// false.
	for (unsigned int i = 0; i < Screens.size(); i++) {
		if (!Screens[i]->Init()) {
			return false;
		}
		// Once the screen is initialised, the internal value of the screen is assigned using this function.
		Screens[i]->setCurrentScreen(i);
	}
	// Initialisation has been successful, return true so the program knows this.
	return true;
}
