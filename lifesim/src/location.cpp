#include <location.h>


void Location::setScreen(std::string tempFileLoc) {

	std::ifstream tempFile(fs::current_path().string() + tempFileLoc);

	std::vector<std::string> tempScreen;
	std::string tempScreenLine;

	while (std::getline(tempFile, tempScreenLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(tempScreenLine);
		std::getline(issSprite, tempScreenLine);
		tempScreen.push_back(tempScreenLine);
		// TEST Print the extracted data to the console
		// std::cout << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << ", s4: " << s4 << std::endl;
	}
	tempFile.close();
	screen = tempScreen;
	tempScreen.clear();
}


void Location::printScreen() {
	for (int i = 0; i < screen.size(); i++) {
		std::cout << screen.at(i) << std::endl;
	}
}

std::string Location::getLocationName() {
	return locationName;
}

int Location::getLocationX() {
	return locationX;
}

int Location::getLocationY() {
	return locationY;
}

std::vector<Location> Location::getAuxLocations() {
	return auxLocations;
}

void Location::setLocationX(int locX) {
	locationX = locX;
}

void Location::setLocationY(int locY) {
	locationY = locY;
}

void Location::addAuxLoc(Location locArg) {
	auxLocations.emplace_back(locArg);
}


Location::Location() {
	locationX = 0;
	locationY = 0;
}

Location::~Location() {

}
