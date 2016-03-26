#pragma once
#include "CScreen.h"
#include "QuestionGen.h"
#include "Settings.h"
#include "PauseableClock.hpp"

// Class Declaration for Screen that displays the Game
class screen2: public cScreen {
private:
	sf::Text screenTitle;
	Button buttonBackToMenu;

	sf::Font font;

	sf::RectangleShape userInputBox;
	sf::Text userInputText;
	sf::Text userInputValidText;
	sf::Text scoreText;
	sf::Text highScoreText;
	sf::Text timerText;
	sf::Text livesText;
	sf::RectangleShape userInputCursorBlink;
	sf::PauseableClock gameClock;
	questionGenerator questionGen;
	std::pair<std::string, std::string> questionStore;
	bool gameStarted;
	bool questionAnswered;
	bool answerIsIncorrect;
	bool gameOver;
	bool didBeatHighScore;
	int scoreCount;
	int livesCount;

	sf::Texture heartEmptyTexture;
	sf::Texture heartFullTexture;

	sf::Sound questionCorrectSound;
	sf::Sound questionIncorrectSound;
	sf::SoundBuffer questionCorrectSoundBuffer;
	sf::SoundBuffer questionIncorrectSoundBuffer;

	std::vector<sf::Sprite> hearts;

public:
	int Run(sf::RenderWindow &window);
	bool Init();
	void startGame();
	void endGame(int finalScore, int livesRemaining, bool didBeatHighScore);
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();
	void GenerateQuestion();
};
