#include "Headers/Screen2.h"
#include "Headers/Constants.h"
#include "Headers/Score.h"
#include <iostream>

//Game Screen

bool screen2::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
		||	!backgroundTexture.loadFromFile("Resources/backgroundGame.png")
		||	!heartEmptyTexture.loadFromFile("Resources/heartEmpty.png")
		||	!heartFullTexture.loadFromFile("Resources/heartFull.png")
		||	!buttonBackToMenu.loadTexture("Resources/buttonQuit.png")){
		return false;
	}	
		questionAnswered = false;

	//Initialize Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);

	//Initializing Text Values
	screenTitle = sf::Text("", font, 35);
	userInputText = sf::Text("", font, 40);
	userInputValidText = sf::Text("", font, 20);
	scoreText = sf::Text("", font, 60);
	highScoreText = sf::Text("", font, 60);
	timerText = sf::Text("", font, 60);


	//Positioning Title and Buttons
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setPosition(WINDOW_X / 32.0f, WINDOW_Y / 24.0f);
	screenTitle.setColor(sf::Color::Black);

	buttonBackToMenu.InitSprite();
	textRect = buttonBackToMenu.sprite.getLocalBounds();
	buttonBackToMenu.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonBackToMenu.sprite.setPosition(150, WINDOW_Y - 100);

	timerText.setPosition(23 * WINDOW_X / 32.0f, 10 * WINDOW_Y / 32.0f);
	timerText.setColor(sf::Color::Black);

	//Initializing Answer Box
	userInputBox.setSize(sf::Vector2f(10 * WINDOW_X / 32.0f, WINDOW_Y / 16.0f));
	userInputBox.setOrigin(userInputBox.getLocalBounds().width / 2, userInputBox.getLocalBounds().height / 2);
	userInputBox.setPosition(sf::Vector2f(13 * WINDOW_X / 16.0f, buttonBackToMenu.sprite.getPosition().y));
	userInputBox.setFillColor(sf::Color::Black);
	userInputBox.setOutlineColor(sf::Color::White);
	userInputBox.setOutlineThickness(2);
	userInputText.setOrigin(0, userInputText.getLocalBounds().height / 2.0f);
	userInputText.setPosition(userInputBox.getGlobalBounds().left*1.01f,userInputBox.getPosition().y - userInputBox.getLocalBounds().height / 2);
	userInputText.setColor(sf::Color::White);
	userInputValidText.setPosition(userInputBox.getGlobalBounds().left, userInputBox.getGlobalBounds().top - userInputBox.getLocalBounds().height);
	userInputValidText.setColor(sf::Color::Transparent);
	userInputCursorBlink.setSize(sf::Vector2f(WINDOW_X / 196.0f, 2 * userInputBox.getSize().y / 3.0f));
	userInputCursorBlink.setOrigin(0, userInputCursorBlink.getSize().y / 2.0f);
	userInputCursorBlink.setPosition(userInputText.getPosition().x, userInputBox.getPosition().y
);

	//Initializing Hearts/Lives
	sf::Sprite baseSprite;
	auto bounds = userInputBox.getGlobalBounds();
	for (int i = 0; i <= 2; i++) {
		hearts.push_back(baseSprite);
		hearts[i].setTexture(heartFullTexture);
		hearts[i].setOrigin(sf::Vector2f(heartFullTexture.getSize()));
		hearts[i].setPosition(sf::Vector2f((bounds.width + bounds.left) - (bounds.width/3.0f) * (2-i), 6 * WINDOW_Y / 8.0f));
	}

	//Initializing Score Text
	scoreText.setPosition(WINDOW_X / 32.0f, 14 * WINDOW_Y / 32.0f);
	scoreText.setColor(sf::Color::Black);
	highScoreText.setPosition(WINDOW_X / 32.0f, 17 * WINDOW_Y / 32.0f);
	highScoreText.setColor(sf::Color::Black);

	return true;
}

void screen2::startGame() {
	livesCount = 3;
	scoreCount = 0;
	gameOver = false;
	gameClock.restart();
	didBeatHighScore = false;
	for (int i = 0; i < 3; i++) {
		hearts[i].setTexture(heartFullTexture);
	}
	GenerateQuestion();
}

int screen2::Events(sf::RenderWindow & window)
{
	if (gameOver) {
		endGame(scoreCount, livesCount, didBeatHighScore);
		return screenScore;
	}
	// Polling window events
	sf::Event event;
	while (window.pollEvent(event)) {
		//If the game should quit
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			endGame(scoreCount, livesCount, didBeatHighScore);
			return screenScore;
		}
		// If the mouse button is pressed
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				if (buttonBackToMenu.sprite.getGlobalBounds().contains(mousePos)) {
					endGame(scoreCount, livesCount, didBeatHighScore);
					return screenScore;
				}
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
			else if (textInput == '/' || textInput == '-') validCharacter = true;
			if (validCharacter) {
				if (userInputText.getString().getSize() < 16) {
					userInputText.setString(userInputText.getString() + textInput);
					userInputValidText.setColor(sf::Color::Transparent);
				}
				else {
					userInputValidText.setString("16 characters maximum.");
					userInputValidText.setColor(sf::Color::Black);
				}
			}
			else {
				userInputValidText.setString("Please enter a valid character:\n(0 - 9, '/', and '-')");
				userInputValidText.setColor(sf::Color::Black);
			}
			
			// Detect if entered text is a backspace
			if (textInput == 8) {
				userInputText.setString(userInputText.getString().substring(0, userInputText.getString().getSize() - 1));
				userInputValidText.setColor(sf::Color::Transparent);
			}
			if (textInput == 13) {
				userInputValidText.setColor(sf::Color::Transparent);
			}
		}
		//If Enter key is pressed
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Return) {
				questionAnswered = true;
			}
		}
		//If mouse is moved
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			buttonHighlightDetect(mousePos, buttonBackToMenu.sprite);
		}
	}
	return getCurrentScreen();
}


void screen2::Draw(sf::RenderWindow & window)
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonBackToMenu.sprite);

	window.draw(userInputBox);
	window.draw(userInputText);
	window.draw(userInputValidText);
	window.draw(userInputCursorBlink);
	window.draw(scoreText);
	window.draw(highScoreText);
	window.draw(timerText);
	for (auto heart : hearts) window.draw(heart);

	window.display();
}

void screen2::Update()
{
	sf::FloatRect inputTextRect = userInputText.getGlobalBounds();
	// Update the position of the blinking cursor
	if (userInputText.getString().getSize() == 0) {
		userInputCursorBlink.setPosition(inputTextRect.left + inputTextRect.width, userInputCursorBlink.getPosition().y);
	}
	else {
		userInputCursorBlink.setPosition(inputTextRect.left + inputTextRect.width, userInputCursorBlink.getPosition().y);
	}
	// Update the color of the blinking cursor
	if (gameClock.getElapsedTime().asMilliseconds() % 1000 > 500) {
		userInputCursorBlink.setFillColor(sf::Color::White);
	}
	else {
		userInputCursorBlink.setFillColor(sf::Color::Transparent);
	}

	if (questionAnswered) {
		if (questionStore.second == userInputText.getString()) {
			userInputText.setString("");
			scoreCount++;
			GenerateQuestion();
		}
		else {
			livesCount--;
			if (livesCount == 0) {
				endGame(scoreCount, livesCount, didBeatHighScore);
			}
			else {
				GenerateQuestion();
			}
		}
	}

	for (int i = 2 - livesCount; i >= 0; i--) {
		hearts[i].setTexture(heartEmptyTexture);
	}
	if (scoreCount > Settings::highScore) {
		Settings::highScore = scoreCount;
		didBeatHighScore = true;
	}
	scoreText.setString("Score:     " + std::to_string(scoreCount));
	highScoreText.setString("Highscore: " + std::to_string(Settings::highScore));

	int seconds = gameClock.getElapsedTime().asMilliseconds() / 1000;
	int milliseconds = (gameClock.getElapsedTime().asMilliseconds() - seconds * 1000) / 10;
	timerText.setString(std::to_string(seconds) + ":" + std::to_string(milliseconds));

	if (seconds >= 250 && seconds < 280) {
		timerText.setColor(sf::Color(255, 165, 0));
	}
	else if (seconds >= 280  && seconds < 290) {
		timerText.setColor(sf::Color::Red);
	}
	else if (seconds >= 290) {
		if (seconds % 2 == 0) {
			timerText.setColor(sf::Color::Red);
		}
		else {
			timerText.setColor(sf::Color::Black);
		}
	}

}

int screen2::Run(sf::RenderWindow &window) {
	sf::Clock clock;
	bool doQuit = false;
	startGame();
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
	userInputText.setString("");
	questionStore = questionGen.chooseQuestion();
	screenTitle.setString(questionStore.first);
	questionAnswered = false;
}

void screen2::endGame(int finalScore, int livesRemaining, bool didBeatHighScore) {
	Score::finalScore = finalScore;
	Score::livesRemaining = livesRemaining;
	Score::didBeatHighScore = didBeatHighScore;
	gameOver = true;
}; 

