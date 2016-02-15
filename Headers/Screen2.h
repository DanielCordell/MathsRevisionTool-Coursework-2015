#pragma once
#include "CScreen.h"
#include "QuestionGen.h"
#include "Settings.h"


// Class Declaration for Screen that displays the Game Menu
class screen2 : public cScreen{
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
	sf::RectangleShape userInputCursorBlink;
	sf::Clock gameClock;
	questionGenerator questionGen;
	std::pair<std::string, std::string> questionStore;
	bool questionAnswered;
	bool gameOver;
	bool didBeatHighScore;
	int scoreCount;
	int livesCount;

	sf::Texture heartEmptyTexture;
	sf::Texture heartFullTexture;

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
