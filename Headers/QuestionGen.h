#include "Screen2.h"
//Class that stores the question generators
class questionGenerator {
public:
	// Choose a question to generate based on user settings
	std::pair<std::string, std::string> chooseQuestion();
private:
	// (x^2 + bx + c = 0)
	std::pair<std::string, std::string> generateQuadratic();
	// (a + b = c)
	std::pair<std::string, std::string> generateAdd();
	// (a - b = c)
	std::pair<std::string, std::string> generateSubtract();
	// (a * b = c)
	std::pair<std::string, std::string> generateMultiply();
	// (a / b = c)
	std::pair<std::string, std::string> generateDivide();
	// (a/b * c/d = e/f)
	std::pair<std::string, std::string> generateMultiplyFraction();
	// (ax + b = c)
	std::pair<std::string, std::string> generateFunctions();
	// (ax + by = c and dx + ey = f)
	std::pair<std::string, std::string> generateSimultaneous();
};

