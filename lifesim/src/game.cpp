#include <game.h>

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include <player.h>
#include <item.h>
#include <cstdlib> // for _dupenv_s

namespace fs = std::filesystem;

Game::Game()
{
}

Game::~Game()
{
}

void Game::setGameID(std::string set) {
	gameID = set;
}

std::string Game::getGameID() {
	return gameID;
}

void Game::start() {
	// Initialize all items 
	initialize_all_items();
	// Initialize Player object player
	Player player;

	// Get user input
	int userChoice = -1;
	while (userChoice != 1 && userChoice != 2 && userChoice != 3) {
		userChoice = -1;
		printMain();
		std::cout << "==================================================" << std::endl;
		std::cout << "             Enter Choice 1, 2, or 3              " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << std::endl;

		// Get user input
		userChoice = getCleanInt();

		// Process user input
		switch (userChoice) {
		case 1:
			loadGameMM();
			break;
		case 2:
			newGame();
			break;
		case 3:
			quitGameMM();
			break;
		case 69:
			std::cout << "nice." << std::endl;
			std::cout << "but try again." << std::endl;
			break;
		default:
			std::cout << "            Try again.            " << std::endl;
			break;
		}
	}
}

void Game::printMain() {
	std::cout << "  __  __                    _                     " << std::endl;
	std::cout << " |  \\/  | _   _  _ __    __| |  __ _  _ __    ___ " << std::endl;
	std::cout << " | |\\/| || | | || '_ \\  / _` | / _` || '_ \\  / _ \\" << std::endl;
	std::cout << " | |  | || |_| || | | || (_| || (_| || | | ||  __/" << std::endl;
	std::cout << " |_|  |_| \\__,_||_| |_| \\__,_| \\__,_||_| |_| \\___|" << std::endl;
	std::cout << "                                                  " << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "             |     1. Load Game     |             " << std::endl;
	std::cout << "             |     2.  New Game     |             " << std::endl;
	std::cout << "             |     3.      Quit     |             " << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << std::endl;
}

int Game::getCleanInt() {
	// Get user input
	int userInt;
	bool failed = true;
	
	while (failed == true) {
		std::cin >> userInt;

		if (std::cin.fail())
		{
			std::cout << "==================================================" << std::endl;
			std::cout << "               ERROR! Invalid Input               " << std::endl;
			std::cout << "==================================================" << std::endl;
			std::cout << std::endl;

			// Get rid of failure state
			std::cin.clear();

			// Discard 'bad' character(s) 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// Reset user input
			userInt = -1;
			std::cout << "           Try again: Enter an integer.           " << std::endl;
		}
		else {
			failed = false;
			return userInt;
		}
	}
}

std::string Game::getCleanString() {
	// Get user input
	std::string userString;
	bool failed = true;

	while (failed == true) {
		std::cin >> userString;

		if (std::cin.fail())
		{
			std::cout << "==================================================" << std::endl;
			std::cout << "               ERROR! Invalid Input               " << std::endl;
			std::cout << "==================================================" << std::endl;
			std::cout << std::endl;

			// Get rid of failure state
			std::cin.clear();

			// Discard 'bad' character(s) 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// Reset user input
			userString = "";
		}
		else {
			failed = false;
			return userString;
		}
	}
}

void Game::loadGameMM() {

	// Get the user's documents folder
	char* documentsPath = nullptr;
	size_t bufferSize = 0;
	_dupenv_s(&documentsPath, &bufferSize, "USERPROFILE");
	if (documentsPath == nullptr) {
		std::cerr << "Error: Unable to determine documents folder." << std::endl;
		delete[] documentsPath;
		return;
	}
	std::string saveGamesFolder = documentsPath;
	saveGamesFolder += "\\Documents\\mundane\\";
	if (fs::exists(saveGamesFolder)) {
		std::cout << "Folder already exists: " << saveGamesFolder << std::endl;
	}
	else {
		std::filesystem::create_directory(saveGamesFolder);
	}

	saveGamesFolder += "savegames\\";
	if (fs::exists(saveGamesFolder)) {
		std::cout << "Folder already exists: " << saveGamesFolder << std::endl;
	}
	else {
		std::filesystem::create_directory(saveGamesFolder);
	}
	delete[] documentsPath;

	// Iterate over the saveGamesFolder
	int counter = 0;
	for (const auto& entry : fs::directory_iterator(saveGamesFolder)) {
		std::cout << counter + 1 << ". " << entry.path() << std::endl;
		// Count the number of save files found
		counter++;
	}
	std::cout << std::endl;

	if (counter == 0) {
		// Get rid of failure state
		std::cin.clear();

		// Discard 'bad' character(s) 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::string loadNew = "";
		// Savegames folder is empty
		std::cout << "==================================================" << std::endl;
		std::cout << "               No Save Files Found.               " << std::endl;
		std::cout << std::endl;
		std::cout << "                  New Game? (y/n)                 " << std::endl;
		std::cout << "==================================================" << std::endl;

		while (loadNew == "") {
			// Handle input errors
			loadNew = getCleanString();
			// Start a new game
			if ((loadNew == "y") || (loadNew == "Y")) {
				newGame();
			}
			// Back to main menu
			else if ((loadNew == "n") || (loadNew == "N")) {
				start();
			}
			// Handle invalid response
			else {
				std::cout << "                    Try again.                    " << std::endl;
				std::cout << std::endl;
				std::cout << "                  New Game? (y/n)                 " << std::endl;
				std::cout << "==================================================" << std::endl;
				loadNew = "";
			}
		}
	}
	else {
		int userLoad;

		if (counter == 1) {
			std::cout << "There is only one save game on file." << std::endl;
			std::cout << "Loading." << std::endl;
			userLoad = 1;
		}
		else {
			// Get user input in range 1 - counter, inclusive
			userLoad = 0;
			while ((userLoad < 1) || (userLoad > counter)) {
				std::cout << "Enter a number to choose which " << std::endl;
				std::cout << "game to load, from 1 to " << (counter) << ", inclusive." << std::endl;
				userLoad = getCleanInt();
			}
		}

		// Now iterate and load that data from the file
		counter = 1;
		for (const auto& entry : fs::directory_iterator(saveGamesFolder)) {
			std::cout << counter << ". " << entry.path() << std::endl;
			// Count the number of save files found
			if (counter == userLoad) {
				std::cout << "Loading: " << counter << ". " << entry.path() << std::endl;

				// Initialize a new player object to hold loaded data
				Player loaded;

				// Declare a string bigLoad to bring in raw csv data
				std::string bigLoad;

				// Separate base file name from path
				std::string base_filename = entry.path().string();
				base_filename = base_filename.substr(base_filename.find_last_of("/\\") + 1);

				// Declare file stream object to read from file
				std::ifstream file(saveGamesFolder + base_filename);

				// Check if file is opened successfully
				if (!file.is_open()) {
					std::cerr << "Failed to open file" << std::endl;
					start();
				}

				// Declare variables to store data
				std::string s1, s2, s3, s4;

				// Read each line of the file and extract data into variables
				std::string line;
				while (std::getline(file, line)) {
					// Extract data from each column and store in variables
					std::istringstream iss(line);
					std::getline(iss, s1, ',');
					std::getline(iss, s2, ',');
					std::getline(iss, s3, ',');
					std::getline(iss, s4);

					// Print the extracted data to the console
					// std::cout << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << ", s4: " << s4 << std::endl;
				}

				// Close the file stream
				file.close();

				// Set name
				loaded.setName(s1);
				// Set isSpecial
				if (s2 == "true") {
					loaded.setIsSpecial(true);
				}
				else {
					loaded.setIsSpecial(false);
				}
				// Set hp
				loaded.setHP(stoi(s3));
				// Set maxHP
				loaded.setMaxHP(stoi(s4));

				// Welcome the player back
				std::cout << "Welcome back, " << loaded.getName() << "!" << std::endl;

				runGame(loaded);

				// Exit the while loop
				continue;
			}
			else {
				counter++;
			}
		}
	}
}


void Game::loadGame(Player set) {
	
	char* documentsPath = nullptr;
	size_t bufferSize = 0;
	_dupenv_s(&documentsPath, &bufferSize, "USERPROFILE");
	if (documentsPath == nullptr) {
		std::cerr << "Error: Unable to determine documents folder." << std::endl;
		delete[] documentsPath;
		return;
	}
	std::string saveGamesFolder = documentsPath;
	saveGamesFolder += "\\Documents\\mundane\\";
	if (fs::exists(saveGamesFolder)) {
		std::cout << "Folder already exists: " << saveGamesFolder << std::endl;
	}
	else {
		std::filesystem::create_directory(saveGamesFolder);
	}

	saveGamesFolder += "savegames\\";
	if (fs::exists(saveGamesFolder)) {
		std::cout << "Folder already exists: " << saveGamesFolder << std::endl;
	}
	else {
		std::filesystem::create_directory(saveGamesFolder);
	}
	delete[] documentsPath;

	// Check if player would like to save first
	std::cout << "Would you like to save this game first?" << std::endl;
	std::string save = "";
	while (save == "") {
		std::cout << "Enter (y/n): ";
		save = getCleanString();
		if ((save == "y") || (save == "Y")) {
			saveGame(set);
		}
		else if ((save != "n") && (save != "N")) {
			// Get new input
			save = "";
			std::cout << std::endl;
			std::cout << "Try again." << std::endl;

		}
		// else: save is "n" or "N"
	}

	int counter = 0;
	for (const auto& entry : fs::directory_iterator(saveGamesFolder)) {
		std::cout << counter + 1 << ". " << entry.path() << std::endl;
		// Count the number of save files found
		counter++;
	}
	std::cout << std::endl;

	if (counter == 0) {
		// Get rid of failure state
		std::cin.clear();

		// Discard 'bad' character(s) 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::string loadNew = "";
		// Savegames folder is empty
		std::cout << "==================================================" << std::endl;
		std::cout << "               No Save Files Found.               " << std::endl;
		std::cout << std::endl;
		std::cout << "                  New Game? (y/n)                 " << std::endl;
		std::cout << "==================================================" << std::endl;

		while (loadNew == "") {
			// Handle input errors
			loadNew = getCleanString();
			// Start a new game
			if ((loadNew == "y") || (loadNew == "Y")) {
				newGame();
			}
			// Back to main menu
			else if ((loadNew == "n") || (loadNew == "N")) {
				start();
			}
			// Handle invalid response
			else {
				std::cout << "                    Try again.                    " << std::endl;
				std::cout << std::endl;
				std::cout << "                  New Game? (y/n)                 " << std::endl;
				std::cout << "==================================================" << std::endl;
				loadNew = "";
			}
		}
	}
	else {
		int userLoad;

		if (counter == 1) {
			std::cout << "There is only one save game on file." << std::endl;
			std::cout << "Loading." << std::endl;
			userLoad = 1;
		}
		else {
			// Get user input in range 1 - counter, inclusive
			userLoad = 0;
			while ((userLoad < 1) || (userLoad > counter)) {
				std::cout << "Enter a number to choose which " << std::endl;
				std::cout << "game to load, from 1 to " << (counter) << ", inclusive." << std::endl;
				userLoad = getCleanInt();
			}
		}

		// Now iterate and load that data from the file
		counter = 1;
		for (const auto& entry : fs::directory_iterator(saveGamesFolder)) {
			std::cout << counter << ". " << entry.path() << std::endl;
			// Count the number of save files found
			if (counter == userLoad) {
				std::cout << "Loading: " << counter << ". " << entry.path() << std::endl;

				// Initialize a new player object to hold loaded data
				Player loaded;

				// Declare a string bigLoad to bring in raw csv data
				std::string bigLoad;

				// Separate base file name from path
				std::string base_filename = entry.path().string();
				base_filename = base_filename.substr(base_filename.find_last_of("/\\") + 1);

				// Declare file stream object to read from file
				std::ifstream file(saveGamesFolder + base_filename);
				std::cout << saveGamesFolder + base_filename + ".csv" << std::endl;
				// Check if file is opened successfully
				if (!file.is_open()) {
					std::cerr << "Failed to open file" << std::endl;
					pauseMenu(set);
				}

				// Declare variables to store data
				std::string s1, s2, s3, s4;

				// Read each line of the file and extract data into variables
				std::string line;
				while (std::getline(file, line)) {
					// Extract data from each column and store in variables
					std::istringstream iss(line);
					std::getline(iss, s1, ',');
					std::getline(iss, s2, ',');
					std::getline(iss, s3, ',');
					std::getline(iss, s4);

					// Print the extracted data to the console
					std::cout << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << ", s4: " << s4 << std::endl;
				}

				// Close the file stream
				file.close();

				// Set name
				loaded.setName(s1);
				// Set isSpecial
				if (s2 == "true") {
					loaded.setIsSpecial(true);
				}
				else {
					loaded.setIsSpecial(false);
				}
				// Set hp
				loaded.setHP(stoi(s3));
				// Set maxHP
				loaded.setMaxHP(stoi(s4));

				// Welcome the player back
				std::cout << "Welcome back, " << loaded.getName() << "!" << std::endl;

				runGame(loaded);

				// Exit the while loop
				continue;
			}
			else {
				counter++;
			}
		}
	}
}

void Game::newGame() {
	// Initialize player object
	Player player;

	std::cout << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << std::endl;
	std::cout << "                What is your name?                " << std::endl;
	std::cout << std::endl;

	player.setName(getCleanString());
	player.setIsSpecial();
	player.setMaxHP(100);
	player.setHP(100);

	std::cout << "Welcome to Mundane, " << player.getName() << "!" << std::endl;
	
	// TEST player.printHP();
	
	runGame(player);
}

void Game::quitGameMM() {
	// Confirm quit command
	std::cout << std::endl;
	std::cout << "              Quit to Desktop?? (y/n)             " << std::endl;
	std::cout << "==================================================" << std::endl;

	std::string quit = "";
	while (quit == "") {
		// Handle input errors
		quit = getCleanString();
		// Start a new game
		if (quit == "y" || quit == "Y") {
			exit(0);
		}
		// Back to main menu
		else if (quit == "n" || quit == "N") {
			start();
		}
		// Handle invalid response
		else {
			std::cout << "                    Try again.                    " << std::endl;
			std::cout << std::endl;
			std::cout << "              Quit to Desktop?? (y/n)             " << std::endl;
			std::cout << "==================================================" << std::endl;
			quit = "";
		}
	}
	// Quit with exit function, return code 0
	exit(0);
}

void Game::quitGame(Player setPlayer) {

	// Confirm quit command
	std::cout << std::endl;
	std::cout << "                 Quit Game?? (y/n)                " << std::endl;
	std::cout << "==================================================" << std::endl;
	
	std::string quit = "";
	while (quit == "") {
		// Handle input errors
		quit = getCleanString();
		// Start a new game
		if (quit == "y" || quit == "Y") {
			// Do nothing
		}
		// Back to main menu
		else if (quit == "n" || quit == "N") {
			// Back to pause menu
			pauseMenu(setPlayer);
		}
		// Handle invalid response
		else {
			std::cout << "                    Try again.                    " << std::endl;
			std::cout << std::endl;
			std::cout << "                 Quit Game?? (y/n)                " << std::endl;
			std::cout << "==================================================" << std::endl;
			quit = "";
		}
	}

	// Save before quitting?
	std::cout << "==================================================" << std::endl;
	std::cout << "          Would you like to save?? (y/n)          " << std::endl;

	std::string save = "";
	while (save == "") {
		// Handle input errors
		save = getCleanString();
		// Start a new game
		if ((save == "y") || (save == "Y")) {
			saveGame(setPlayer);
		}
		// Back to main menu
		else if ((save == "n") || (save == "N")) {
			// do nothing
		}
		// Handle invalid response
		else {
			std::cout << "                    Try again.                    " << std::endl;
			std::cout << std::endl;
			std::cout << "                 Save Game?? (y/n)                " << std::endl;
			std::cout << "==================================================" << std::endl;
			save = "";
		}
	}

	// Return to main menu
	start();
}

void Game::saveGame(Player set) {
	// Get gameID from player
	std::cout << "               Name your save file:               " << std::endl;
	std::cout << std::endl;
	std::cout << "==================================================" << std::endl;
	gameID = getCleanString();

	// Get the user's documents folder
	char* documentsPath = nullptr;
	size_t bufferSize = 0;
	_dupenv_s(&documentsPath, &bufferSize, "USERPROFILE");
	if (documentsPath == nullptr) {
		std::cerr << "Error: Unable to determine documents folder." << std::endl;
		return;
	}

	// Create path if needed
	std::ofstream saveFile;
	std::string fileName = std::string(documentsPath) + "\\My Documents\\Mundane\\";

	if (fs::exists(fileName)) {
		std::cout << "Folder already exists: " << fileName << std::endl;
	}
	else {
		std::filesystem::create_directory(fileName);
	}

	fileName += "savegames\\";
	if (fs::exists(fileName)) {
		std::cout << "Folder already exists: " << fileName << std::endl;
	}
	else {
		std::filesystem::create_directory(fileName);
	}

	// Name save file according to user input
	fileName += gameID;
	fileName += ".csv";

	// Generate a csv with player data, so players can pick up where they left off
	saveFile.open(fileName);
	if (!saveFile.is_open()) {
		std::cerr << "Error: Unable to create save file." << std::endl;
		return;
	}

	// Write player data to csv 
	saveFile << set.getName() << ",";
	saveFile << set.getIsSpecial() << ",";
	saveFile << set.getHP() << ",";
	saveFile << set.getMaxHP() << ",";

	// TODO: Include additional player data, as well as inventory data

	// Close the file
	saveFile.close();
	// Print success message
	std::cout << "Game \'" << gameID << "\' has been saved." << std::endl;

	// Free the documentsPath memory
	free(documentsPath);
}

void Game::pauseMenu(Player set) {
	bool paused = true;
	while (paused) {
		// Print options
		std::cout << "                      Paused                      " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << "                 1: Resume Game                   " << std::endl;
		std::cout << "                 2: Save Game                     " << std::endl;
		std::cout << "                 3: Load Game                     " << std::endl;
		std::cout << "                 4: Quit to Main Menu             " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << "Enter your choice here: ";
		// Get user choice
		int userChoice = getCleanInt();
		switch (userChoice) {
		case 1:
			paused = false;
			runGame(set);
			break;
		case 2:
			saveGame(set);
			break;
		case 3:
			paused = false;
			loadGame(set);
			break;
		case 4:
			quitGame(set);
			break;
		default:
			break;
		}
	}
}

void Game::runGame(Player set) {
	bool gameRunning = true;
	while (gameRunning) {
		std::cout << "                     Options:                     " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << "                 1: Pause Menu                    " << std::endl;
		std::cout << "                 2: Journal                       " << std::endl;
		std::cout << "                 3: Stats                         " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << std::endl;
		std::cout << "Name: " << set.getName() << " | ";
		set.printHP();
		std::cout << std::endl;
		
		int play = getCleanInt();
		switch (play) {
		case 1:
			pauseMenu(set);
			break;
		case 2:
			std::cout << "Sorry! The \'Journal\' logic has not yet been created... Coming soon!" << std::endl;
			break;
		case 3:
			std::cout << "Sorry! The \'Bio\' logic has not yet been created... Coming soon!" << std::endl;
			break;
		default:
			break;
		}
	}
}

void Game::initialize_all_items() {
	// Variables for parsing sprite .csv files
	std::vector<std::string> tempSprite;
	std::string spriteLine;
	
	// Declare file stream object to read from file
	std::ifstream spriteFile(fs::current_path().string() + "\\sprites\\tusk_helm.txt");
	std::cout << fs::current_path().string().append("\\sprites\\tusk_helm.txt") << std::endl;

	// Helmets
	Item tusk_helm;
	while (std::getline(spriteFile, spriteLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(spriteLine);
		std::getline(issSprite, spriteLine);
		tempSprite.push_back(spriteLine);

		// Print the extracted data to the console
		// std::cout << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << ", s4: " << s4 << std::endl;
	}

	spriteFile.close();

	// TESTS
	tusk_helm.setItemSprite(tempSprite);
	tusk_helm.printItemSprite();

	tempSprite.clear();
	
	std::ifstream mapFile1(fs::current_path().string() + "\\sprites\\world_map.txt");
	std::ofstream mapFile2(fs::current_path().string() + "\\sprites\\world_map_ocean_contrast.txt");

	Item world_map;
	while (std::getline(mapFile1, spriteLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(spriteLine);
		std::getline(issSprite, spriteLine);
		std::replace_if(spriteLine.begin(), spriteLine.end(), [](char ch) { return ch != ' '; }, '@');
		tempSprite.push_back(spriteLine);

		mapFile2 << spriteLine << "\n";
		// Print the extracted data to the console
		// std::cout << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << ", s4: " << s4 << std::endl;
	}

	mapFile1.close();
	mapFile2.close();
	tempSprite.clear();
}