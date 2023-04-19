#pragma once
#include <vector>
#include <filesystem>
#include <fstream>


#include <inventory.h>

#include <conio.h> // handles keyboard input via getch()

namespace fs = std::filesystem;

class Location {
public:
	Location();
	~Location();

	// Printers
	void printScreen();
	

	// Accessors
	std::string getLocationName();

	int getLocationX();
	int getLocationY();

	std::vector<Location> getAuxLocations();

	void addAuxLoc(Location);

	// Mutators
	void setScreen(std::string);

	void setLocationName(std::string nameArg) { locationName = nameArg; }

	void setLocationX(int);
	void setLocationY(int);


private:

	std::string locationName;

	// Store the main 'sprite'
	std::vector<std::string> screen;
	// Store any attached locations which can be accessed via the main hub
	std::vector<Location> auxLocations;

	int locationX;
	int locationY;

};