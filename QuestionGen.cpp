#include "Headers\Rand.h"
#include "Headers\QuestionGen.h"
#include <iostream> // Temp
#include "Headers\Settings.h"

std::pair<std::string, std::string> questionGenerator::generateQuadratic() {
	int solution1 = getRand(1, 15) * getPlMn();
	int solution2 = getRand(1, 15) * getPlMn();
	int factorValue1 = -solution1;
	int factorValue2 = -solution2;

	int coeffX = (factorValue1 + factorValue2);
	int coeffC = factorValue1 * factorValue2;

	bool useLarger = getBool();
	std::string questionText = ("What is the value of the " + std::string((solution1 == solution2) ? "" : (useLarger ? "largest" : "smallest")) + " solution to the equation:\n\n");
	questionText.append("x² + " + std::to_string(coeffX) + "x + " + std::to_string(coeffC));

	std::string answerText;

	if (useLarger) {
		answerText =  solution1 > solution2 ? solution1 : solution2;
	}
	else {
		answerText = solution1 < solution2 ? solution1 : solution2;
	}

	return std::make_pair(questionText, answerText);
}

std::pair<std::string, std::string> questionGenerator::generateAdd() {
	int value1 = getRand(30, 250) * getPlMn();
	int value2 = getRand(30, 250);
	int solution = value1 + value2;
	std::cout << value1 << " + " << value2 << " = " << solution << "\n\n";

	std::string questionText;
	std::string answerText;

	return std::make_pair(questionText, answerText);
}
std::pair<std::string, std::string> questionGenerator::generateSubtract() {
	int value1 = getRand(30, 250) * getPlMn();
	int value2 = getRand(30, 250);
	int solution = value1 - value2;
	std::cout << value1 << " - " << value2 << " = " << solution << "\n\n";

	std::string questionText;
	std::string answerText;

	return std::make_pair(questionText, answerText);
}
std::pair<std::string, std::string> questionGenerator::generateMultiply() {
	int value1 = getRand(5, 25) * getPlMn();
	int value2 = getRand(5, 25) * getPlMn();
	int solution = value1 * value2;
	std::cout << value1 << " x " << value2 << " = " << solution << "\n\n";

	std::string questionText;
	std::string answerText;

	return std::make_pair(questionText, answerText);
}
std::pair<std::string, std::string> questionGenerator::generateDivide() {
	int quotent = getRand(10, 30) * getPlMn();
	int divisor = getRand(10, 30) * getPlMn();
	int dividend = quotent * divisor;

	std::cout << dividend << " / " << divisor << " = " << quotent << "\n\n";

	std::string questionText;
	std::string answerText;

	return std::make_pair(questionText, answerText);
}

std::pair<std::string, std::string> questionGenerator::generateMultiplyFraction() {
	int temp;

	int numerator1 = getRand(1, 15);
	temp = getRand(2, 10);		// This will become the denominator
	int denominator1 = temp * ((numerator1 == temp) ? 2 : 1); // If numerator = denominator then double the denominator (astd::pair<std::string, std::string>ing x/x = 1)

	int numerator2 = getRand(1, 15);
	temp = getRand(2, 10);		// This will become the denominator
	int	denominator2 = temp * ((numerator2 == temp) ? 2 : 1); // If numerator = denominator then double the denominator

	int numeratorAnswer = numerator1 * numerator2;
	int denominatorAnswer = denominator1 * denominator2;

	for (int i = numeratorAnswer * denominatorAnswer; i > 1; i--) {
		if ((denominatorAnswer % i == 0) && (numeratorAnswer % i == 0)) {
			denominatorAnswer /= i;
			numeratorAnswer /= i;
		}
	}

	std::cout << numerator1 << "/" << denominator1 << " * " << numerator2 << "/" << denominator2 << "\n";
	if (denominatorAnswer == 1) std::cout << "= " << numeratorAnswer << "\n\n";
	else std::cout << "= " << numeratorAnswer << "/" << denominatorAnswer << "\n\n";

	std::string questionText;
	std::string answerText;

	return std::make_pair(questionText, answerText);
}
std::pair<std::string, std::string> questionGenerator::generateFunctions() {
	int coeffx = getRand(2, 40) * getPlMn();
	int valuex = getRand(2, 20) * getPlMn();
	int valuec = getRand(5, 40) * getPlMn();

	int answer = coeffx * valuex + valuec;

	std::cout << coeffx << "x + " << valuec << " = " << answer << "\n";
	std::cout << "x = " << valuex << "\n\n";

	std::string questionText;
	std::string answerText;

	return std::make_pair(questionText, answerText);
}

std::pair<std::string, std::string> questionGenerator::generateSimultaneous() {
	int valuex = getRand(1, 30) * getPlMn();
	int valuey = getRand(1, 30) * getPlMn();

	int coeffx_1 = getRand(1, 6) * getPlMn();
	int coeffy_1 = getRand(1, 6) * getPlMn();
	int coeffx_2 = getRand(1, 6) * getPlMn();
	int coeffy_2 = getRand(1, 6) * getPlMn();

	int answer1 = coeffx_1 * valuex + coeffy_1 * valuey;
	int answer2 = coeffx_2 * valuex + coeffy_2 * valuey;

	std::cout << coeffx_1 << "x + " << coeffy_1 << "y = " << answer1 << "\n";
	std::cout << coeffx_2 << "x + " << coeffy_2 << "y = " << answer2 << "\n";
	std::cout << "x = " << valuex << ", y = " << valuey << "\n\n";

	std::string questionText;
	std::string answerText;

	return std::make_pair(questionText, answerText);
}

std::pair<std::string, std::string> questionGenerator::chooseQuestion(){
	std::vector<std::string> allowedQuestions;
	for (auto iterator : Settings::questionSettings) {
		if (iterator.second) {
			allowedQuestions.insert(allowedQuestions.end(), iterator.first);
		}
	}
	int randomIndex = getRand(0, allowedQuestions.size);
	std::string questionType = allowedQuestions[randomIndex];

	if (questionType == )

		// MAKE AN ENUM
}