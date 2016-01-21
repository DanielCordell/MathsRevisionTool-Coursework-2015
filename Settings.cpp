#include "Headers/Settings.h"
#include <iostream>
#include <sstream>

int Settings::volumePercent;
bool Settings::volumeMute;
std::map<std::string, bool> Settings::questionSettings;


Settings::Settings() {
	settingsFile = std::fstream("Settings/settings.txt");

	questionSettings["qstAdd"] = true;
	questionSettings["qstSub"] = true;
	questionSettings["qstMlt"] = true;
	questionSettings["qstDvd"] = true;
	questionSettings["qstMfr"] = true;
	questionSettings["qstFns"] = true;
	questionSettings["qstQdr"] = true;
	questionSettings["qstSim"] = true;
}

Settings::~Settings() {
	//Deletes current settings and saves new settings
	std::remove("Settings/settings.txt");
	settingsFile.open("Settings/settings.txt", std::fstream::out);

	settingsFile << "// Volume Settings // \n";
	settingsFile << "volPer:" << Settings::volumePercent << "\n";
	std::cout << Settings::volumePercent << "\n";
	std::cout << Settings::volumeMute << "\n";
	settingsFile << "volMut:" << Settings::volumeMute << "\n";
	settingsFile << "// Question Settings // \n";
	settingsFile << "qstAdd:" << questionSettings["qstAdd"] << "\n";
	settingsFile << "qstSub:" << questionSettings["qstSub"] << "\n";
	settingsFile << "qstMlt:" << questionSettings["qstMlt"] << "\n";
	settingsFile << "qstDvd:" << questionSettings["qstDvd"] << "\n";
	settingsFile << "qstMfr:" << questionSettings["qstMfr"] << "\n";
	settingsFile << "qstFns:" << questionSettings["qstFns"] << "\n";
	settingsFile << "qstQdr:" << questionSettings["qstQdr"] << "\n";
	settingsFile << "qstSim:" << questionSettings["qstSim"] << "\n";
	settingsFile << "// End of Settings //";
	settingsFile.close();
}

void Settings::generateSettingsFile() {
	settingsFile.open("Settings/settings.txt", std::fstream::out);
	settingsFile << "// Volume Settings // \n";
	settingsFile << "volPer:50\n";
	settingsFile << "volMut:0\n\n";
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

	// If the setting describes a question being active or not
	else if (questionSettings.find(settingName) != questionSettings.end()) {
		questionSettings[settingName] = settingValue;
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

std::string Settings::enumToString(questionTypes questionEnum) {

	switch (questionEnum) {
	case questionTypes::add:
		return "qstAdd";
	case questionTypes::sub:
		return "qstSub";
	case questionTypes::mlt:
		return "qstMlt";
	case questionTypes::dvd:
		return "qstDvd";
	case questionTypes::fns:
		return "qstFns";
	case questionTypes::mfr:
		return "qstMfr";
	case questionTypes::qdr:
		return "qstQdr";
	case questionTypes::sim:
		return "qstSim";
	default:
		return "qstAdd"; //Should never happen
	}
}