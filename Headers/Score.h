#pragma once
#include "SFML\Graphics.hpp"

struct Score {
	// These are all static, so every implementation of the struct class will contain these instances of the member variables.
	// The integer value of the user's final score
	static int finalScore;
	// The number of lives remaining at the end of a round of questions.
	static int livesRemaining;
	// A boolean determining if the user has beaten the current high score.
	static bool didBeatHighScore;
	// A boolean detecting if the user has opted to try a new question from the retry/continue screen (screen5).
	static bool newQuestionFromScreen5;
	// The answer to the current question, this is passed to screen5 and displayed if the user wishes to continue to a new question.
	static std::string answer;
};
