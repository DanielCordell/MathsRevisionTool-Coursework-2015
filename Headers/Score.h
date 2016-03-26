#pragma once
#include "SFML\Graphics.hpp"

struct Score {
	static int finalScore;
	static int livesRemaining;
	static bool didBeatHighScore;
	static bool newQuestionFromScreen5;
	static std::string answer;
};