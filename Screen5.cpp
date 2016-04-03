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
	screenTitle = sf::Text("Incorrect Answer, would you like to:", font, 60);
	answerText.setString("Correct answer was: " + Score::answer);
	buttonContinue.InitSprite();
	buttonRetry.InitSprite();

	//Positioning Text and Buttons
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	screenTitle.setPosition(WINDOW_X / 2, 80);
	screenTitle.setColor(sf::Color::Black);

	textRect = answerText.getLocalBounds();
	answerText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	answerText.setPosition(WINDOW_X / 2, 7 * WINDOW_Y / 8);
	answerText.setColor(sf::Color::Black);

	textRect = buttonRetry.sprite.getLocalBounds();
	buttonRetry.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonRetry.sprite.setPosition(WINDOW_X / 3, WINDOW_Y / 2);

	textRect = buttonContinue.sprite.getLocalBounds();
	buttonContinue.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonContinue.sprite.setPosition(2 * WINDOW_X / 3, WINDOW_Y / 2);
	
	// Start with the internal clock paused.
	clock.pause();
	return true;
}

int screen5::Events(sf::RenderWindow & window) {
	// If the time on the clock is greater than two seconds, 
	if (clock.getElapsedTime().asSeconds() > 2) {
		// Setting this value to true means that the game screen can detect a new question needs to be generated.
		Score::newQuestionFromScreen5 = true;
		// Restart and pause the clock ready for the next time.
		clock.restart();
		clock.pause();
		// Reset this value for next time.
		newQuestion = false;
		// Return back to the game screen.
		return screenGame;
	}
	sf::Event event;
	while (window.pollEvent(event)) {
		// If the escape button was pressed
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenQuitGame;
		}
		// If the mouse button was pressed
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				if (!newQuestion) { // Stops the button being pressed more than once.
					if (buttonContinue.sprite.getGlobalBounds().contains(mousePos)) {
						// A new questiton should be generated, the clock starts.
						newQuestion = true;
						clock.restart();
						buttonClickSound.play();
					}
					if (buttonRetry.sprite.getGlobalBounds().contains(mousePos)) {
						// Return back to the game screen to retry the question.
						buttonClickSound.play();
						return screenGame;
					}
				}
			}
		}
		//If the mouse was moved
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			buttonHighlightDetect(mousePos, buttonContinue.sprite);
			buttonHighlightDetect(mousePos, buttonRetry.sprite);
		}
	}
	return getCurrentScreen();
}

void screen5::Draw(sf::RenderWindow & window) {
	// Draws game objects to the screen.
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	if (newQuestion) window.draw(answerText);
	window.draw(buttonContinue.sprite);
	window.draw(buttonRetry.sprite);
	window.display();
}

void screen5::Update() {
	// No Updates Needed
}

int screen5::Run(sf::RenderWindow &window) {
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
