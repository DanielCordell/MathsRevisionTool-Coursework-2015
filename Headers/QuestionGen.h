#pragma once
#include <utility>
#include <string>
//Class that stores all of the question generators.
class questionGenerator {
public:
	// This function chooses a question to generate based on the users settings, and then returns a pair class which stores two
	// strings. The first string is the question text that the user will be asked, the second string is the answer that the user's
	// answer will be compared to.
	std::pair<std::string, std::string> chooseQuestion();
private:
	// This function will generate a quadratic qusetion of the form (x^2 + bx + c = 0)
	std::pair<std::string, std::string> generateQuadratic();
	// This function will generate an addition question of the form (a + b = c)
	std::pair<std::string, std::string> generateAdd();
	// This function will generate a subtraction question of the form (a - b = c)
	std::pair<std::string, std::string> generateSubtract();
	// This function will generate a multiplication question of the form (a * b = c)
	std::pair<std::string, std::string> generateMultiply();
	// This function will generate a division question of the form (a / b = c)
	std::pair<std::string, std::string> generateDivide();
	// This function generates a fraction multiplication question of the form (a/b * c/d = e/f)
	std::pair<std::string, std::string> generateMultiplyFraction();
	// This function generates a functions question of the form (ax + b = c)
	std::pair<std::string, std::string> generateFunctions();
	// This function generates a simultaneous equations question of the form (ax + by = c and dx + ey = f)
	std::pair<std::string, std::string> generateSimultaneous();
};
