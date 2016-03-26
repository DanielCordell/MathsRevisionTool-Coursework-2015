#pragma once
#include "CScreen.h"
#include "Button.h"

// Class Declaration for Screen that displays the Retry Options
class screen5: public cScreen {
private:
	sf::Text screenTitle;
	sf::Font font;

	Button buttonContinue;
	Button buttonRetry;

public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();
};
