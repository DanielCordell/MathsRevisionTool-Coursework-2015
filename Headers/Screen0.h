#pragma once
#include "CScreen.h"

// Class Declaration for Screen that displays the menu. This inherits from the cScreen class.
class screen0: public cScreen {
private:
	// The on screen text representing the screen title.
	sf::Text screenTitle;
	
	// Classes representing the numerous on screen buttons.
	Button buttonStart;
	Button buttonHelp;
	Button buttonSettings;
	Button buttonQuit;
	
	// The font used on the current screen.
	sf::Font font;
	// My name that will display on the screen.
	sf::Text name;
public:
	// The sub-gameloop, which controls this specific screen.
	int Run(sf::RenderWindow &window);
	// This function initialises the screen and positions variables. Returns false if there is an error, true otherwise.
	bool Init();
	// This function handles all screen events such as button presses and moving the mouse. Returns the ID value of the next screen
	// to be loaded.
	int Events(sf::RenderWindow &window);
	// This function draws all screen resources to the screen.
	void Draw(sf::RenderWindow &window);;
	// This function updates game logic.
	void Update();
};
