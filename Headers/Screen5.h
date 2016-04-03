#pragma once
#include "CScreen.h"
#include "Button.h"
#include "PauseableClock.h"

// Class Declaration for Screen that displays the Retry Options. This inherits from the cScreen class.
class screen5: public cScreen {
private:
	// Declaring Class Variables
	sf::Text screenTitle;
	sf::Font font;
	sf::Text answerText;

	Button buttonContinue;
	Button buttonRetry;
	sf::PauseableClock clock;
	// Boolean to detect if a new question needs to be generated or not.
	bool newQuestion;

public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();
};
