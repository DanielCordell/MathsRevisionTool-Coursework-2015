#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <vector>
#include <Windows.h>

#include "SFML/Graphics.hpp"
#include "Headers/Rand.h"
#include "Headers/QuestionGen.h"
#include "Headers/Settings.h"
#include "Headers/GameState.h"
#include "Headers/Constants.h"
#include "Headers/Screen0.h"
#include "Headers/Screen1.h"
#include "Headers/Screen2.h"
#include "Headers/Screen3.h"


//TODO Comments

int main() {

	// Set the seed for the random generators
	srand(int(time(0)));
	
	// Setup game classes
	GameState state;
	int currentScreen = screenMainMenu;

	// Creates settings file if it doesn't exist and loads the settings from file
	state.settings.initSettings();

	// Setup new screens
	state.Screens.push_back(new screen0); // Adding Main Menu
	state.Screens.push_back(new screen1); // Adding Options Menu
	state.Screens.push_back(new screen2); // Adding Game Screen
	state.Screens.push_back(new screen3); // Adding Help Screen

	// Init Screens
	for (unsigned int i = 0; i < state.Screens.size(); i++) {
		if (!state.Screens[i]->Init()) {
			std::cerr << "Error when initializing\n" << std::endl;
			system("pause"); // REMOVE AT END
			return EXIT_FAILURE;
		}
		state.Screens[i]->setCurrentScreen(i);
	}

	// Main Loop
	while (currentScreen >= 0) {
		currentScreen = state.Screens[currentScreen]->Run(state.Window);
	}
	return 0;
}