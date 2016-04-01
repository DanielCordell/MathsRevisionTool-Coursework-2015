#include "Headers/CScreen.h"

// Initialising functions
// Detects if a mouse is hovering over a button based on the mouse position, and if it is, tints the button slightly grey.
// If it isn't then the tint is removed.
// This version of the function is for sprites
void cScreen::buttonHighlightDetect(sf::Vector2i &mousePos, sf::Sprite &button) {
	// If the mouse's current position is within the bounds of the button
	if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		// Set the tint of the button to RGB color 200,200,200
		button.setColor(sf::Color(200, 200, 200));
	}
	// If not set the tint of the button to white
	else button.setColor(sf::Color::White);
}
// This version of the function is for rectangleShapes (rectangles with no texture attatched)
// Otherwise the function is the same as above
void cScreen::buttonHighlightDetect(sf::Vector2i &mousePos, sf::RectangleShape &button) {
	if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		button.setFillColor(sf::Color(200, 200, 200));
	}
	else button.setFillColor(sf::Color::White);
}

// Declaring the static variables which will exist in every class that inherits from cScreen
sf::Music cScreen::music;
sf::Sound cScreen::buttonClickSound;
sf::SoundBuffer cScreen::buttonClickSoundBuffer;
