#pragma once
#include <fstream>
#include <map>

// An enumeration which is used to refer to each specific topic/type of question.
enum class questionTypes {
	add,
	sub,
	mlt,
	dvd,
	mfr,
	fns,
	qdr,
	sim
};

// A class that stores all of the user's current settings.
class Settings {
private:	// Private Member Objects
	// File Input/Output class, needed to save/load settings from a settings file.
	std::fstream settingsFile;
public:		// Public Member Objects
	// Settings constructor, runs automatically when an instance of the settings class is created.
	Settings();
	// Settings destructor, runs automatically when an instance of the settings class is destroyed (out of scope).
	~Settings();
	// A mapping of the questionType enumeration to a boolean value. This saves all of the settings that refer to weather a
	// topic is enabled or disabled for question generation.
	static std::map<questionTypes, bool> questionSettings;
	// A boolean value which detects if the volume is muted or not.
	static bool volumeMute;
	// An integer value which specifies the percentage volume the game is currently using (0-100).
	static int volumePercent;
	// An integer value which stores the current high score.
	static int highScore;
	// Initialises the settings class, by creating a settings file if one does not exist already, and loading all settings from
	// the file into the class.
	void initSettings();
	// Loads a specific setting from the string argument of the function into the member variable that stores that specific
	// setting in the class.
	void loadSettingsFromFile(std::string);
	// Generates a settings file with the default values.
	void generateSettingsFile();
	// Converts the identifier found in the settings file into the questionTypes enum, so each setting
	// can be referred to programatically.
	questionTypes stringToEnum(std::string);
};
