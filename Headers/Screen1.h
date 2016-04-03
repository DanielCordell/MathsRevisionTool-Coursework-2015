#pragma once
#include "CScreen.h"
#include "Settings.h"
#include "Constants.h"

// Class Declaration for Screen that displays the settings menu. This inherits from the cScreen class.
class screen1: public cScreen {
private:
	// The on screen text representing the screen title.
	sf::Text screenTitle;
	// Class representing the button to return the user back to the main menu.
	Button buttonBackToMenu;
	// The texture representing the cross from a checkbox
	sf::Texture buttonCrossTexture;
	
	// The on screen text that will display the subheading 'volume options'.
	sf::Text screenTitleVolume;
	// The on screen text which will identify the volume slider.
	sf::Text volumeText;
	// The array of vertices which make up the trianglular shape of the volume slider.
	sf::VertexArray volumeSliderBack;
	// The white rectangular slider which the user can adjust to change the volume settings.
	sf::RectangleShape volumeSlider;
	
	// The on screen text that will identify the mute checkbox
	sf::Text muteText;
	// The rectangular shape which will form the clickable part of the checkbox
	sf::RectangleShape muteButtonBack;
	// The checkbox cross which will appear and disappear as needed.
	sf::Sprite muteButtonCrossSprite;
	
	// The on screen text that will display the subheading "Enable / Disable Questions"
	sf::Text screenTitleQuestions;
	
	// The on screen text which will identify the addition questions checkbox, the rectangular clickable part of the checkbox,
	// and the checkbox cross. All other checkboxes have the same three parts.
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
	
	// The font used on the current screen.
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
