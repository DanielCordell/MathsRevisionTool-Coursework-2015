#include "Headers/Button.h"
#include <string>

// A class that defines a clickable button with a sprite and a texture

void Button::InitSprite() {
	sprite.setTexture(texture);
}

bool Button::loadTexture(std::string file) {
	return texture.loadFromFile(file);
}