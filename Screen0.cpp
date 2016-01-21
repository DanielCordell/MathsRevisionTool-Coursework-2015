#include "Headers/Screen0.h"
#include "Headers/Constants.h"

#include <iostream>
// Main Menu Screen

bool screen0::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
	||  !backgroundTexture.loadFromFile("Resources/backgroundMenu.png")){
		return false;
	}

	//Initialize Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);

	//Initializing Text Values
	screenTitle = sf::Text("Maths Game", font, 100);
	buttonStart = sf::Text("Start", font, 80);
	buttonHelp = sf::Text("Help", font, 80);
	buttonOptions = sf::Text("Options", font, 80);
	buttonQuit = sf::Text("Quit", font, 80);
	
	//Positioning Text
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	screenTitle.setPosition(WINDOW_X/2, 80);
	screenTitle.setColor(sf::Color::White);

	textRect = buttonStart.getLocalBounds();
	buttonStart.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonStart.setPosition(WINDOW_X / 8, WINDOW_Y / 2);
	buttonStart.setColor(sf::Color::White);

	textRect = buttonHelp.getLocalBounds();
	buttonHelp.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonHelp.setPosition(WINDOW_X - WINDOW_X/8, WINDOW_Y / 2);
	buttonHelp.setColor(sf::Color::White);

	textRect = buttonOptions.getLocalBounds();
	buttonOptions.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonOptions.setPosition(WINDOW_X / 8, 5 * WINDOW_Y / 6);
	buttonOptions.setColor(sf::Color::White);

	textRect = buttonQuit.getLocalBounds();
	buttonQuit.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonQuit.setPosition(WINDOW_X - WINDOW_X / 8, 5 * WINDOW_Y / 6);
	buttonQuit.setColor(sf::Color::White);
	return true;
};

// Game loop for Main Menu Screen
int screen0::Run(sf::RenderWindow &window) {
	sf::Clock clock;
	bool doQuit = false;

	while (true) {
		if (clock.getElapsedTime().asMilliseconds() >= 1000.0/60.0) /* Framerate Limit */ {
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
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				if (buttonStart.getGlobalBounds().contains(mousePos)) return screenGame; // If start button clicked
				if (buttonHelp.getGlobalBounds().contains(mousePos)) return screenHelp; // If help button clicked
				if (buttonOptions.getGlobalBounds().contains(mousePos)) return screenOptions; // If options button clicked
				if (buttonQuit.getGlobalBounds().contains(mousePos)) return screenQuitGame; // If quit button clicked
			}
		}
	}
	return getCurrentScreen();
}

 
void screen0::Draw(sf::RenderWindow &window){
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonStart);
	window.draw(buttonHelp);
	window.draw(buttonOptions);
	window.draw(buttonQuit);
	window.display();
}

void screen0::Update(){
}
