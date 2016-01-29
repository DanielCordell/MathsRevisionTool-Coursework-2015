#include "Headers\Rand.h"
#include "Headers\QuestionGen.h"
#include <iostream> // Temp
#include "Headers\Settings.h"
#include <vector>
std::pair<std::string, std::string> questionGenerator::chooseQuestion() {
	std::vector<questionTypes> allowedQuestions;
	for (auto iterator : Settings::questionSettings) {
		if (iterator.second) {
			allowedQuestions.insert(allowedQuestions.end(), iterator.first);
		}
	}
	int randomIndex = getRand(0, allowedQuestions.size() - 1);
	questionTypes questionType = allowedQuestions[randomIndex];

	switch (questionType) {
	case questionTypes::add:
		return generateAdd();
	case questionTypes::sub:
		return generateSubtract();
	case questionTypes::mlt:
		return generateMultiply();
	case questionTypes::dvd:
		return generateDivide();
	case questionTypes::fns:
		return generateFunctions();
	case questionTypes::mfr:
		return generateMultiplyFraction();
	case questionTypes::qdr:
		return generateQuadratic();
	case questionTypes::sim:
		return generateSimultaneous();
	default:
		break;
	return generateAdd();
	}
}

std::pair<std::string, std::string> questionGenerator::generateQuadratic() {
	int solution1 = getRand(1, 15) * getPlMn();
	int solution2 = getRand(1, 15) * getPlMn();

	int factorValue1 = -solution1;
	int factorValue2 = -solution2;

	int coeffX = factorValue1 + factorValue2;
	int coeffC = factorValue1 * factorValue2;

	bool useLarger = getBool();
	std::string questionText = ("What is the value of the " + std::string((solution1 == solution2) ? "" : (useLarger ? "largest" : "smallest")) + " solution to this equation?\n\n");
	questionText.append("x² + " + std::to_string(coeffX) + "x + " + std::to_string(coeffC) + " = 0");

	std::string answerText;
	if (useLarger) {
		answerText =  std::to_string(solution1 > solution2 ? solution1 : solution2);
	}
	else {
		answerText = std::to_string(solution1 < solution2 ? solution1 : solution2);
	}

	return std::make_pair(questionText, answerText);
}

std::pair<std::string, std::string> questionGenerator::generateAdd() {
	int value1 = getRand(30, 250) * getPlMn();
	int value2 = getRand(30, 250);
	int solution = value1 + value2;

	std::string questionText = "What is the solution to this equation?\n\n";
	questionText.append(std::to_string(value1) + " + " + std::to_string(value2) + " = ?");
	std::string answerText = std::to_string(solution);

	return std::make_pair(questionText, answerText);
}
std::pair<std::string, std::string> questionGenerator::generateSubtract() {
	int value1 = getRand(30, 250) * getPlMn();
	int value2 = getRand(30, 250);
	int solution = value1 - value2;

	std::string questionText = "What is the solution to this equation?\n\n";
	questionText.append(std::to_string(value1) + " - " + std::to_string(value2) + " = ?");
	std::string answerText = std::to_string(solution);

	return std::make_pair(questionText, answerText);
}
std::pair<std::string, std::string> questionGenerator::generateMultiply() {
	int value1 = getRand(5, 25) * getPlMn();
	int value2 = getRand(5, 25) * getPlMn();
	int solution = value1 * value2;

	std::string questionText = "What is the solution to this equation?\n\n";
	questionText.append(std::to_string(value1) + " × " + std::to_string(value2) + " = ?");
	std::string answerText = std::to_string(solution);

	return std::make_pair(questionText, answerText);
}
std::pair<std::string, std::string> questionGenerator::generateDivide() {
	int quotent = getRand(10, 30) * getPlMn();
	int divisor = getRand(10, 30) * getPlMn();
	int dividend = quotent * divisor;

	std::string questionText = "What is the solution to this equation?\n\n"; 
	questionText.append(std::to_string(dividend) + " ÷ " + std::to_string(divisor) + " = ?");
	std::string answerText = std::to_string(quotent);

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

	std::string questionText = "What is the resulting simplified fraction from this multiplication?\n\n";
	questionText.append(std::to_string(numerator1) + "/" + std::to_string(denominator1) + " × " + std::to_string(numerator2) + "/" + std::to_string(denominator2));
	std::string answerText = denominatorAnswer == 1 ? std::to_string(numeratorAnswer) : std::to_string(numeratorAnswer) + "/" + std::to_string(denominatorAnswer);

	return std::make_pair(questionText, answerText);
}
std::pair<std::string, std::string> questionGenerator::generateFunctions() {
	int coeffx = getRand(2, 40) * getPlMn();
	int valuex = getRand(2, 20) * getPlMn();
	int valuec = getRand(5, 40) * getPlMn();

	int answer = coeffx * valuex + valuec;

	std::string questionText = "What is the value of x that solves this equation?\n\n";
	questionText.append(std::to_string(coeffx) + "x + " + std::to_string(valuec) + " = " + std::to_string(answer));
	std::string answerText = std::to_string(valuex);
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

	bool getValueX = getBool();

	std::string questionText = "What is the value of " + std::string(getValueX ? "x" : "y") + " that satisfies the following simultaneous \nequations?\n\n";
	questionText.append(std::to_string(coeffx_1) + "x + " + std::to_string(coeffy_1) + "y = " + std::to_string(answer1) + "\n");
	questionText.append(std::to_string(coeffx_2) + "x + " + std::to_string(coeffy_2) + "y = " + std::to_string(answer2) + "\n");
	std::string answerText = std::to_string(getValueX ? valuex : valuey);

	return std::make_pair(questionText, answerText);
}