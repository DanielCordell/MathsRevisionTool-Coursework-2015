#include "Headers/Screen0.h"
#include "Headers/Constants.h"
#include "Headers/Settings.h"

#include <iostream>
// Main Menu Screen

bool screen0::Init() {
	// Loading fonts and textures for this screen
	// If loading any resource fails, then this function returns false. The program will know to close due to missing resources.
	if (!font.loadFromFile("Resources/font.ttf")
		|| !backgroundTexture.loadFromFile("Resources/backgroundMenu.png")
		|| !buttonStart.loadTexture("Resources/buttonStart.png")
		|| !buttonHelp.loadTexture("Resources/buttonHelp.png")
		|| !buttonSettings.loadTexture("Resources/buttonSettings.png")
		|| !buttonQuit.loadTexture("Resources/buttonQuit.png")
		// As well as music for cScreen (static variable so same everywhere)
		|| !buttonClickSoundBuffer.loadFromFile("Resources/buttonClick.wav")
		|| !music.openFromFile("Resources/backgroundMusic.wav")) {
		return false;
	}

	// Initialising Audio
	// This only happens once in the program, as all of these sounds are static so appear on each screen, and music is in a separate
	// thread to the actual game screen, so this will play regardless of what is occuring on-screen.
	buttonClickSound.setBuffer(buttonClickSoundBuffer);
	buttonClickSound.setVolume(Settings::volumePercent);
	music.setVolume(Settings::volumePercent);
	music.setLoop(true);
	music.play();

	// Initialising the Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);

	// Initializing Text Values
	screenTitle = sf::Text("Number Wizard", font, 100);
	name = sf::Text("Created by Daniel Cordell", font, 40);
	buttonStart.sprite.setTexture(buttonStart.texture);
	buttonHelp.sprite.setTexture(buttonHelp.texture);
	buttonQuit.sprite.setTexture(buttonQuit.texture);
	buttonSettings.sprite.setTexture(buttonSettings.texture);

	// Positioning Text
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setOrigin(textRect.width / 2, textRect.height / 2);
	screenTitle.setPosition(WINDOW_X / 2.0f, WINDOW_Y / 8.0f);
	screenTitle.setColor(sf::Color::Black);

	textRect = name.getLocalBounds();
	name.setOrigin(textRect.width, textRect.height);
	name.setPosition(WINDOW_X - 4, WINDOW_Y - 14);
	name.setColor(sf::Color::Black);

	// Positioning Buttons
	textRect = buttonStart.sprite.getLocalBounds();
	buttonStart.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonStart.sprite.setPosition(WINDOW_X / 8, 5 * WINDOW_Y / 8);

	textRect = buttonHelp.sprite.getLocalBounds();
	buttonHelp.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonHelp.sprite.setPosition(3 * WINDOW_X / 8, 5 * WINDOW_Y / 8);

	textRect = buttonSettings.sprite.getLocalBounds();
	buttonSettings.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonSettings.sprite.setPosition(5 * WINDOW_X / 8, 5 * WINDOW_Y / 8);

	textRect = buttonQuit.sprite.getLocalBounds();
	buttonQuit.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonQuit.sprite.setPosition(7 * WINDOW_X / 8, 5 * WINDOW_Y / 8);
	return true;
};

// Game loop for Main Menu Screen
int screen0::Run(sf::RenderWindow &window) {
	// Defines a clock that will limit the game update rate, so that it does not run as fast as the processor (which will slow
	// down the computer system over time).
	sf::Clock clock;
	// Loop runs forever until the return statement is met.
	while (true) {
		if (clock.getElapsedTime().asMilliseconds() >= 1000.0 / 60.0) /* Framerate Limit */ {
			clock.restart();
			// Events function defines the next screen that should be loaded
			int nextScreen = Events(window); 
			// Return the next screen to the main function if it is different to the current screen.
			if (nextScreen != getCurrentScreen()) return nextScreen; 
			Update();
			Draw(window);
		}
	}
}

// Event Handling
int screen0::Events(sf::RenderWindow &window) {
	// Defines a system event and all parameters
	sf::Event event;
	// While there are still system events, assign them to the instance of the Event class.
	while (window.pollEvent(event)) {
		// If the screen should quit, then return the ID for quitting the game to the main function.
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenQuitGame;
		}
		// If the mouse button is pressed....
		if (event.type == sf::Event::MouseButtonPressed) {
			// If the button that was pressed was the left mouse button...
			if (event.mouseButton.button == sf::Mouse::Left) {
				// Get the current position of the mouse.
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				// Assume a button has been clicked, and create a variable specifying the return value of this function
				bool buttonClicked = true;
				screen returnValue;
				// If start button clicked, then return the ID of the game screen.
				if (buttonStart.sprite.getGlobalBounds().contains(mousePos)) returnValue = screenGame;
				// If help button clicked, then return the ID of the help screen.
				else if (buttonHelp.sprite.getGlobalBounds().contains(mousePos)) returnValue = screenHelp; 
				// If settings button clicked, return the ID of the settings screen.
				else if (buttonSettings.sprite.getGlobalBounds().contains(mousePos)) returnValue = screenOptions;
				// If quit button clicked, return ID of quitting the game.
				else if (buttonQuit.sprite.getGlobalBounds().contains(mousePos)) returnValue = screenQuitGame;
				// A button has not been pressed.
				else buttonClicked = false;
				// If a button has been pressed, return the value of the ID the button was referring to, and play a sound.
				if (buttonClicked) {
					buttonClickSound.play();
					return returnValue;
				}
			}
		}
		//If the mouse is moved
		if (event.type == sf::Event::MouseMoved) {
			// Get the current mouse position, and run the buttonHighlightDetect function on all buttons on the screen.
			// If the buttons are being hovered over, they will get a slight tint.
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			buttonHighlightDetect(mousePos, buttonStart.sprite);
			buttonHighlightDetect(mousePos, buttonHelp.sprite);
			buttonHighlightDetect(mousePos, buttonSettings.sprite);
			buttonHighlightDetect(mousePos, buttonQuit.sprite);
		}
	}
	// If no return value has been specified, then return the value of the current screen.
	return getCurrentScreen();
}

// Draw all resources to the screen.
void screen0::Draw(sf::RenderWindow &window) {
	// Clear the screen.
	window.clear();
	// Draw all resources.
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonStart.sprite);
	window.draw(buttonHelp.sprite);
	window.draw(buttonSettings.sprite);
	window.draw(buttonQuit.sprite);
	window.draw(name);
	// Display all changes to the screen.
	window.display();
}

void screen0::Update() {
	// No game logic to update
}
