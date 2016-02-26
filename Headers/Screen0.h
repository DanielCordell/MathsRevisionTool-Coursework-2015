#pragma once
#include "CScreen.h"

// Class Declaration for Screen that displays the menu
class screen0 : public cScreen {
private:
	sf::Text screenTitle;

	Button buttonStart;
	Button buttonHelp;
	Button buttonSettings;
	Button buttonQuit;
	sf::Font font;

public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();

	~screen0();

};