#pragma once
#include "SFML\Graphics.hpp"

// A class that defines a clickable button with a sprite and a texture.
// The LoadTexture function takes a string parameter, which is the location of the file where the texture is stored.
// This function returns true if texture loading was a success, and false if it has failed. This allows for error detection.
// The InitSprite function takes that texture and applies it to the sprite so it can be used on the screen.

class Button {
public:
	sf::Sprite sprite;
	sf::Texture texture;
	void InitSprite();
	bool loadTexture(std::string file);
};
