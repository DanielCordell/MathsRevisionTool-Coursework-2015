#pragma once
#include "CScreen.h"

// Class Declaration for Screen that displays the Help Menu
class screen3 : public cScreen{
private:
	sf::Text screenTitle;
	sf::Text buttonBackToMenu;

	sf::Font font;

public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();

	~screen3();
};
