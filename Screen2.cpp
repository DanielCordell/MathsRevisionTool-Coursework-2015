#include "Headers/Screen2.h"
#include "Headers/Constants.h"
#include "Headers/Score.h"
#include <iostream>

//Game Screen

bool screen2::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
		|| !backgroundTexture.loadFromFile("Resources/backgroundGame.png")
		|| !heartEmptyTexture.loadFromFile("Resources/heartEmpty.png")
		|| !heartFullTexture.loadFromFile("Resources/heartFull.png")
		|| !buttonBackToMenu.loadTexture("Resources/buttonQuit.png")
		|| !questionCorrectSoundBuffer.loadFromFile("Resources/questionCorrectSound.wav")
		|| !questionIncorrectSoundBuffer.loadFromFile("Resources/questionIncorrectSound.wav")) {
		return false;
	}
	questionAnswered = false;

	//Initialising Sounds
	questionCorrectSound.setBuffer(questionCorrectSoundBuffer);
	questionIncorrectSound.setBuffer(questionIncorrectSoundBuffer);
	questionCorrectSound.setVolume(Settings::volumePercent);
	questionIncorrectSound.setVolume(Settings::volumePercent);

	//Initialising Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getGlobalBounds().width, WINDOW_Y / backgroundSprite.getGlobalBounds().height);

	//Initializing Text Values
	screenTitle = sf::Text("", font, 35);
	userInputText = sf::Text("", font, 40);
	userInputValidText = sf::Text("", font, 20);
	scoreText = sf::Text("Score:     0", font, 60);
	highScoreText = sf::Text("Highscore: 0", font, 60);
	timerText = sf::Text("", font, 60);
	livesText = sf::Text("Lives:", font, 60);

	//Positioning Title and Buttons
	sf::FloatRect textRect;
	textRect = screenTitle.getLocalBounds();
	screenTitle.setPosition(WINDOW_X / 32.0f, WINDOW_Y / 24.0f);
	screenTitle.setColor(sf::Color::Black);

	buttonBackToMenu.InitSprite();
	textRect = buttonBackToMenu.sprite.getLocalBounds();
	buttonBackToMenu.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonBackToMenu.sprite.setPosition(WINDOW_X - 150, WINDOW_Y - 100);

	//Initializing the Answer Box
	userInputBox.setSize(sf::Vector2f(18 * WINDOW_X / 64.0f, WINDOW_Y / 16.0f));
	userInputBox.setOrigin(0, userInputBox.getLocalBounds().height / 2.0f);
	userInputBox.setPosition(sf::Vector2f(WINDOW_X / 32.0f, 7 * WINDOW_Y / 16.0f));
	userInputBox.setFillColor(sf::Color::Black);
	userInputBox.setOutlineColor(sf::Color::White);
	userInputBox.setOutlineThickness(2);
	userInputText.setOrigin(0, userInputText.getLocalBounds().height / 2.0f);
	userInputText.setPosition(userInputBox.getGlobalBounds().left*1.1f, userInputBox.getPosition().y - userInputBox.getLocalBounds().height / 2.0f);
	userInputText.setColor(sf::Color::White);
	userInputValidText.setPosition(userInputBox.getGlobalBounds().left, userInputBox.getGlobalBounds().top - userInputBox.getLocalBounds().height / 2.0f);
	userInputValidText.setColor(sf::Color::Transparent);
	userInputCursorBlink.setSize(sf::Vector2f(WINDOW_X / 196.0f, 2 * userInputBox.getSize().y / 3.0f));
	userInputCursorBlink.setOrigin(0, userInputCursorBlink.getSize().y / 2.0f);
	userInputCursorBlink.setPosition(userInputText.getPosition().x, userInputBox.getPosition().y);

	//Initializing Hearts/Lives
	sf::Sprite baseSprite; // A sprite template.
	for (int i = 0; i <= 2; i++) {
		// Adding the base sprite to the list, and adjusting it's position and texture.
		hearts.push_back(baseSprite);
		hearts[i].setTexture(heartFullTexture);
		hearts[i].setOrigin(heartFullTexture.getSize().x, heartFullTexture.getSize().y / 2.0f);
		hearts[i].setPosition(sf::Vector2f((WINDOW_X - 20) - (9 * heartFullTexture.getSize().x / 8.0f) * (2 - i), 7 * WINDOW_Y / 16.0f));
	}
	livesText.setOrigin(livesText.getLocalBounds().width / 2.0f, livesText.getLocalBounds().height / 2.0f);
	livesText.setPosition(hearts[1].getPosition());
	livesText.move(-hearts[0].getLocalBounds().width / 2.0f, -hearts[0].getLocalBounds().height);
	livesText.setColor(sf::Color::Black);

	//Initializing Score and Timer Text
	scoreText.setPosition(WINDOW_X / 32.0f, 25 * WINDOW_Y / 32.0f);
	scoreText.setColor(sf::Color::Black);
	highScoreText.setPosition(WINDOW_X / 32.0f, 28 * WINDOW_Y / 32.0f);
	highScoreText.setColor(sf::Color::Black);
	timerText.setPosition(WINDOW_X / 32.0f, 22 * WINDOW_Y / 32.0f);
	timerText.setColor(sf::Color::Black);

	return true;
}

void screen2::startGame() {
	// Detects if all question types are disabled.
	bool areQuestionsEnabled = false;
	for (auto questionSetting : Settings::questionSettings) {
		if (questionSetting.second) {
			areQuestionsEnabled = true;
		}
	}
	// If all of the questions are disabled, re-enable all of them.
	if (!areQuestionsEnabled) {
		for (auto &questionSetting : Settings::questionSettings) questionSetting.second = true;
	}

	// Default game settings
	livesCount = 3;
	scoreCount = 0;
	gameOver = false;
	gameStarted = true;
	gameClock.restart();
	didBeatHighScore = false;
	answerIsIncorrect = false;
	Score::newQuestionFromScreen5 = false;
	for (int i = 0; i < 3; i++) {
		hearts[i].setTexture(heartFullTexture);
	}
	userInputValidText.setColor(sf::Color::Transparent);
	userInputText.setString("");
	GenerateQuestion();
}

int screen2::Events(sf::RenderWindow & window) {
	// If the game is over, run the endgame procedure and move to the score screen.
	if (gameOver) {
		endGame(scoreCount, livesCount, didBeatHighScore);
		return screenScore;
	}
	// If the user enters an incorrect answer, reset the user's answer settings (answerIsIncorrect, questionAnswere and 
	// userInputText), pause the game clock, set the answer string in the score class to the answer to the current question,
	// and move to the retry/continue screen.
	if (answerIsIncorrect) {
		answerIsIncorrect = false;
		userInputText.setString("");
		questionAnswered = false;
		gameClock.pause();
		Score::answer = questionStore.second;
		return screenRetry;
	}
	// If the retry screen has specified that a new question must be generated, generate a new question.
	if (Score::newQuestionFromScreen5) {
		Score::newQuestionFromScreen5 = false;
		GenerateQuestion();
	}

	// Polling window events
	sf::Event event;
	while (window.pollEvent(event)) {
		//If the game should quit...
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			endGame(scoreCount, livesCount, didBeatHighScore);
			return screenScore;
		}
		// If the mouse button is pressed...
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));
				if (buttonBackToMenu.sprite.getGlobalBounds().contains(mousePos)) {
					endGame(scoreCount, livesCount, didBeatHighScore);
					buttonClickSound.play();
					return screenScore;
				}
			}
		}
		// If text is entered...
		if (event.type == sf::Event::TextEntered) {
			// The entered character.
			char textInput = event.text.unicode;
			// A boolean value which detects if the entered character is valid.
			bool validCharacter = false;

			// Detect if entered text is a number...
			if ((textInput - '0') >= 0 && (textInput - '0') <= 9) {
				validCharacter = true;
			}

			// Detect if entered text is a valid symbol (/ or -)
			else if (textInput == '/' || textInput == '-') validCharacter = true;
			if (validCharacter) {
				// If the text input is a valid character, and the current length of the answer string is less than
				// 8, then add the character to the string.
				if (userInputText.getString().getSize() < 8) {
					userInputText.setString(userInputText.getString() + textInput);
					userInputValidText.setColor(sf::Color::Transparent);
				}
				else {
				// if the current length of the input string is eight or more, then display the userInputValidText with
				// the string "8 characters maximum" to alert the user of their error.
					userInputValidText.setColor(sf::Color::Black);
					userInputValidText.setString("8 characters maximum");
				}
			}
			// If the text input is not a valid chaaracter, display the userInputValidText with the string alerting the user
			// that they must enter a valid character.
			else {
				userInputValidText.setString("Please enter a valid character: (0 - 9, '/', and '-')");
				userInputValidText.setColor(sf::Color::Black);
			}

			// Detect if entered text is a backspace.
			if (textInput == 8) {
				userInputText.setString(userInputText.getString().substring(0, userInputText.getString().getSize() - 1));
				userInputValidText.setColor(sf::Color::Transparent);
			}
		}
		//If Enter key is pressed
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Return) {
				userInputValidText.setColor(sf::Color::Transparent);
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

void screen2::Draw(sf::RenderWindow & window) {
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
	window.draw(livesText);
	window.display();
}

void screen2::Update() {
	// Start the game clock on the first update tick.
	gameClock.start();

	sf::FloatRect inputTextRect = userInputText.getGlobalBounds();
	// Update the position of the blinking cursor
	userInputCursorBlink.setPosition(inputTextRect.left + inputTextRect.width, userInputCursorBlink.getPosition().y);

	// Update the color of the blinking cursor
	if (gameClock.getElapsedTime().asMilliseconds() % 1000 > 500) {
		userInputCursorBlink.setFillColor(sf::Color::White);
	}
	else {
		userInputCursorBlink.setFillColor(sf::Color::Transparent);
	}
	
	// If the question has been answered and it is correct, increment the score, play the question correct sound, delete the
	// user input and generate a new question.
	if (questionAnswered) {
		if (questionStore.second == userInputText.getString()) {
			userInputText.setString("");
			scoreCount++;
			questionCorrectSound.play();
			GenerateQuestion();
		}
		// If the answer is not correct, decrement the score, play the question incorrect sound.
		// If the number of lives is now 0, then end the game. If not, then set the answerIsIncorrect boolean to true.
		else {
			livesCount--;
			questionIncorrectSound.play();
			if (livesCount == 0) {
				gameOver = true;
			}
			else {
				answerIsIncorrect = true;
			}
		}
	}
	
	// Set the heart empty texture to the correct number of hearts depending on the number of lives.
	for (int i = 2 - livesCount; i >= 0; i--) {
		hearts[i].setTexture(heartEmptyTexture);
	}
	// If the high score has been beaten, set the high score to the current score, and set the bool didBeatHighScore to true.
	if (scoreCount > Settings::highScore) {
		Settings::highScore = scoreCount;
		didBeatHighScore = true;
	}
	// Update the score, highscore and timer text.
	scoreText.setString("Score:     " + std::to_string(scoreCount));
	highScoreText.setString("Highscore: " + std::to_string(Settings::highScore));
	
	int minutes = gameClock.getElapsedTime().asSeconds() / 60;
	int totalSeconds = gameClock.getElapsedTime().asMilliseconds() / 1000;
	int seconds = totalSeconds % 60;
	timerText.setString("Time:   " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
	// Change the colour of the timer depending on the number of seconds left.
	if (totalSeconds >= 250 && totalSeconds < 280) {
		timerText.setColor(sf::Color(255, 165, 0));
	}
	else if (totalSeconds >= 280 && totalSeconds < 290) {
		timerText.setColor(sf::Color::Red);
	}
	else if (totalSeconds >= 290 && totalSeconds < 300) {
		if (totalSeconds % 2 == 0) {
			timerText.setColor(sf::Color::Red);
		}
		else {
			timerText.setColor(sf::Color(255, 165, 0);
		}
	}
	// If the number of seconds exceeds 300 (5 minutes) then end the game.
	else if (totalSeconds >= 300) {
		gameOver = true;
	}
	// Set the volume for the correct and incorrect sounds.
	questionCorrectSound.setVolume(Settings::volumePercent);
	questionIncorrectSound.setVolume(Settings::volumePercent);
}

int screen2::Run(sf::RenderWindow &window) {
	sf::Clock clock;
	// If a game has not been started, then run the startGame function.
	if (!gameStarted) startGame();
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
	// Set the questionStore to a new randomly generated question, and display the new question.
	questionStore = questionGen.chooseQuestion();
	screenTitle.setString(questionStore.first);
	questionAnswered = false;
}

void screen2::endGame(int finalScore, int livesRemaining, bool didBeatHighScore) {
	// Set all score values to their corresponding variables in the store class.
	Score::finalScore = finalScore;
	Score::livesRemaining = livesRemaining;
	Score::didBeatHighScore = didBeatHighScore;
};
