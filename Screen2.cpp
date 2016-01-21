#include "Headers/Screen2.h"
#include "Headers/Constants.h"

//Game Screen

bool screen2::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
		|| !backgroundTexture.loadFromFile("Resources/backgroundGame.png")){
		return false;
	}	
		questionAnswered = false;
		questionCorrect = false;

	//Initialize Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);

	//Initializing Text Values
	screenTitle = sf::Text("", font, 80);
	buttonBackToMenu = sf::Text("Done", font, 60);
	userInputText = sf::Text("", font, 40);
	userInputValidText = sf::Text("", font, 20);
	questionAnswer = sf::Text("", font, 40);

	//Positioning Title and Buttons
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	screenTitle.setPosition(WINDOW_X / 2, 80);
	screenTitle.setColor(sf::Color::White);

	textRect = buttonBackToMenu.getLocalBounds();
	buttonBackToMenu.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonBackToMenu.setPosition(WINDOW_X / 12.0f, 15 * WINDOW_Y / 16.0f);
	buttonBackToMenu.setColor(sf::Color::White);

	//Initializing Answer Box
	userInputBox.setSize(sf::Vector2f(4 * WINDOW_X / 16.0f, WINDOW_Y / 16.0f));
	userInputBox.setOrigin(userInputBox.getLocalBounds().width / 2, userInputBox.getLocalBounds().height / 2);
	userInputBox.setPosition(sf::Vector2f(13 * WINDOW_X / 16.0f, buttonBackToMenu.getPosition().y));
	userInputBox.setFillColor(sf::Color::Black);
	userInputBox.setOutlineColor(sf::Color::Green);
	userInputBox.setOutlineThickness(2);
	userInputText.setOrigin(0, userInputText.getLocalBounds().height / 2.0f);
	userInputText.setPosition(userInputBox.getGlobalBounds().left*1.01f,userInputBox.getPosition().y - userInputBox.getLocalBounds().height / 2);
	userInputText.setColor(sf::Color::White);
	userInputValidText.setPosition(userInputBox.getGlobalBounds().left, userInputBox.getGlobalBounds().top - userInputBox.getLocalBounds().height);
	userInputValidText.setColor(sf::Color::Transparent);
	userInputCursorBlink.setSize(sf::Vector2f(WINDOW_X / 196.0f, 2 * userInputBox.getSize().y / 3.0f));
	userInputCursorBlink.setOrigin(0, userInputCursorBlink.getSize().y / 2.0f);
	userInputCursorBlink.setPosition(userInputText.getPosition().x, userInputText.getPosition().y);
	
	GenerateQuestion();
	return true;
}

int screen2::Events(sf::RenderWindow & window)
{
	// Polling window events
	sf::Event event;
	while (window.pollEvent(event)) {
		//If the game should quit
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenQuitGame;
		}
		// If the mouse button is pressed
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				if (buttonBackToMenu.getGlobalBounds().contains(mousePos)) return 0;
			}
		}
		// If text is entered
		if (event.type == sf::Event::TextEntered) {
			char textInput = event.text.unicode;
			bool validCharacter = false;

			// Detect if entered text is a number
			if ((textInput - '0') >= 0 && (textInput - '0') <= 9) {
					validCharacter = true;
				}

			// Detect if entered text is a valid symbol
			if (textInput == '.' || textInput == '/') validCharacter = true;
			if (validCharacter) {
				if (userInputText.getString().getSize() < 16) {
					userInputText.setString(userInputText.getString() + textInput);
					userInputValidText.setColor(sf::Color::Transparent);
				}
				else {
					userInputValidText.setString("16 characters only.");
					userInputValidText.setColor(sf::Color::White);
				}
			}
			else {
				userInputValidText.setString("Please enter a valid character:\n(0 - 9, '/' and '.')");
				userInputValidText.setColor(sf::Color::White);
			}
			
			// Detect if entered text is a backspace
			if (textInput == 8) {
				userInputText.setString(userInputText.getString().substring(0, userInputText.getString().getSize() - 1));
				userInputValidText.setColor(sf::Color::Transparent);
			}
		}
	}
	return getCurrentScreen();
}


void screen2::Draw(sf::RenderWindow & window)
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonBackToMenu);

	window.draw(userInputBox);
	window.draw(userInputText);
	window.draw(userInputValidText);
	window.draw(userInputCursorBlink);
	window.display();
}

void screen2::Update()
{
	sf::FloatRect inputTextRect = userInputText.getGlobalBounds();
	// Update the position of the blinking cursor
	if (userInputText.getString().getSize() == 0) {
		userInputCursorBlink.setPosition(inputTextRect.left + inputTextRect.width, inputTextRect.top + userInputBox.getSize().y / 2.0f);
	}
	else {
		userInputCursorBlink.setPosition(inputTextRect.left + inputTextRect.width, inputTextRect.top + inputTextRect.height / 2.0f);
	}
	// Update the color of the blinking cursor
	if (gameClock.getElapsedTime().asMilliseconds() % 1000 > 500) {
		userInputCursorBlink.setFillColor(sf::Color::White);
	}
	else {
		userInputCursorBlink.setFillColor(sf::Color::Transparent);
	}

	if (questionCorrect) {
		GenerateQuestion();

	}
}

int screen2::Run(sf::RenderWindow &window) {
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

void screen2::GenerateQuestion() {
	auto newQuestion = questionGen.chooseQuestion();
	screenTitle.setString(newQuestion.first);
	questionAnswer.setString(newQuestion.second);
}