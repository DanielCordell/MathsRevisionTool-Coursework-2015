#pragma once
#include <fstream>
#include <map>

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

class Settings {
private:
	std::fstream settingsFile;
public:
	Settings();
	~Settings();
	static std::map<questionTypes, bool> questionSettings;
	static bool volumeMute;
	static int volumePercent;
	static int highScore;
	void initSettings();
	void loadSettingsFromFile(std::string);
	void generateSettingsFile();
	questionTypes stringToEnum(std::string);

};