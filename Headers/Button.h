#pragma once
#include "SFML\Graphics.hpp"

// A class that defines a clickable button with a sprite and a texture

class Button {
public:
	sf::Sprite sprite;
	sf::Texture texture;
	void InitSprite();
	bool loadTexture(std::string file);
};