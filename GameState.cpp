#include "Headers/GameState.h"
#include "Headers/Constants.h"
#include <iostream>


GameState::GameState() {
	Window.create(sf::VideoMode(WINDOW_X, WINDOW_Y), "YAY A THING", sf::Style::Close);
	Window.setKeyRepeatEnabled(false);
}