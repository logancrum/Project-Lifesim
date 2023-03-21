#pragma once
#include <iostream>

#include <town.h>
#include <item.h>

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
	void enterTown(Player);


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

};