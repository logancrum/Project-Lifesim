#pragma once
#include <location.h>

class Town: public Location {
public:
	Town();
	~Town();

	void setTownAuxScreens(std::string, std::string, std::string);
	void setTownAuxScreens(std::string, std::string, std::string, std::string);

	std::vector<std::string> getTownAuxScreens();

	void printBlacksmith();
	void printGrocer();
	void printTavern();
	void printAux4();

private:

	std::vector<std::string> townBlacksmithScreen;
	std::vector<std::string> townGrocerScreen;
	std::vector<std::string> townTavernScreen;
	std::vector<std::string> aux4Screen;

	std::vector<std::string> allTownAuxScreens;

	Inventory blacksmithInventory;
	Inventory grocerInventory;
	Inventory tavernInventory;
	Inventory aux4Inventory;

};



