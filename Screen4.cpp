#include "Headers/screen4.h"
#include "Headers/Constants.h"
#include "Headers/Score.h"
#include <iostream>

//Score Screen

bool screen4::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
		|| !backgroundTexture.loadFromFile("Resources/backgroundHelp.png")
		|| !buttonBackToMenu.loadTexture("Resources/buttonReturn.png")) {
		return false;
	}
	//Initialising Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);

	//Initialising Text Values
	screenTitle = sf::Text("Game Over", font, 80);
	finalScoreText = sf::Text("Final Score:  " + std::to_string(Score::finalScore), font, 60);
	livesLeftText = sf::Text("Lives Left:   " + std::to_string(Score::livesRemaining)", font, 60);
	newHighScoreText = sf::Text("New High\n Score!", font, 80);
	
	// If the high score was beaten, display beaten high score text. If not, then hide the text.
	if (Score::didBeatHighScore) {
		newHighScoreText.setColor(sf::Color::Black);
	}
	else {
		newHighScoreText.setColor(sf::Color::Transparent);
	}
	
	//Positioning Text
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	screenTitle.setPosition(WINDOW_X / 2, 80);
	screenTitle.setColor(sf::Color::Black);

	buttonBackToMenu.InitSprite();
	textRect = buttonBackToMenu.sprite.getLocalBounds();
	buttonBackToMenu.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonBackToMenu.sprite.setPosition(WINDOW_X - 150, WINDOW_Y - 100);

	textRect = newHighScoreText.getLocalBounds();
	newHighScoreText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);

	finalScoreText.setPosition(WINDOW_X / 32.0f, 14 * WINDOW_Y / 32.0f);
	livesLeftText.setPosition(WINDOW_X / 32.0f, 17 * WINDOW_Y / 32.0f);
	newHighScoreText.setPosition(sf::Vector2f(3 * WINDOW_X / 4.0f, 9 * WINDOW_Y / 16.0f));

	finalScoreText.setColor(sf::Color::Black);
	livesLeftText.setColor(sf::Color::Black);
	return true;
}

int screen4::Events(sf::RenderWindow & window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		// If the escape button pressed...
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenQuitGame;
		}
		// If the mouse button pressed...
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				if (buttonBackToMenu.sprite.getGlobalBounds().contains(mousePos)) {
					buttonClickSound.play();
					return screenMainMenu;
				}
			}
		}
		//If the mouse is moved...
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			buttonHighlightDetect(mousePos, buttonBackToMenu.sprite);
		}
	}
	return getCurrentScreen();
}

void screen4::Draw(sf::RenderWindow & window) {
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonBackToMenu.sprite);

	window.draw(finalScoreText);
	window.draw(livesLeftText);
	window.draw(newHighScoreText);
	window.display();
}

void screen4::Update() {
	// No Updates Needed
}

int screen4::Run(sf::RenderWindow &window) {
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
