#pragma once
#include "CScreen.h"
#include "Settings.h"
#include "Constants.h"

// Class Declaration for Screen that displays the Options Menu
class screen1 : public cScreen{
private:
	sf::Text screenTitle;
	Button buttonBackToMenu;

	sf::Texture buttonCrossTexture;

	sf::Text screenTitleVolume;
	sf::Text volumeText;
	sf::VertexArray volumeSliderBack;
	sf::RectangleShape volumeSlider;

	sf::Text muteText;
	sf::RectangleShape muteButtonBack;
	sf::Sprite muteButtonCrossSprite;

	sf::Text screenTitleQuestions;
	
	sf::Text questionTextAdd;
	sf::RectangleShape questionButtonAddBack;
	sf::Sprite questionButtonAddSprite;
	
	sf::Text questionTextSubtract;
	sf::RectangleShape questionButtonSubtractBack;
	sf::Sprite questionButtonSubtractSprite;

	sf::Text questionTextMultiply;
	sf::RectangleShape questionButtonMultiplyBack;
	sf::Sprite questionButtonMultiplySprite;

	sf::Text questionTextDivide;
	sf::RectangleShape questionButtonDivideBack;
	sf::Sprite questionButtonDivideSprite;

	sf::Text questionTextQuadratic;
	sf::RectangleShape questionButtonQuadraticBack;
	sf::Sprite questionButtonQuadraticSprite;

	sf::Text questionTextMultiplyFraction;
	sf::RectangleShape questionButtonMultiplyFractionBack;
	sf::Sprite questionButtonMultiplyFractionSprite;

	sf::Text questionTextFunctions;
	sf::RectangleShape questionButtonFunctionsBack;
	sf::Sprite questionButtonFunctionsSprite;

	sf::Text questionTextSimultaneous;
	sf::RectangleShape questionButtonSimultaneousBack;
	sf::Sprite questionButtonSimultaneousSprite;

	sf::Font font;

	// If true the volume slider is allowed to move
	bool canVolumeMove;

	// Integer value of the default size of the slider
	sf::Vector2f defaultSliderSize;
public:
	int Run(sf::RenderWindow &window);
	bool Init();
	int Events(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);;
	void Update();
};
