#include "Headers/Screen3.h"
#include "Headers/Constants.h"
#include <iostream>
#include <sstream>

//Help Screen

bool screen3::Init() {
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
	screenTitle = sf::Text("Welcome to Number Wizard", font, 50);
	helpText = sf::Text("", font, 40);
	
	// Adding the help text to a string buffer.
	std::stringstream buffer;
	buffer << "This game will have you answering as many maths\n";
	buffer << "questions as possible in five minutes. See if\n";
	buffer << "you can beat your high score!\n\n";
	buffer << "You will need a pen and some paper to be\n";
	buffer << "able to asnwer some of the questions.\n";
	buffer << "All questions are randomly generated.\n\n";
	buffer << "Use the Enter key to submit your answers.\n";
	
	// Putting the text from the buffer into the helpText class.
	helpText.setString(buffer.str());

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

	textRect = helpText.getLocalBounds();
	helpText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	helpText.setPosition(9 * WINDOW_X / 16.0f, WINDOW_Y / 2.0f);
	helpText.setColor(sf::Color::Black);
	return true;
}

int screen3::Events(sf::RenderWindow & window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		// If the escape button pressed..
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenMainMenu;
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

void screen3::Draw(sf::RenderWindow & window) {
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(helpText);
	window.draw(buttonBackToMenu.sprite);
	window.display();
}

void screen3::Update() {
	// No updates needes
}

int screen3::Run(sf::RenderWindow &window) {
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
