#include "Headers/CScreen.h"

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
