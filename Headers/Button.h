#pragma once
#include "SFML\Graphics.hpp"

class Button {
public:
	sf::Sprite sprite;
	sf::Texture texture;
	void InitSprite();
	bool loadTexture(std::string file);
};