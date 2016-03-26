#include "Headers/Settings.h"
#include <iostream>
#include <sstream>
#include <Windows.h>

int Settings::highScore;
int Settings::volumePercent;
bool Settings::volumeMute;
std::map<questionTypes, bool> Settings::questionSettings;

Settings::Settings() {
	settingsFile = std::fstream("Settings/settings.txt");

	questionSettings.insert(std::make_pair(questionTypes::add, true));
	questionSettings.insert(std::make_pair(questionTypes::sub, true));
	questionSettings.insert(std::make_pair(questionTypes::dvd, true));
	questionSettings.insert(std::make_pair(questionTypes::mlt, true));
	questionSettings.insert(std::make_pair(questionTypes::fns, true));
	questionSettings.insert(std::make_pair(questionTypes::mfr, true));
	questionSettings.insert(std::make_pair(questionTypes::qdr, true));
	questionSettings.insert(std::make_pair(questionTypes::sim, true));
}

Settings::~Settings() {
	//Deletes current settings and saves new settings
	std::remove("Settings/settings.txt");
	settingsFile.open("Settings/settings.txt", std::fstream::out);

	settingsFile << "// Volume Settings // \n";
	settingsFile << "volPer:" << Settings::volumePercent << "\n";
	settingsFile << "volMut:" << Settings::volumeMute << "\n";
	settingsFile << "hghScr:" << Settings::highScore << "\n";
	settingsFile << "// Question Settings // \n";
	settingsFile << "qstAdd:" << questionSettings[questionTypes::add] << "\n";
	settingsFile << "qstSub:" << questionSettings[questionTypes::sub] << "\n";
	settingsFile << "qstMlt:" << questionSettings[questionTypes::mlt] << "\n";
	settingsFile << "qstDvd:" << questionSettings[questionTypes::dvd] << "\n";
	settingsFile << "qstMfr:" << questionSettings[questionTypes::mfr] << "\n";
	settingsFile << "qstFns:" << questionSettings[questionTypes::fns] << "\n";
	settingsFile << "qstQdr:" << questionSettings[questionTypes::qdr] << "\n";
	settingsFile << "qstSim:" << questionSettings[questionTypes::sim] << "\n";
	settingsFile << "// End of Settings //";
	settingsFile.close();
}

void Settings::generateSettingsFile() {
	CreateDirectory("Settings", 0);
	settingsFile.open("Settings/settings.txt", std::fstream::out);
	settingsFile << "// Volume Settings // \n";
	settingsFile << "volPer:50\n";
	settingsFile << "volMut:0\n\n";
	settingsFile << "hghScr:0";
	settingsFile << "// Question Settings // \n";
	settingsFile << "qstAdd:1\n";
	settingsFile << "qstSub:1\n";
	settingsFile << "qstMlt:1\n";
	settingsFile << "qstDvd:1\n";
	settingsFile << "qstMfr:1\n";
	settingsFile << "qstFns:1\n";
	settingsFile << "qstQdr:1\n";
	settingsFile << "qstSim:1\n";
	settingsFile << "// End of Settings //";

	settingsFile.close();
}

void Settings::loadSettingsFromFile(std::string settingsLine) {
	// Best way I can do this in limited time scale

	// Split the setting into it's name and its value
	std::string settingName = settingsLine.substr(0, 6);
	int settingValue;
	std::istringstream buffer(settingsLine.substr(7));
	buffer >> settingValue;

	std::cout << "Loading Setting: " << settingsLine << " into " << settingName << " With Value " << settingValue << "\n";

	// If the setting is volume level
	if (settingName == "volPer") {
		volumePercent = settingValue;
	}

	// If the setting is volume muted
	else if (settingName == "volMut") {
		volumeMute = settingValue;
	}

	else if (settingName == "hghScr") {
		highScore = settingValue;
	}
	// If the setting describes a question being active or not
	else if (questionSettings.find(stringToEnum(settingName)) != questionSettings.end()) {
		questionSettings[stringToEnum(settingName)] = settingValue;
	}

	else {
		std::cout << "Settings file contains illegal characters:" << settingsLine << "\n" << "Ignoring...\n\n";
	}
}

void Settings::initSettings() {
	//If the file does not exist
	if (!settingsFile.good()) {
		//Generate Settings File
		std::cout << "Settings File Does Not Exist... \n";
		std::cout << "Generating Settings File... \n\n";

		//Creates the file and loads the default settings
		generateSettingsFile();
	}

	else {
		std::cout << "Settings File Exists... \n\n";
		settingsFile.close();
	}

	settingsFile.open("Settings/settings.txt", std::fstream::in);
	// Read the file line by line
	std::string settingsLine;
	while (std::getline(settingsFile, settingsLine)) {
		// If the line loaded from the file is not blank and is not a comment then load that setting
		if (settingsLine.length() != 0) {
			if (settingsLine[0] != '/') {
				loadSettingsFromFile(settingsLine);
			}
		}
	}
	settingsFile.close();
}

questionTypes Settings::stringToEnum(std::string questionString) {
	if (questionString == "qstAdd")			return questionTypes::add;
	else if (questionString == "qstSub")	return questionTypes::sub;
	else if (questionString == "qstMlt")	return questionTypes::mlt;
	else if (questionString == "qstDvd")	return questionTypes::dvd;
	else if (questionString == "qstFns")	return questionTypes::fns;
	else if (questionString == "qstMfr")	return questionTypes::mfr;
	else if (questionString == "qstQdr")	return questionTypes::qdr;
	else if (questionString == "qstSim")	return questionTypes::sim;
	else									return questionTypes::add; //Should never happen
}