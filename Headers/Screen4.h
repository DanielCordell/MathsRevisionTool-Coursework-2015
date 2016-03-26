#pragma once
#include "CScreen.h"

// Class Declaration for Screen that displays the Score
class screen4: public cScreen {
private:
	sf::Text screenTitle;
	Button buttonBackToMenu;

	sf::Text finalScoreText;
	sf::Text livesLeftText;
	sf::Text newHighScoreText;
	sf::Font font;

public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();
};
