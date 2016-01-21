#pragma once
#include "CScreen.h"
#include "QuestionGen.h"

// Class Declaration for Screen that displays the Game Menu
class screen2 : public cScreen{
private:
	sf::Text screenTitle;
	sf::Text buttonBackToMenu;

	sf::Font font;

	sf::RectangleShape userInputBox;
	sf::Text userInputText;
	sf::Text userInputValidText;
	sf::RectangleShape userInputCursorBlink;
	sf::Clock gameClock;
	questionGenerator questionGen;
	std::pair<std::string, std::string> questionStore;

	sf::Text questionAnswer;
	bool questionAnswered;
	bool questionCorrect;
public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();
	void GenerateQuestion();

	~screen2();
};
