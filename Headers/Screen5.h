#pragma once
#include "CScreen.h"
#include "Button.h"
#include "PauseableClock.h"

// Class Declaration for Screen that displays the Retry Options
class screen5: public cScreen {
private:
	sf::Text screenTitle;
	sf::Font font;
	sf::Text answerText;

	Button buttonContinue;
	Button buttonRetry;
	sf::PauseableClock clock;
	bool newQuestion;

public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();
};
