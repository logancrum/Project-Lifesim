#pragma once
#include <location.h>

class Town: public Location {
public:
	Town();
	~Town();

	void setTownAuxScreens(std::string, std::string, std::string);

	void printBlacksmith();
	void printGrocer();
	void printTavern();

private:

	std::vector<std::string> townBlacksmithScreen;
	std::vector<std::string> townGrocerScreen;
	std::vector<std::string> townTavernScreen;
	
};



