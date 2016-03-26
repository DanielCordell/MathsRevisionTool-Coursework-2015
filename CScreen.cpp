#include "Headers/CScreen.h"

// Detects if a mouse is hovering over a button and changes the colour of the button if it is
void cScreen::buttonHighlightDetect(sf::Vector2i &mousePos, sf::Sprite &button) {
	if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		button.setColor(sf::Color(200, 200, 200));
	}
	else button.setColor(sf::Color::White);
}
void cScreen::buttonHighlightDetect(sf::Vector2i &mousePos, sf::RectangleShape &button) {
	if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		button.setFillColor(sf::Color(200, 200, 200));
	}
	else button.setFillColor(sf::Color::White);
}

sf::Music cScreen::music;
sf::Sound cScreen::buttonClickSound;
sf::SoundBuffer cScreen::buttonClickSoundBuffer;