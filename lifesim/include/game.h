#pragma once
#include <iostream>

#include <town.h>
#include <item.h>
#include <player.h>

class Game {
public:
	Game();
	~Game();

private:
	std::string gameID;

public:
	// Initialization
	void start();
	int initMap();
	void initialize_all_items();
	void initialize_all_towns();

	// Main menu functions
	void printMain();
	void loadGameMM();
	void newGame();
	void quitGameMM();

	// Game Menu Functions
	void pauseMenu(Player);
	void quitGame(Player);
	void loadGame(Player);
	void saveGame(Player);

	// Game loop
	void runGame(Player);

	// Map loop
	void travMap(Player);

	// Location loop
	void enterTown(Player);
	void enterBlacksmith(Town, Player);
	void enterGrocer(Town, Player);
	void enterTavern(Town, Player);

	// Function to display town, etc... 

	// cin functions
	int getCleanInt();
	std::string getCleanString();

	// Screen Printers
	void displayMap(Player);

	// Accessors
	std::string getGameID();

	// Mutators
	void setGameID(std::string set);

	std::vector<Town> towns;
	std::vector<Location> locations;

	// Towns
	


};