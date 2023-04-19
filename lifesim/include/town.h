#pragma once
#include <location.h>

class Town: public Location {
public:
	Town(std::string nameArg, int xArg, int yArg, 
		std::string mainScreenArg, std::string aux1Arg, std::string aux2Arg, std::string aux3Arg);
	Town(std::string nameArg, int xArg, int yArg,
		std::string mainScreenArg, std::string aux1Arg, std::string aux2Arg, std::string aux3Arg, std::string aux4Arg);

	void setTownAuxScreens(std::string, std::string, std::string);
	void setTownAuxScreens(std::string, std::string, std::string, std::string);

	std::vector<std::string> getTownAuxScreens();

	std::shared_ptr<Inventory> getBlacksmithInv() { return blacksmithInventory; }
	std::shared_ptr<Inventory> getGrocerInv() { return grocerInventory; }
	std::shared_ptr<Inventory> getTavernInv() { return tavernInventory; }
	std::shared_ptr<Inventory> getAux4Inv() { return aux4Inventory; }

	void setBlacksmithInv(std::shared_ptr<Inventory> invArg) { blacksmithInventory = invArg; }
	void setGrocerInv(std::shared_ptr<Inventory> invArg) { grocerInventory = invArg; }
	void setTavernInv(std::shared_ptr<Inventory> invArg) {  tavernInventory = invArg; }
	void setAux4Inv(std::shared_ptr<Inventory> invArg) { aux4Inventory = invArg; }

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

	std::shared_ptr<Inventory> blacksmithInventory;
	std::shared_ptr<Inventory> grocerInventory;
	std::shared_ptr<Inventory> tavernInventory;
	std::shared_ptr<Inventory> aux4Inventory;

};



