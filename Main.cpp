// Including all necessary files

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
#include "Headers/Score.h"

int main() {
	// Setting the seed for the random generators
	srand(int(time(0)));

	// Setup game classes
	GameState state;
	int currentScreen = screenMainMenu;

	// If initialisation of the gamestate fails:
	if (!state.initGameState()) {
		std::cerr << "Error when initializing\n" << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Main Loop
	while (currentScreen >= 0) {
		currentScreen = state.Screens[currentScreen]->Run(state.Window);
	}
	return 0;
}