#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

// Base class for all screen classes
class cScreen {
private:
	// Stores the ID of the current screen
	int currentScreen;
protected:
	// The sprite and texture of the background
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;

	// The game sounds and background music
	// These are static variables, so every window has the same music and sounds
	static sf::Sound buttonClickSound;
	static sf::SoundBuffer buttonClickSoundBuffer;
	static sf::Music music;

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

	// Detects if a mouse is hovering over a button and changes the colour of the button if it is
	void buttonHighlightDetect(sf::Vector2i &mousePos, sf::Sprite &button);
	void buttonHighlightDetect(sf::Vector2i &mousePos, sf::RectangleShape &button);

	// Sets the ID of the current screen
	inline void setCurrentScreen(const int _currentScreen) { currentScreen = _currentScreen; }

	// Gets the ID of the current screen
	inline const int& getCurrentScreen() { return currentScreen; }
};

// Enumeration corresponding to different screen types
enum screen {
	screenQuitGame = -1,
	screenMainMenu,
	screenOptions,
	screenGame,
	screenHelp,
	screenScore,
	screenRetry
};