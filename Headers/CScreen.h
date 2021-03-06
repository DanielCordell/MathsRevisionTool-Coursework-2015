#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

// Base class for all screen classes. All screen classes are "inherited" from this class, meaning they all contain their own
// versions of these functions and variables, which can all contain different data. This avoids us having to repeat portions of
// the class definition multiple times in code.

class cScreen {

private:	// Members only the current class can detect.
	// Stores the integer ID of the current screen. This will be used to compare a screen that is about to open with the 
	// current screen to see if they are different.
	int currentScreen;
protected:	// Members only the current class and any inherited classses can detect. 
	// The sprite and texture of the background. The texture holds the image data, and the sprite is the transformable version
	// of a texture that can be drawn to the screen.
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;

	// The game sounds and background music.
	// buttonClickSoundBuffer is the buffer that stores the sound data.
	// buttonClickSound is the playable version of the sound buffer, which will be played when a button is pressed.
	// These are static variables. so every window has the same music and sounds. This saves us having to have multiple copies
	// of the exact same variable in different classes. They only need to be initialised once, so this is done in the screen0 class.
	static sf::Sound buttonClickSound;
	static sf::SoundBuffer buttonClickSoundBuffer;
	static sf::Music music;

public:		// Members that can be detected by any function or class.
	// The functions below are all virtual functions. This means they do not have any functionality assinged to them as of right now
	// as this will be given when I define the inherited classes. This allows for any necessary changes between the functionality
	// of inhereted classes, but means that all inherited classes will have functions with these names, which will perform similar
	// functions.
	
	// Game Loop for each screen. Returns an integer value to the MAIN function, which corresponds to a new screen that should display.
	// A value of -1 (screenQuitGame) signifies that the program should quit.
	virtual int Run(sf::RenderWindow &window) = 0;

	// Initialises the screen (loads resources and positions objects on screen). Returns false if there is an error, so it can be
	// detected. Only called once throughout the program.
	virtual bool Init() = 0;

	// Returns the value of the next screen that should be displayed to the Run function, which in turn returns that value to
	// the main function.
	virtual int Events(sf::RenderWindow &window) = 0;

	// Updates game logic, such as the position of elements, their colour, and the text for things such as on screen timers.
	virtual void Update() = 0;

	// Draws all of the game objects to the screen. Required or nothing would appear on the screen even if it is created in a class.
	virtual void Draw(sf::RenderWindow &window) = 0;

	// Detects if a mouse is hovering over a button based on the mouse position, and if it is, tints the button slightly grey.
	// If it isn't then the tint is removed.
	void buttonHighlightDetect(sf::Vector2i &mousePos, sf::Sprite &button);
	void buttonHighlightDetect(sf::Vector2i &mousePos, sf::RectangleShape &button);

	// Sets the ID of the variable currentScreen, to assign values to each of the multiple screens.
	inline void setCurrentScreen(const int _currentScreen) { currentScreen = _currentScreen; }

	// Gets the ID of the current screen, which is compared to the value of the next screen to be loaded. If they are the same then
	// nothing happens, but if they are different then the current screen is closed and a new screen is open.
	inline const int& getCurrentScreen() { return currentScreen; }
};

// Enumeration corresponding to different screen types. These are used to uniquelly refer to each screen in code. Each enumeration
// has a numeric value assigned to it (screenQuitGame = -1, so screenMainMenu = 0, screenOptions = 1 and so on). 
enum screen {
	screenQuitGame = -1,
	screenMainMenu,
	screenOptions,
	screenGame,
	screenHelp,
	screenScore,
	screenRetry
};
