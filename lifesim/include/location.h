#pragma once
#include <vector>
#include <iostream>

#include <player.h>

class Location {
public:
	Location();
	~Location();

	void enterLocation(Player);

	// Printers
	void printHub();
	

	// Getters

	std::string getLocationName();

	int getLocationX();
	int getLocationY();

private:

	std::string locationName;

	// Store the main 'sprite'
	std::vector<std::string> centralHub;
	// Store any attached locations which can be accessed via the main hub
	std::vector<Location> auxLocations;

	int locationX;
	int locationY;
};
