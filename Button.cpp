#include "Headers/Button.h"
#include <string>

// A class that defines a clickable button with a sprite and a texture.
// The LoadTexture function takes a string parameter, which is the location of the file where the texture is stored.
// This function returns true if texture loading was a success, and false if it has failed. This allows for error detection.
// The InitSprite function takes that texture and applies it to the sprite so it can be used on the screen.

void Button::InitSprite() {
	// Calls the internal function of the sprite class to apply a texture to itself.
	sprite.setTexture(texture);
}

bool Button::loadTexture(std::string file) {
	// Calls the internal function of the texture class to load a texture from a file.
	return texture.loadFromFile(file);
}
