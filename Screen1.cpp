#include "Headers/Screen1.h"
#include "Headers/Constants.h"
#include <iostream>

//Settings Screen

bool screen1::Init() {
	//Loading fonts and textures for this screen
	if (!font.loadFromFile("Resources/font.ttf")
		|| !backgroundTexture.loadFromFile("Resources/backgroundSettings.png")
		|| !buttonCrossTexture.loadFromFile("Resources/SettingsCross.png")
		|| !buttonBackToMenu.loadTexture("Resources/buttonReturn.png")) {
		return false;
	}

	//Initialize Background
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(WINDOW_X / backgroundSprite.getLocalBounds().width, WINDOW_Y / backgroundSprite.getLocalBounds().height);

	//Initializing Text Values
	screenTitle = sf::Text("Settings", font, 50);
	screenTitleVolume = sf::Text("Volume Options", font, 40);
	screenTitleQuestions = sf::Text("Enable / Disable Questions", font, 40);
	volumeText = sf::Text("Volume", font, 28);
	volumeText.setColor(sf::Color::Black);
	muteText = sf::Text("Mute", font, 28);
	muteText.setColor(sf::Color::Black);
	questionTextAdd = sf::Text("Addition", font, 28);
	questionTextAdd.setColor(sf::Color::Black);
	questionTextSubtract = sf::Text("Subtraction", font, 28);
	questionTextSubtract.setColor(sf::Color::Black);
	questionTextMultiply = sf::Text("Multiplication", font, 28);
	questionTextMultiply.setColor(sf::Color::Black);
	questionTextDivide = sf::Text("Division", font, 28);
	questionTextDivide.setColor(sf::Color::Black);
	questionTextMultiplyFraction = sf::Text("   Fraction\nMultiplication", font, 28);
	questionTextMultiplyFraction.setColor(sf::Color::Black);
	questionTextQuadratic = sf::Text("Quadratics", font, 28);
	questionTextQuadratic.setColor(sf::Color::Black);
	questionTextSimultaneous = sf::Text("Simultaneous\n  Equations", font, 28);
	questionTextSimultaneous.setColor(sf::Color::Black);
	questionTextFunctions = sf::Text("Functions", font, 28);
	questionTextFunctions.setColor(sf::Color::Black);

	//Initializing Volume Slider
	volumeSliderBack = sf::VertexArray(sf::Quads, 4);
	volumeSliderBack[0] = sf::Vertex(sf::Vector2f(12 * WINDOW_X / 64.0f, 22 * WINDOW_Y / 64.0f), sf::Color::Cyan);
	volumeSliderBack[1] = sf::Vertex(sf::Vector2f(24 * WINDOW_X / 64.0f, 22 * WINDOW_Y / 64.0f), sf::Color(1, 102, 144));
	volumeSliderBack[2] = sf::Vertex(sf::Vector2f(24 * WINDOW_X / 64.0f, 18 * WINDOW_Y / 64.0f), sf::Color(1, 102, 144));
	volumeSliderBack[3] = sf::Vertex(sf::Vector2f(12 * WINDOW_X / 64.0f, 21 * WINDOW_Y / 64.0f), sf::Color::Cyan);

	sf::FloatRect volSldBackRect = volumeSliderBack.getBounds();
	volumeSlider.setSize(sf::Vector2f(WINDOW_X / 128.0f, 5 * volSldBackRect.height / 4.0f));
	sf::FloatRect volumeSliderRect = volumeSlider.getLocalBounds();
	volumeSlider.setOrigin(sf::Vector2f(volumeSliderRect.width / 2.0f, volumeSliderRect.height));
	volumeSlider.setPosition((volSldBackRect.left + Settings::volumePercent / 100.0f * (volSldBackRect.width)), volSldBackRect.height + volSldBackRect.top);

	volumeText.setOrigin(volumeText.getLocalBounds().width / 2.0f, volumeText.getLocalBounds().height / 2.0f);
	volumeText.setPosition(18 * WINDOW_X / 64.0f, 14 * WINDOW_Y / 64.0f);

	//Initializing Mute Button
	muteButtonBack.setSize(sf::Vector2f(WINDOW_X / 30.0f, WINDOW_X / 30.0f)); // Using WINDOW_X for both x and y, as it needs to be a square
	muteButtonBack.setOrigin(sf::Vector2f(muteButtonBack.getLocalBounds().width / 2.0f, muteButtonBack.getLocalBounds().height / 2.0f));
	muteButtonBack.setPosition((WINDOW_X - volSldBackRect.left - volSldBackRect.width / 2.0f), volSldBackRect.height / 2.0f + volSldBackRect.top);
	muteButtonBack.setOutlineColor(sf::Color::Black);
	muteButtonBack.setOutlineThickness(2);

	muteButtonCrossSprite.setTexture(buttonCrossTexture);
	muteButtonCrossSprite.setScale(muteButtonBack.getLocalBounds().width / muteButtonCrossSprite.getLocalBounds().width, muteButtonBack.getLocalBounds().height / muteButtonCrossSprite.getLocalBounds().height);
	muteButtonCrossSprite.setOrigin(muteButtonCrossSprite.getLocalBounds().width / 2, muteButtonCrossSprite.getLocalBounds().height / 2);
	muteButtonCrossSprite.setPosition(muteButtonBack.getPosition());
	muteButtonCrossSprite.setColor(sf::Color(sf::Color::Transparent));

	muteText.setOrigin(muteText.getLocalBounds().width / 2.0f, muteText.getLocalBounds().height / 2.0f);
	muteText.setPosition(WINDOW_X - volumeText.getPosition().x, volumeText.getPosition().y);

	//Initializing Question Buttons
	questionButtonAddBack.setSize(muteButtonBack.getSize());
	questionButtonAddBack.setOrigin(muteButtonBack.getOrigin());
	questionButtonAddBack.setPosition(muteButtonBack.getPosition().x, 18 * WINDOW_Y / 32.0f);
	questionButtonAddBack.setOutlineColor(sf::Color::Black);
	questionButtonAddBack.setOutlineThickness(2);
	questionButtonAddSprite.setTexture(buttonCrossTexture);
	questionButtonAddSprite.setScale(muteButtonCrossSprite.getScale());
	questionButtonAddSprite.setOrigin(muteButtonCrossSprite.getOrigin());
	questionButtonAddSprite.setPosition(questionButtonAddBack.getPosition());
	questionTextAdd.setOrigin(questionTextAdd.getLocalBounds().width / 2, questionTextAdd.getLocalBounds().height / 2);
	questionTextAdd.setPosition(questionButtonAddBack.getPosition().x, 15 * WINDOW_Y / 32.0f);

	questionButtonSubtractBack.setSize(muteButtonBack.getSize());
	questionButtonSubtractBack.setOrigin(muteButtonBack.getOrigin());
	questionButtonSubtractBack.setPosition(muteButtonBack.getPosition().x - 4 * muteButtonBack.getLocalBounds().width, 18 * WINDOW_Y / 32.0f);
	questionButtonSubtractBack.setOutlineColor(sf::Color::Black);
	questionButtonSubtractBack.setOutlineThickness(2);
	questionButtonSubtractSprite.setTexture(buttonCrossTexture);
	questionButtonSubtractSprite.setScale(muteButtonCrossSprite.getScale());
	questionButtonSubtractSprite.setOrigin(muteButtonCrossSprite.getOrigin());
	questionButtonSubtractSprite.setPosition(questionButtonSubtractBack.getPosition());
	questionTextSubtract.setOrigin(questionTextSubtract.getLocalBounds().width / 2, questionTextSubtract.getLocalBounds().height / 2);
	questionTextSubtract.setPosition(questionButtonSubtractBack.getPosition().x, 15 * WINDOW_Y / 32.0f);

	questionButtonDivideBack.setSize(muteButtonBack.getSize());
	questionButtonDivideBack.setOrigin(muteButtonBack.getOrigin());
	questionButtonDivideBack.setPosition(muteButtonBack.getPosition().x - 8 * muteButtonBack.getLocalBounds().width, 18 * WINDOW_Y / 32.0f);
	questionButtonDivideBack.setOutlineColor(sf::Color::Black);
	questionButtonDivideBack.setOutlineThickness(2);
	questionButtonDivideSprite.setTexture(buttonCrossTexture);
	questionButtonDivideSprite.setScale(muteButtonCrossSprite.getScale());
	questionButtonDivideSprite.setOrigin(muteButtonCrossSprite.getOrigin());
	questionButtonDivideSprite.setPosition(questionButtonDivideBack.getPosition());
	questionTextDivide.setOrigin(questionTextDivide.getLocalBounds().width / 2, questionTextDivide.getLocalBounds().height / 2);
	questionTextDivide.setPosition(questionButtonDivideBack.getPosition().x, 15 * WINDOW_Y / 32.0f);

	questionButtonFunctionsBack.setSize(muteButtonBack.getSize());
	questionButtonFunctionsBack.setOrigin(muteButtonBack.getOrigin());
	questionButtonFunctionsBack.setPosition(muteButtonBack.getPosition().x - 16 * muteButtonBack.getLocalBounds().width, 18 * WINDOW_Y / 32.0f);
	questionButtonFunctionsBack.setOutlineColor(sf::Color::Black);
	questionButtonFunctionsBack.setOutlineThickness(2);
	questionButtonFunctionsSprite.setTexture(buttonCrossTexture);
	questionButtonFunctionsSprite.setScale(muteButtonCrossSprite.getScale());
	questionButtonFunctionsSprite.setOrigin(muteButtonCrossSprite.getOrigin());
	questionButtonFunctionsSprite.setPosition(questionButtonFunctionsBack.getPosition());
	questionTextFunctions.setOrigin(questionTextFunctions.getLocalBounds().width / 2, questionTextFunctions.getLocalBounds().height / 2);
	questionTextFunctions.setPosition(questionButtonFunctionsBack.getPosition().x, 15 * WINDOW_Y / 32.0f);

	questionButtonMultiplyBack.setSize(muteButtonBack.getSize());
	questionButtonMultiplyBack.setOrigin(muteButtonBack.getOrigin());
	questionButtonMultiplyBack.setPosition(muteButtonBack.getPosition().x - 12 * muteButtonBack.getLocalBounds().width, 18 * WINDOW_Y / 32.0f);
	questionButtonMultiplyBack.setOutlineColor(sf::Color::Black);
	questionButtonMultiplyBack.setOutlineThickness(2);
	questionButtonMultiplySprite.setTexture(buttonCrossTexture);
	questionButtonMultiplySprite.setScale(muteButtonCrossSprite.getScale());
	questionButtonMultiplySprite.setOrigin(muteButtonCrossSprite.getOrigin());
	questionButtonMultiplySprite.setPosition(questionButtonMultiplyBack.getPosition());
	questionTextMultiply.setOrigin(questionTextMultiply.getLocalBounds().width / 2, questionTextMultiply.getLocalBounds().height / 2);
	questionTextMultiply.setPosition(questionButtonMultiplyBack.getPosition().x, 15 * WINDOW_Y / 32.0f);
	questionButtonMultiplyFractionSprite.setTexture(buttonCrossTexture);

	questionButtonQuadraticBack.setSize(muteButtonBack.getSize());
	questionButtonQuadraticBack.setOrigin(muteButtonBack.getOrigin());
	questionButtonQuadraticBack.setPosition(muteButtonBack.getPosition().x + 4 * muteButtonBack.getLocalBounds().width, 18 * WINDOW_Y / 32.0f);
	questionButtonQuadraticBack.setOutlineColor(sf::Color::Black);
	questionButtonQuadraticBack.setOutlineThickness(2);
	questionButtonQuadraticSprite.setTexture(buttonCrossTexture);
	questionButtonQuadraticSprite.setScale(muteButtonCrossSprite.getScale());
	questionButtonQuadraticSprite.setOrigin(muteButtonCrossSprite.getOrigin());
	questionButtonQuadraticSprite.setPosition(questionButtonQuadraticBack.getPosition());
	questionTextQuadratic.setOrigin(questionTextQuadratic.getLocalBounds().width / 2, questionTextQuadratic.getLocalBounds().height / 2);
	questionTextQuadratic.setPosition(questionButtonQuadraticBack.getPosition().x, 15 * WINDOW_Y / 32.0f);

	questionButtonSimultaneousBack.setSize(muteButtonBack.getSize());
	questionButtonSimultaneousBack.setOrigin(muteButtonBack.getOrigin());
	questionButtonSimultaneousBack.setPosition(muteButtonBack.getPosition().x - 4 * muteButtonBack.getLocalBounds().width, 24 * WINDOW_Y / 32.0f);
	questionButtonSimultaneousBack.setOutlineColor(sf::Color::Black);
	questionButtonSimultaneousBack.setOutlineThickness(2);
	questionButtonSimultaneousSprite.setTexture(buttonCrossTexture);
	questionButtonSimultaneousSprite.setScale(muteButtonCrossSprite.getScale());
	questionButtonSimultaneousSprite.setOrigin(muteButtonCrossSprite.getOrigin());
	questionButtonSimultaneousSprite.setPosition(questionButtonSimultaneousBack.getPosition());
	questionTextSimultaneous.setOrigin(questionTextSimultaneous.getLocalBounds().width / 2, questionTextSimultaneous.getLocalBounds().height / 2);
	questionTextSimultaneous.setPosition(questionButtonSimultaneousBack.getPosition().x, 21 * WINDOW_Y / 32.0f);

	questionButtonMultiplyFractionBack.setSize(muteButtonBack.getSize());
	questionButtonMultiplyFractionBack.setOrigin(muteButtonBack.getOrigin());
	questionButtonMultiplyFractionBack.setPosition(muteButtonBack.getPosition().x - 8 * muteButtonBack.getLocalBounds().width, 24 * WINDOW_Y / 32.0f);
	questionButtonMultiplyFractionBack.setOutlineColor(sf::Color::Black);
	questionButtonMultiplyFractionBack.setOutlineThickness(2);
	questionButtonMultiplyFractionSprite.setTexture(buttonCrossTexture);
	questionButtonMultiplyFractionSprite.setScale(muteButtonCrossSprite.getScale());
	questionButtonMultiplyFractionSprite.setOrigin(muteButtonCrossSprite.getOrigin());
	questionButtonMultiplyFractionSprite.setPosition(questionButtonMultiplyFractionBack.getPosition());
	questionTextMultiplyFraction.setOrigin(questionTextMultiplyFraction.getLocalBounds().width / 2, questionTextMultiplyFraction.getLocalBounds().height / 2);
	questionTextMultiplyFraction.setPosition(questionButtonMultiplyFractionBack.getPosition().x, 21 * WINDOW_Y / 32.0f);

	//Positioning Titles and Return Button
	sf::FloatRect textRect = screenTitle.getLocalBounds();
	screenTitle.setOrigin(textRect.width / 2, textRect.height / 2);
	screenTitle.setPosition(WINDOW_X / 2.0f, WINDOW_Y / 16.0f);
	screenTitle.setColor(sf::Color::Black);

	textRect = screenTitleVolume.getLocalBounds();
	screenTitleVolume.setOrigin(textRect.width / 2, textRect.height / 2);
	screenTitleVolume.setPosition(WINDOW_X / 2.0f, 3 * WINDOW_Y / 16.0f);
	screenTitleVolume.setColor(sf::Color::Black);

	textRect = screenTitleQuestions.getLocalBounds();
	screenTitleQuestions.setOrigin(textRect.width / 2, textRect.height / 2);
	screenTitleQuestions.setPosition(WINDOW_X / 2.0f, 13 * WINDOW_Y / 32.0f);
	screenTitleQuestions.setColor(sf::Color::Black);

	buttonBackToMenu.InitSprite();
	textRect = buttonBackToMenu.sprite.getLocalBounds();
	buttonBackToMenu.sprite.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	buttonBackToMenu.sprite.setPosition(WINDOW_X - 150, WINDOW_Y - 100);

	//Misc
	canVolumeMove = false;
	return true;
}

int screen1::Events(sf::RenderWindow & window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		bool escapePressed = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
		if (event.type == sf::Event::Closed || escapePressed) {
			return screenMainMenu;
		}
		// If Mouse Pressed
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(sf::Mouse::getPosition(window));

				if (buttonBackToMenu.sprite.getGlobalBounds().contains(mousePos)) {
					buttonClickSound.play();
					return screenMainMenu;
				}
				else if (volumeSliderBack.getBounds().contains(mousePos)) {
					canVolumeMove = true;
					Settings::volumePercent = int((mousePos.x - volumeSliderBack[0].position.x) * 100 / volumeSliderBack.getBounds().width);
					buttonClickSound.play();
				}

				else if (muteButtonBack.getGlobalBounds().contains(mousePos)) {
					Settings::volumeMute = !Settings::volumeMute;
					if (Settings::volumeMute) Settings::volumePercent = 0;
					else Settings::volumePercent = 50;
					buttonClickSound.play();
				}

				else if (questionButtonAddBack.getGlobalBounds().contains(mousePos)) {
					Settings::questionSettings[questionTypes::add] = !Settings::questionSettings[questionTypes::add];
					buttonClickSound.play();
				}
				else if (questionButtonSubtractBack.getGlobalBounds().contains(mousePos)) {
					Settings::questionSettings[questionTypes::sub] = !Settings::questionSettings[questionTypes::sub];
					buttonClickSound.play();
				}
				else if (questionButtonMultiplyBack.getGlobalBounds().contains(mousePos)) {
					Settings::questionSettings[questionTypes::mlt] = !Settings::questionSettings[questionTypes::mlt];
					buttonClickSound.play();
				}
				else if (questionButtonDivideBack.getGlobalBounds().contains(mousePos)) {
					Settings::questionSettings[questionTypes::dvd] = !Settings::questionSettings[questionTypes::dvd];
					buttonClickSound.play();
				}
				else if (questionButtonMultiplyFractionBack.getGlobalBounds().contains(mousePos)) {
					Settings::questionSettings[questionTypes::mfr] = !Settings::questionSettings[questionTypes::mfr];
					buttonClickSound.play();
				}
				else if (questionButtonFunctionsBack.getGlobalBounds().contains(mousePos)) {
					Settings::questionSettings[questionTypes::fns] = !Settings::questionSettings[questionTypes::fns];
					buttonClickSound.play();
				}
				else if (questionButtonQuadraticBack.getGlobalBounds().contains(mousePos)) {
					Settings::questionSettings[questionTypes::qdr] = !Settings::questionSettings[questionTypes::qdr];
					buttonClickSound.play();
				}
				else if (questionButtonSimultaneousBack.getGlobalBounds().contains(mousePos)) {
					Settings::questionSettings[questionTypes::sim] = !Settings::questionSettings[questionTypes::sim];
					buttonClickSound.play();
				}
			}
		}
		// If Mouse Moved
		else if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canVolumeMove == true) {
				int mousePosLimited = int(mousePos.x);
				if (mousePosLimited > volumeSliderBack.getBounds().left + volumeSliderBack.getBounds().width) {
					mousePosLimited = int(volumeSliderBack.getBounds().left + volumeSliderBack.getBounds().width);
				}
				else if (mousePosLimited < volumeSliderBack.getBounds().left) {
					mousePosLimited = int(volumeSliderBack.getBounds().left);
				}
				Settings::volumePercent = int((mousePosLimited - volumeSliderBack[0].position.x) * 100.0f / volumeSliderBack.getBounds().width);
				if (Settings::volumePercent == 0) {
					Settings::volumeMute = true;
				}
				else {
					Settings::volumeMute = false;
				}
			}
			buttonHighlightDetect(mousePos, buttonBackToMenu.sprite);
			buttonHighlightDetect(mousePos, muteButtonBack);
			buttonHighlightDetect(mousePos, questionButtonAddBack);
			buttonHighlightDetect(mousePos, questionButtonDivideBack);
			buttonHighlightDetect(mousePos, questionButtonFunctionsBack);
			buttonHighlightDetect(mousePos, questionButtonMultiplyFractionBack);
			buttonHighlightDetect(mousePos, questionButtonMultiplyBack);
			buttonHighlightDetect(mousePos, questionButtonQuadraticBack);
			buttonHighlightDetect(mousePos, questionButtonSimultaneousBack);
			buttonHighlightDetect(mousePos, questionButtonSubtractBack);
			buttonHighlightDetect(mousePos, volumeSlider);
		}
		else if (event.type == sf::Event::MouseButtonReleased) canVolumeMove = false;
	}
	return getCurrentScreen();
}

void screen1::Update() {
	if (canVolumeMove) {
		volumeSlider.setFillColor(sf::Color(100, 100, 100));
	}
	else {
		volumeSlider.setFillColor(sf::Color::Black);
	}

	sf::FloatRect volSldBackRect = volumeSliderBack.getBounds();
	volumeSlider.setPosition(volSldBackRect.left + volSldBackRect.width * (Settings::volumePercent / 100.0f), volumeSlider.getPosition().y);
	volumeSlider.setScale(1, Settings::volumePercent / 150.0f + 1 / 3.0f);

	if (!Settings::volumeMute)					muteButtonCrossSprite.setColor(sf::Color::Transparent);
	else										muteButtonCrossSprite.setColor(sf::Color::Black);
	if (!Settings::questionSettings[questionTypes::add])	questionButtonAddSprite.setColor(sf::Color::Transparent);
	else										questionButtonAddSprite.setColor(sf::Color::Black);
	if (!Settings::questionSettings[questionTypes::sub])	questionButtonSubtractSprite.setColor(sf::Color::Transparent);
	else										questionButtonSubtractSprite.setColor(sf::Color::Black);
	if (!Settings::questionSettings[questionTypes::mlt])	questionButtonMultiplySprite.setColor(sf::Color::Transparent);
	else										questionButtonMultiplySprite.setColor(sf::Color::Black);
	if (!Settings::questionSettings[questionTypes::dvd])	questionButtonDivideSprite.setColor(sf::Color::Transparent);
	else										questionButtonDivideSprite.setColor(sf::Color::Black);
	if (!Settings::questionSettings[questionTypes::fns])	questionButtonFunctionsSprite.setColor(sf::Color::Transparent);
	else										questionButtonFunctionsSprite.setColor(sf::Color::Black);
	if (!Settings::questionSettings[questionTypes::mfr])	questionButtonMultiplyFractionSprite.setColor(sf::Color::Transparent);
	else										questionButtonMultiplyFractionSprite.setColor(sf::Color::Black);
	if (!Settings::questionSettings[questionTypes::qdr])	questionButtonQuadraticSprite.setColor(sf::Color::Transparent);
	else										questionButtonQuadraticSprite.setColor(sf::Color::Black);
	if (!Settings::questionSettings[questionTypes::sim])	questionButtonSimultaneousSprite.setColor(sf::Color::Transparent);
	else										questionButtonSimultaneousSprite.setColor(sf::Color::Black);

	buttonClickSound.setVolume(Settings::volumePercent);
}
void screen1::Draw(sf::RenderWindow & window) {
	window.clear();
	window.draw(backgroundSprite);
	window.draw(screenTitle);
	window.draw(buttonBackToMenu.sprite);

	window.draw(screenTitleVolume);
	window.draw(volumeSliderBack);
	window.draw(volumeSlider);
	window.draw(volumeText);

	window.draw(muteButtonBack);
	window.draw(muteButtonCrossSprite);
	window.draw(muteText);

	window.draw(screenTitleQuestions);
	window.draw(questionButtonAddBack);
	window.draw(questionButtonAddSprite);
	window.draw(questionTextAdd);

	window.draw(questionButtonSubtractBack);
	window.draw(questionButtonSubtractSprite);
	window.draw(questionTextSubtract);

	window.draw(questionButtonDivideBack);
	window.draw(questionButtonDivideSprite);
	window.draw(questionTextDivide);

	window.draw(questionButtonMultiplyBack);
	window.draw(questionButtonMultiplySprite);
	window.draw(questionTextMultiply);

	window.draw(questionButtonFunctionsBack);
	window.draw(questionButtonFunctionsSprite);
	window.draw(questionTextFunctions);

	window.draw(questionButtonSimultaneousBack);
	window.draw(questionButtonSimultaneousSprite);
	window.draw(questionTextSimultaneous);

	window.draw(questionButtonQuadraticBack);
	window.draw(questionButtonQuadraticSprite);
	window.draw(questionTextQuadratic);

	window.draw(questionButtonMultiplyFractionBack);
	window.draw(questionButtonMultiplyFractionSprite);
	window.draw(questionTextMultiplyFraction);

	window.display();

	music.setVolume(Settings::volumePercent);
	std::cout << music.getVolume() << std::endl;
}

int screen1::Run(sf::RenderWindow &window) {
	sf::Clock clock;

	while (true) {
		if (clock.getElapsedTime().asMilliseconds() >= 1000.0 / 60.0) /* Framerate Limit */ {
			clock.restart();
			int nextScreen = Events(window); // What is the next screen that should be loaded
			if (nextScreen != getCurrentScreen()) return nextScreen; // Return the next screen to main
			Update();
			Draw(window);
		}
	}
}
