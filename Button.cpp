#include "Headers/Button.h"
#include <string>

void Button::InitSprite() {
	sprite.setTexture(texture);
}

bool Button::loadTexture(std::string file) {
	return texture.loadFromFile(file);
}