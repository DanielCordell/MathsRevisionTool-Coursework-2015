#include "Headers/Screen3.h"
#include "Headers/Constants.h"
#include <iostream>

//Help Screen

bool screen3::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
		|| !backgroundTexture.loadFromFile("Resources/backgroundHelp.png")) {
		return false;
	}
	//Initialize Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);



	//Initializing Text Values
	screenTitle = sf::Text("Help Screen", font, 80);
	buttonBackToMenu = sf::Text("Done", font, 60);

	//Positioning Text
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	screenTitle.setPosition(WINDOW_X / 2, 80);
	screenTitle.setColor(sf::Color::White);

	textRect = buttonBackToMenu.getLocalBounds();
	buttonBackToMenu.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonBackToMenu.setPosition(150, WINDOW_Y - 100);
	buttonBackToMenu.setColor(sf::Color::White);

	return true;
}

int screen3::Events(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event)) {
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenQuitGame;
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				if (buttonBackToMenu.getGlobalBounds().contains(mousePos)) return 0;
			}
		}
	}
	return getCurrentScreen();
}


void screen3::Draw(sf::RenderWindow & window)
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonBackToMenu);
	window.display();
}

void screen3::Update()
{

}

int screen3::Run(sf::RenderWindow &window) {
	sf::Clock clock;
	bool doQuit = false;

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