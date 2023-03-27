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



Town::Town()
{
}

Town::~Town()
{
}