#pragma once
#include <SFML/Graphics.hpp>

// Base class for all screen classes
class cScreen {
private:
	int currentScreen;
protected:
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
public:

	// Game Loop for each screen. Returns an integer value which corresponds to a new screen to display. A value of -1 quits the program.
	virtual int Run(sf::RenderWindow &window) = 0;

	// Returns false if init fails
	virtual bool Init() = 0;

	// Returns the value of the next screen that should be displayed
	virtual int Events(sf::RenderWindow &window) = 0;

	// Updates game logic
	virtual void Update() = 0;

	// Drawing the game to the screen
	virtual void Draw(sf::RenderWindow &window) = 0;

	inline void setCurrentScreen(const int _currentScreen) { currentScreen = _currentScreen; }
	inline const int& getCurrentScreen() { return currentScreen; }
};

// Enum corresponding to screen type

enum screen {
	screenQuitGame = -1,
	screenMainMenu,
	screenOptions,
	screenGame,
	screenHelp,
	screenIngameMenu
};