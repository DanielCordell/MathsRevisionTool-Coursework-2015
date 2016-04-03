#pragma once
#include "CScreen.h"

// Class Declaration for Screen that displays the Help Menu
class screen3: public cScreen {
private:
	// The on screen text representing the screen title.
	sf::Text screenTitle;
	// The class representing the button to take the user back to the main menu.
	Button buttonBackToMenu;
	// The on screen help text. This will contain the entire help text.
	sf::Text helpText;
	// The font for the current screen.
	sf::Font font;

public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();

	~screen3();
};
