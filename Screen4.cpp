#include "Headers/screen4.h"
#include "Headers/Constants.h"
#include "Headers/Score.h"
#include <iostream>

//Score Screen

bool screen4::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
		|| !backgroundTexture.loadFromFile("Resources/backgroundHelp.png")) {
		return false;
	}
	//Initialize Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);

	//Initializing Text Values
	screenTitle = sf::Text("Score", font, 80);
	buttonBackToMenu = sf::Text("Return", font, 60);
	timeTakenText = sf::Text("", font, 40);
	finalScoreText = sf::Text("", font, 40);
	livesLeftText = sf::Text("", font, 40);
	
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

	timeTakenText.setPosition(sf::Vector2f(WINDOW_X / 16.0f, 7 * WINDOW_Y / 16.0f));
	finalScoreText.setPosition(sf::Vector2f(WINDOW_X / 16.0f, 8 * WINDOW_Y / 16.0f));
	livesLeftText.setPosition(sf::Vector2f(WINDOW_X / 16.0f, 9 * WINDOW_Y / 16.0f));
	return true;
}

int screen4::Events(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event)) {
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenMainMenu;
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


void screen4::Draw(sf::RenderWindow & window)
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonBackToMenu);

	window.draw(timeTakenText);
	window.draw(finalScoreText);
	window.draw(livesLeftText);
	window.display();
}

void screen4::Update()
{

}

void screen4::updateValues()
{
	finalScoreText.setString("Final Score: " + std::to_string(Score::finalScore));
	livesLeftText.setString("Lives Left: " + std::to_string(Score::livesRemaining));
	timeTakenText.setString("Time Taken: " + std::to_string(int(Score::timeTaken.asSeconds())) + "." + std::to_string(int(Score::timeTaken.asSeconds() * 10) - int(Score::timeTaken.asSeconds())) + " Seconds");
}

int screen4::Run(sf::RenderWindow &window) {
	sf::Clock clock;
	updateValues();

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