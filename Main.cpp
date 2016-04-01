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

// This function is the first function that runs when the program begins. All functions will be called from here, and the program
// will close once this function ends.
int main() {
	// Setting the seed for the internal c++ random generator to the current system time. This means all random numbers
	// generated will be different every time.
	srand(int(time(0)));

	// Creates an instance of the gamestate class (this implicity calls the constructor).
	GameState state;
	// Creates a variable which refers to the current screen.
	int currentScreen = screenMainMenu;

	// If initialisation of the gameState class fails, print an error to the console and closes the program.
	if (!state.initGameState()) {
		std::cerr << "Error when initializing\n" << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Main Loop
	// While the currentScreen variable is greater than or equal to 0 (-1 refers to the program closing) then
	// call the the run function from the current screen is called.
	while (currentScreen >= 0) {
		currentScreen = state.Screens[currentScreen]->Run(state.Window);
	}
	// The program will only close when currentScreen = -1 (or lower, but this won't occur).
	return 0;
}
