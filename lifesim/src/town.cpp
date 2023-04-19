#include <town.h>

void Town::setTownAuxScreens(std::string aux1, std::string aux2, std::string aux3) {
	std::ifstream tempFile1(fs::current_path().string() + aux1);

	std::vector<std::string> tempScreen;
	std::string tempScreenLine;

	while (std::getline(tempFile1, tempScreenLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(tempScreenLine);
		std::getline(issSprite, tempScreenLine);
		tempScreen.push_back(tempScreenLine);
	}
	tempFile1.close();
	townBlacksmithScreen = tempScreen;
	tempScreen.clear();

	std::ifstream tempFile2(fs::current_path().string() + aux2);

	while (std::getline(tempFile2, tempScreenLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(tempScreenLine);
		std::getline(issSprite, tempScreenLine);
		tempScreen.push_back(tempScreenLine);
	}
	tempFile2.close();
	townGrocerScreen = tempScreen;
	tempScreen.clear();

	std::ifstream tempFile3(fs::current_path().string() + aux3);

	while (std::getline(tempFile3, tempScreenLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(tempScreenLine);
		std::getline(issSprite, tempScreenLine);
		tempScreen.push_back(tempScreenLine);
	}
	tempFile3.close();
	townTavernScreen = tempScreen;
	tempScreen.clear();


	// Add screens to vector of screens
	allTownAuxScreens.emplace_back(aux1);
	allTownAuxScreens.emplace_back(aux2);
	allTownAuxScreens.emplace_back(aux3);
}

void Town::setTownAuxScreens(std::string aux1, std::string aux2, std::string aux3, std::string aux4) {
	std::ifstream tempFile1(fs::current_path().string() + aux1);

	std::vector<std::string> tempScreen;
	std::string tempScreenLine;

	while (std::getline(tempFile1, tempScreenLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(tempScreenLine);
		std::getline(issSprite, tempScreenLine);
		tempScreen.push_back(tempScreenLine);
	}
	tempFile1.close();
	townBlacksmithScreen = tempScreen;
	tempScreen.clear();

	std::ifstream tempFile2(fs::current_path().string() + aux2);

	while (std::getline(tempFile2, tempScreenLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(tempScreenLine);
		std::getline(issSprite, tempScreenLine);
		tempScreen.push_back(tempScreenLine);
	}
	tempFile2.close();
	townGrocerScreen = tempScreen;
	tempScreen.clear();

	std::ifstream tempFile3(fs::current_path().string() + aux3);

	while (std::getline(tempFile3, tempScreenLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(tempScreenLine);
		std::getline(issSprite, tempScreenLine);
		tempScreen.push_back(tempScreenLine);
	}
	tempFile3.close();
	townTavernScreen = tempScreen;
	tempScreen.clear();

	std::ifstream tempFile4(fs::current_path().string() + aux4);

	while (std::getline(tempFile4, tempScreenLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(tempScreenLine);
		std::getline(issSprite, tempScreenLine);
		tempScreen.push_back(tempScreenLine);
	}
	tempFile4.close();
	aux4Screen = tempScreen;
	tempScreen.clear();

	// Add screens to vector of screens
	allTownAuxScreens.emplace_back(aux1);
	allTownAuxScreens.emplace_back(aux2);
	allTownAuxScreens.emplace_back(aux3);
	allTownAuxScreens.emplace_back(aux4);
}

std::vector<std::string> Town::getTownAuxScreens() {
	return allTownAuxScreens;
}

void Town::printBlacksmith() {
	for (int i = 0; i < townBlacksmithScreen.size(); i++) {
		std::cout << townBlacksmithScreen.at(i) << std::endl;
	}
}

void Town::printGrocer() {
	for (int i = 0; i < townGrocerScreen.size(); i++) {
		std::cout << townGrocerScreen.at(i) << std::endl;
	}
}

void Town::printTavern() {
	for (int i = 0; i < townTavernScreen.size(); i++) {
		std::cout << townTavernScreen.at(i) << std::endl;
	}
}
void Town::printAux4() {
	for (int i = 0; i < aux4Screen.size(); i++) {
		std::cout << aux4Screen.at(i) << std::endl;
	}
}

Town::Town(std::string nameArg, int xArg, int yArg,
	std::string mainScreenArg, std::string aux1Arg, std::string aux2Arg, std::string aux3Arg) {
	
	// Set the town location
	setLocationX(xArg);
	setLocationY(yArg);

	setLocationName(nameArg);

	// Set all Screens
	setScreen(mainScreenArg);
	setTownAuxScreens(aux1Arg, aux2Arg, aux3Arg);


	blacksmithInventory = std::make_shared<Inventory>(1000, 100, 10, 10, 1000, 1, 2, "Blacksmith", false);
	grocerInventory = std::make_shared<Inventory>(1000, 100, 10, 10, 1000, 1, 2, "Grocer", false);
	tavernInventory = std::make_shared<Inventory>(1000, 100, 10, 10, 1000, 1, 2, "Tavern", false);
	aux4Inventory = std::make_shared<Inventory>(1000, 100, 10, 10, 1000, 1, 2, "Mysterious Merchant", false);
}

Town::Town(std::string nameArg, int xArg, int yArg,
	std::string mainScreenArg, std::string aux1Arg, std::string aux2Arg, std::string aux3Arg, std::string aux4Arg) {

	// Set the town location
	setLocationX(xArg);
	setLocationY(yArg);

	setLocationName(nameArg);

	// Set all Screens
	setScreen(mainScreenArg);
	setTownAuxScreens(aux1Arg, aux2Arg, aux3Arg, aux4Arg);

	blacksmithInventory = std::make_shared<Inventory>(1000, 1000, 100, 100, 100, 1, 2, "Blacksmith", false);
	grocerInventory = std::make_shared<Inventory>(1000, 1000, 100, 100, 100, 1, 2, "Grocer", false);
	tavernInventory = std::make_shared<Inventory>(1000, 1000, 100, 100, 100, 1, 2, "Tavern", false);
	aux4Inventory = std::make_shared<Inventory>(1000, 1000, 100, 100, 100, 1, 2, "Mysterious Merchant", false);

}
