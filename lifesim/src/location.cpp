#include <location.h>

void Location::enterLocation(Player set) {
	system("CLS");
	std::cout << "You arrive at " << getLocationName() << std::endl;
	printHub();
}

void Location::printHub() {
	for (int i = 0; i < centralHub.size(); i++) {
		std::cout << centralHub.at(i) << std::endl;
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

Location::Location() {
	locationX = 0;
	locationY = 0;
}

Location::~Location() {

}
