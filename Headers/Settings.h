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
	static std::map<std::string, bool> questionSettings;
	static bool volumeMute;
	static int volumePercent;
	void initSettings();
	void loadSettingsFromFile(std::string);
	void generateSettingsFile();
	std::string enumToString(questionTypes);
	questionTypes stringToEnum(std::string);

};