#include "Headers/screen5.h"
#include "Headers/Constants.h"
#include "Headers/Score.h"
#include <iostream>

//Retry Screen

bool screen5::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
		|| !backgroundTexture.loadFromFile("Resources/backgroundHelp.png")
		|| !buttonRetry.loadTexture("Resources/buttonRetry.png")
		|| !buttonContinue.loadTexture("Resources/buttonContinue.png")) {
		return false;
	}
	//Initialize Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);

	//Initializing Text and Buttons
	screenTitle = sf::Text("Retry Question or Continue", font, 80);
	buttonContinue.InitSprite();
	buttonRetry.InitSprite();

	//Positioning Text and Buttons
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	screenTitle.setPosition(WINDOW_X / 2, 80);
	screenTitle.setColor(sf::Color::Black);

	textRect = buttonRetry.sprite.getLocalBounds();
	buttonRetry.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonRetry.sprite.setPosition(WINDOW_X / 3, WINDOW_Y / 2);

	textRect = buttonContinue.sprite.getLocalBounds();
	buttonContinue.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonContinue.sprite.setPosition(2 * WINDOW_X / 3, WINDOW_Y / 2);

	return true;
}

int screen5::Events(sf::RenderWindow & window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		// If escape button pressed
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenQuitGame;
		}
		// If mouse button pressed
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				{
					if (buttonContinue.sprite.getGlobalBounds().contains(mousePos)) {
						Score::newQuestionFromScreen5 = true;
						return screenGame;
					}
					if (buttonRetry.sprite.getGlobalBounds().contains(mousePos)) {
						return screenGame;
					}
				}
			}
		}
		//If mouse is moved
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			buttonHighlightDetect(mousePos, buttonContinue.sprite);
			buttonHighlightDetect(mousePos, buttonRetry.sprite);
		}
	}
	return getCurrentScreen();
}

void screen5::Draw(sf::RenderWindow & window) {
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonContinue.sprite);
	window.draw(buttonRetry.sprite);
	window.display();
}

void screen5::Update() {
	// No updating needed
}

int screen5::Run(sf::RenderWindow &window) {
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