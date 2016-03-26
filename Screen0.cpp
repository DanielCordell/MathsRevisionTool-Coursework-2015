#include "Headers/Screen0.h"
#include "Headers/Constants.h"
#include "Headers/Settings.h"

#include <iostream>
// Main Menu Screen

bool screen0::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
		|| !backgroundTexture.loadFromFile("Resources/backgroundMenu.png")
		|| !buttonStart.loadTexture("Resources/buttonStart.png")
		|| !buttonHelp.loadTexture("Resources/buttonHelp.png")
		|| !buttonSettings.loadTexture("Resources/buttonSettings.png")
		|| !buttonQuit.loadTexture("Resources/buttonQuit.png")
		|| !buttonClickSoundBuffer.loadFromFile("Resources/buttonClick.wav")
		|| !music.openFromFile("Resources/backgroundMusic.wav")) {
		return false;
	}

	//Initialize Audio
	buttonClickSound.setBuffer(buttonClickSoundBuffer);
	buttonClickSound.setVolume(Settings::volumePercent);
	music.setVolume(Settings::volumePercent);
	music.setLoop(true);
	music.play();

	//Initialize Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);

	//Initializing Text Values
	screenTitle = sf::Text("Number Wizard", font, 100);
	name = sf::Text("Created by Daniel Cordell", font, 40);
	buttonStart.sprite.setTexture(buttonStart.texture);
	buttonHelp.sprite.setTexture(buttonHelp.texture);
	buttonQuit.sprite.setTexture(buttonQuit.texture);
	buttonSettings.sprite.setTexture(buttonSettings.texture);

	//Positioning Text
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setOrigin(textRect.width / 2, textRect.height / 2);
	screenTitle.setPosition(WINDOW_X / 2.0f, WINDOW_Y / 8.0f);
	screenTitle.setColor(sf::Color::Black);

	textRect = name.getLocalBounds();
	name.setOrigin(textRect.width, textRect.height);
	name.setPosition(WINDOW_X - 4, WINDOW_Y - 14);
	name.setColor(sf::Color::Black);

	//Positioning Buttons
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
	sf::Clock clock;
	while (true) {
		if (clock.getElapsedTime().asMilliseconds() >= 1000.0 / 60.0) /* Framerate Limit */ {
			clock.restart();
			int nextScreen = Events(window); // What is the next screen that should be loaded
			if (nextScreen != getCurrentScreen()) return nextScreen; // Return the next screen to main
			Update();
			Draw(window);
		}
	}
}

// Event Handling
int screen0::Events(sf::RenderWindow &window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenQuitGame;
		}
		// If mouse button pressed
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				bool buttonClicked = true;
				screen returnValue;
				if (buttonStart.sprite.getGlobalBounds().contains(mousePos)) returnValue = screenGame; // If start button clicked
				else if (buttonHelp.sprite.getGlobalBounds().contains(mousePos)) returnValue = screenHelp; // If help button clicked
				else if (buttonSettings.sprite.getGlobalBounds().contains(mousePos)) returnValue = screenOptions; // If options button clicked
				else if (buttonQuit.sprite.getGlobalBounds().contains(mousePos)) returnValue = screenQuitGame; // If quit button clicked
				else buttonClicked = false;
				if (buttonClicked) {
					buttonClickSound.play();
					return returnValue;
				}
			}
		}
		//If mouse is moved
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			buttonHighlightDetect(mousePos, buttonStart.sprite);
			buttonHighlightDetect(mousePos, buttonHelp.sprite);
			buttonHighlightDetect(mousePos, buttonSettings.sprite);
			buttonHighlightDetect(mousePos, buttonQuit.sprite);
		}
	}
	return getCurrentScreen();
}

void screen0::Draw(sf::RenderWindow &window) {
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonStart.sprite);
	window.draw(buttonHelp.sprite);
	window.draw(buttonSettings.sprite);
	window.draw(buttonQuit.sprite);
	window.draw(name);
	window.display();
}

void screen0::Update() {
	buttonClickSound.setVolume(Settings::volumePercent);
}