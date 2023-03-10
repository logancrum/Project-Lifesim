#pragma once
#include <iostream>
#include <player.h>

class Game
{
public:
	Game();
	~Game();

private:
	std::string gameID;

public:
	// Initialization
	void start();
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


	// cin functions
	int getCleanInt();
	std::string getCleanString();

	// Screen Printers


	// Accessors
	std::string getGameID();

	// Mutators
	void setGameID(std::string set);

};