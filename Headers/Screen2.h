#pragma once
#include "CScreen.h"
#include "QuestionGen.h"
#include "Settings.h"
#include "PauseableClock.h"

// Class Declaration for Screen that displays the Game
class screen2: public cScreen {
private:
	// The on screen text representing the screen title. On this screen, this is the current question.
	sf::Text screenTitle;
	// Class representing the button to take the user back to the main menu.
	Button buttonBackToMenu;
	// The font for the current screen.
	sf::Font font;
	// A rectangle representing the user input box.
	sf::RectangleShape userInputBox;
	// A rectangle representing the blinking input cursor.
	sf::RectangleShape userInputCursorBlink;
	// The text that stores the user's input.
	sf::Text userInputText;
	// The text that displays when the user's input is invalid (invalid characters or too long).
	sf::Text userInputValidText;
	// The text that shows the current score.
	sf::Text scoreText;
	// The text that shows the current high score.
	sf::Text highScoreText;
	// The text that shows the current time (mm:ss).
	sf::Text timerText;
	// The text that is used to identify the lives counter.
	sf::Text livesText;
	// The internal clock.
	sf::PauseableClock gameClock;
	// The class which contains all necessary procedures to randomly generate questions.
	questionGenerator questionGen;
	// A class which stores a pair of objects,in this case the current question and the current answer, as strings.
	std::pair<std::string, std::string> questionStore;
	// A boolean which is true if a game (or round) has started.
	bool gameStarted;
	// A boolean which is true if the user has answed a question (no matter if it is correct or not).
	bool questionAnswered;
	// A boolean which is true if the user's answer is incorrect.
	bool answerIsIncorrect;
	// A boolean which is true when the game is over (lives run out or timer runs out).
	bool gameOver;
	// A boolean which is true if the user has beaten their high score.
	bool didBeatHighScore;
	// The current score and number of lives.
	int scoreCount;
	int livesCount;
	// The texture for an empty heart and a full heart, used for lives.
	sf::Texture heartEmptyTexture;
	sf::Texture heartFullTexture;
	// The sound and soundbuffers for the question correct and incorrect noises.
	sf::Sound questionCorrectSound;
	sf::Sound questionIncorrectSound;
	sf::SoundBuffer questionCorrectSoundBuffer;
	sf::SoundBuffer questionIncorrectSoundBuffer;
	// A list of sprites, which will represent the tree on screen hearts.
	std::vector<sf::Sprite> hearts;

public:
// This class has slightly different functions than the other screens:
	// The game loop
	int Run(sf::RenderWindow &window);
	// The initialisation function, this runs once when the program is opened, and returns false if there is an initialsation error
	// (failed loading textures).
	bool Init();
	// This function sets up a game, and is run at the start of each game (round).
	void startGame();
	// This function is run at the end of each game, and prepares the score screen.
	void endGame(int finalScore, int livesRemaining, bool didBeatHighScore);
	// The function which handles all screen events. Return value is the ID of the next screen to be loaded.
	int Events(sf::RenderWindow &window);
	// Draws all resources to the screen.
	void Draw(sf::RenderWindow &window);
	// Updates all game logic.
	void Update();
	// Generates a new random question based on the user's settings.
	void GenerateQuestion();
};
