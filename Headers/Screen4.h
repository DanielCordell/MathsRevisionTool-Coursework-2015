#pragma once
#include "CScreen.h"

// Class Declaration for Screen that displays the Score
class screen4: public cScreen {
private:
	// The on screen text representing the screen title.
	sf::Text screenTitle;
	// Class representing the button to return the user to the main menu.
	Button buttonBackToMenu;
	
	// Text values for the screen.
	sf::Text finalScoreText;
	sf::Text livesLeftText;
	sf::Text newHighScoreText;
	// The font for the current screen.
	sf::Font font;

public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();
};
