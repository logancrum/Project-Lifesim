#include <game.h>

namespace fs = std::filesystem;

const int MAP_MAX_ROWS = 86;
const int MAP_MAX_COLS = 300;
char gameMap[MAP_MAX_ROWS][MAP_MAX_COLS];
char gameMapCopy[MAP_MAX_ROWS][MAP_MAX_COLS];

Inventory playerInventory;

Town thowerd;

Game::Game() {
	day = 1;
	season = "Spring";
	seasonCount = 1;
	year = 300;

}

Game::~Game() {
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
	//Initialize the game map
	initMap();
	// Initialize towns, castles, caves, etc...

	initialize_all_towns();
	
	// Initialize Player object player
	Player player;
	
	// TEST 
	// displayMap(player);
	
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
			system("CLS");
			loadGameMM();
			break;
		case 2:
			system("CLS");
			newGame();
			break;
		case 3:
			system("CLS");
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
	system("CLS");
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
	return -1;
}

std::string Game::getCleanString() {
	// Get user input
	std::string userString;
	bool failed = true;

	while (failed == true) {
		std::cin >> userString;

		if (std::cin.fail()) {
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
	return "ERROR: COULD NOT GET CLEAN STRING!";
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
				std::string s1, s2, s3, s4, s5, s6;

				// Read each line of the file and extract data into variables
				std::string line;
				while (std::getline(file, line)) {
					// Extract data from each column and store in variables
					std::istringstream iss(line);
					std::getline(iss, s1, ',');
					std::getline(iss, s2, ',');
					std::getline(iss, s3, ',');
					std::getline(iss, s4, ',');
					std::getline(iss, s5, ',');
					std::getline(iss, s6, ',');

					// Print the extracted data to the console
					std::cout << std::endl << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << ", s4: " << s4 << "s5: " << s5 << ", s6: " << s6 << std::endl;
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

				loaded.setPlayerX(stoi(s5));
				loaded.setPlayerY(stoi(s6));

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
				std::string s1, s2, s3, s4, s5, s6;

				// Read each line of the file and extract data into variables
				std::string line;
				while (std::getline(file, line)) {
					// Extract data from each column and store in variables
					std::istringstream iss(line);
					std::getline(iss, s1, ',');
					std::getline(iss, s2, ',');
					std::getline(iss, s3, ',');
					std::getline(iss, s4, ',');
					std::getline(iss, s5, ',');
					std::getline(iss, s6, ',');

					// Print the extracted data to the console
					std::cout << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << ", s4: " << s4 << "s5: " << s5 << ", s6: " << s6 << std::endl;
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

				loaded.setPlayerX(stoi(s5));
				loaded.setPlayerY(stoi(s6));

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

	system("CLS");

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
	saveFile << set.getPlayerX() << ",";
	saveFile << set.getPlayerY() << ",";
	saveFile << "\n";

	// Write player inventory data to csv
	for (int i = 0; i < playerInventory.getCarriedItems().size(); i++) {
		saveFile << playerInventory.getCarriedItems().at(i).getItemName() << ",";
	}
	saveFile << "\n";
	for (int i = 0; i < playerInventory.getEquippedItems().size(); i++) {
		saveFile << playerInventory.getEquippedItems().at(i).getItemName() << ",";
	}
	saveFile << "\n";

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
			system("CLS");
			paused = false;
			runGame(set);
			break;
		case 2:
			system("CLS");
			saveGame(set);
			break;
		case 3:
			system("CLS");
			paused = false;
			loadGame(set);
			break;
		case 4:
			system("CLS");
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
		std::cout << "                                                  " << std::endl;
		std::cout << "                 1: Pause Menu                    " << std::endl;
		std::cout << "                 2: Journal                       " << std::endl;
		std::cout << "                 3: Stats                         " << std::endl;
		std::cout << "                 4: Move Player                   " << std::endl;
		std::cout << "                                                  " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << std::endl;
		std::cout << "Name: " << set.getName() << " | ";
		set.printHP();
		std::cout << std::endl;
		
		int play = getCleanInt();
		switch (play) {
		case 1:
			system("CLS");
			pauseMenu(set);
			break;
		case 2:
			system("CLS");
			std::cout << "Sorry! The \'Journal\' logic has not yet been created... Coming soon!" << std::endl;
			break;
		case 3:
			system("CLS");
			std::cout << "Sorry! The \'Bio\' logic has not yet been created... Coming soon!" << std::endl;
			break;
		case 4:
			system("CLS");
			travMap(set);
		default:
			break;
		}
	}
}

void Game::travMap(Player set) {
	
	bool mapTime = true;

	system("CLS");
	std::cin.clear();

	displayMap(set);

	while (mapTime) {
		// Different switch options, message depending on Player Location on map
		if (gameMap[set.getPlayerY()][set.getPlayerX()] == 'V') {
			std::cout << "Enter WASD movement command, Q to Quit, or I to enter the town: ";
			char travChoice = _getch();

			if (tolower(travChoice) == 's') {
				if (gameMap[set.getPlayerY() + 1][set.getPlayerX()] != '@') {
					// Move South
					incrementDay();
					set.incPlayerY();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'a') {
				if (gameMap[set.getPlayerY()][set.getPlayerX() - 1] != '@') {
					// Move West
					incrementDay();
					set.decPlayerX();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'w') {
				if (gameMap[set.getPlayerY() - 1][set.getPlayerX()] != '@') {
					// Move North
					incrementDay();
					set.decPlayerY();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'd') {
				if (gameMap[set.getPlayerY()][set.getPlayerX() + 1] != '@') {
					// Move East
					incrementDay();
					set.incPlayerX();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'q') {
				// Quit mapTime
				mapTime = false;
				system("CLS");
				runGame(set);
			}
			else if (tolower(travChoice) == 'i') {
				// Enter the town at { playerX, playerY }
				enterTown(set, getTown(set.getPlayerX(), set.getPlayerY()));
			}
			else {
				// Do Nothing
			}
		}
		else
		{
			std::cout << "Enter WASD movement command, Q to Quit: ";
			char travChoice = _getch();

			if (tolower(travChoice) == 's') {
				if (gameMap[set.getPlayerY() + 1][set.getPlayerX()] != '@') {
					// Move North
					incrementDay();
					set.incPlayerY();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'a') {
				if (gameMap[set.getPlayerY()][set.getPlayerX() - 1] != '@') {
					// Move West
					incrementDay();
					set.decPlayerX();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'w') {
				if (gameMap[set.getPlayerY() - 1][set.getPlayerX()] != '@') {
					// Move South
					incrementDay();
					set.decPlayerY();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'd') {
				if (gameMap[set.getPlayerY()][set.getPlayerX() + 1] != '@') {
					// Move East
					incrementDay();
					set.incPlayerX();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'q') {
				// Quit mapTime
				mapTime = false;
				system("CLS");
				runGame(set);
			}
			else {
				// Do Nothing
			}
		} 
	}
}

Town Game::getTown(int playerXArg, int playerYArg) {
	for (int i = 0; i < all_towns.size(); i++) {
		if ((all_towns.at(i).getLocationX() == playerXArg) && (all_towns.at(i).getLocationY() == playerYArg)) {
			return all_towns.at(i);
		}
	}
}

// Function to display the map
void Game::displayMap(Player set) {
	// std::vector<std::string> mapStrings;

	for (int i = 0; i < MAP_MAX_ROWS; i++) {
		std::string mapString = "";
		for (int j = 0; j < MAP_MAX_COLS; j++) {
			if (i == set.getPlayerY() && j == set.getPlayerX()) {
				mapString += 'P';
			}
			else {
				mapString += gameMap[i][j];
			}
		}
		std::cout << mapString << std::endl;
	}
	
	std::cout << std::endl;
	std::cout << set.getPlayerX() << " | " << set.getPlayerY() << std::endl;
	printCalendar();
}

void Game::enterTown(Player set, Town townArg) {
	
	char townChoice;
	set.setInTownTrue();

	if (townArg.getTownAuxScreens().size() == 3) {

		while (set.getInTown()) {
			std::cin.clear();

			townArg.printScreen();
			std::cout << "State your business: ";

			townChoice = _getch();
			if (townChoice == '1') {
				enterBlacksmith(townArg, set);
			}
			else if (townChoice == '2') {
				enterGrocer(townArg, set);
			}
			else if (townChoice == '3') {
				enterTavern(townArg, set);
			}
			else if (townChoice == '4') {
				set.setInTownFalse();
				travMap(set);
			}
			else {
				thowerd.printScreen();
				std::cout << "State your business: ";
				townChoice = _getch();
			}
		}
	}
	else if (townArg.getTownAuxScreens().size() == 4) {
		while (set.getInTown()) {
			std::cin.clear();

			townArg.printScreen();
			std::cout << "State your business: ";

			townChoice = _getch();
			if (townChoice == '1') {
				enterBlacksmith(townArg, set);
			}
			else if (townChoice == '2') {
				enterGrocer(townArg, set);
			}
			else if (townChoice == '3') {
				enterTavern(townArg, set);
			}
			else if (townChoice == '4') {
				enterAlley (townArg, set);
			}
			else if (townChoice == '5') {
				set.setInTownFalse();
				travMap(set);
			}
			else {
				thowerd.printScreen();
				std::cout << "State your business: ";
				townChoice = _getch();
			}
		}
	}
}

void Game::enterBlacksmith(Town town, Player set) {
	system("CLS");
	std::cin.clear();
	town.printBlacksmith();
	std::cout << "Press any alphanumerical key to return to the town square." << std::endl;
	char stalling = _getch();
	system("CLS");
}

void Game::enterGrocer(Town town, Player set) {
	system("CLS");
	std::cin.clear();
	town.printGrocer();
	std::cout << "Press any alphanumerical key to return to the town square." << std::endl;
	char stalling = _getch();
}

void Game::enterTavern(Town town, Player set) {
	system("CLS");
	std::cin.clear();
	town.printTavern();
	std::cout << "Press any alphanumerical key to return to the town square." << std::endl;
	char stalling = _getch();
}

void Game::enterAlley(Town townArg, Player set) {
	system("CLS");
	std::cin.clear();
	townArg.printAux4();
	std::cout << "Press any alphanumerical key to return to the town square." << std::endl;
	char stalling = _getch();
}
/*
void testBuy() {
	system("CLS");
	bool testingBuy = true;
	std::string testChoice;
	while (testingBuy) {
		system("CLS");
		testShopInventory.printInventorySell();
		testPlayerInventory.printInventoryBuy();
		std::cout << std::endl << "Enter a number to buy an item, enter 0 to quit: ";
		auto inventorySize = testShopInventory.getFoundItems().size();

		// Get user input as string, convert to int; if 0, return to shop screen
		std::cin >> testChoice;
		int indexChoice = stoi(testChoice);
		indexChoice -= 1;

		if (indexChoice == -1) {
			testingBuy = false;
			// Return to shop screen
			runTests();
		}
		if ((indexChoice < inventorySize) && (indexChoice >= 0)) {
			if (testPlayerInventory.getTotalPurse()
				>= (testShopInventory.getFoundItem(indexChoice).getItemValue() * testShopInventory.getSellMult())) {
				testPlayerInventory.buyItem(testShopInventory.getFoundItem(indexChoice));
				testShopInventory.sellItem(indexChoice);
			}
		}
	}
}

void testSell() {
	system("CLS");
	bool testingSell = true;
	std::string testChoice;
	while (testingSell) {
		system("CLS");
		testPlayerInventory.printInventorySell();
		std::cout << std::endl << "Enter a number to sell an item, enter 0 to quit: ";
		auto inventorySize = testPlayerInventory.getFoundItems().size();

		// Get user input as string, convert to int; if 0, return to shop screen
		std::cin >> testChoice;
		int indexChoice = stoi(testChoice);
		indexChoice -= 1;

		if (indexChoice == -1) {
			testingSell = false;
			// Return to shop screen
			runTests();
		}
		if ((indexChoice < inventorySize) && (indexChoice >= 0)) {
			testShopInventory.buyItem(testPlayerInventory.getFoundItem(indexChoice));
			testPlayerInventory.sellItem(indexChoice);
		}
	}
}
*/

// FIXME: Create a loop for each auxilliary location 

void Game::incrementDay() {
	day += 1;
	if (day == 90) {
		// reset to day one of the new season
		day = 1;

		// change the season
		seasonCount += 1;

		if (seasonCount == 5) {
			// This marks the end of winter; reset seasonCount, increment year, set season to spring
			seasonCount = 1;
			year += 1;
			season = "Spring";
		}
		else if (seasonCount == 2) {
			// This marks the end of spring; set season to summer
			season = "Summer";
		}
		else if (seasonCount == 3) {
			// This marks the end of summer; set season to autumn
			season = "Autumn";
		}
		else if (seasonCount == 4) {
			// This marks the end of autumn; set season to winter
			season = "Winter";
		}
	}

	if ((day % 15) == 1) {
		// FIXME: reset all store inventories
	}
}

void Game::printCalendar() {
	std::cout << "Today is Day " << day << " of " << season << ", in the Year " << year << "." << std::endl;
}

int Game::initMap() {
	// create ifstream to read map from txt file
	std::ifstream mapFile(fs::current_path().string() + "\\maps\\world_map_ocean_contrast_b.txt");
	
	// Check that mapFile opened correctly
	if (!mapFile.is_open()) {
		std::cout << "ERROR: Could not open map file" << std::endl;
		// Return ERROR code
		return -1;
	}
	else {

		// Read the map from the file
		std::string mapLine;
		int row = 0;

		while (std::getline(mapFile, mapLine)) {
			// Make sure the row isn't too long
			if (mapLine.length() > MAP_MAX_COLS) {
				std::cout << "Error: row " << row << " is too long!" << std::endl;
				return 1;
			}
			// Copy the row into the map array
			for (int col = 0; col < mapLine.length(); col++) {
				gameMap[row][col] = mapLine[col];
			}
			row++; // move on to the next row
		}
		// Close the file
		mapFile.close();

		// Return successful code
		return 0;
	}
}

void Game::initialize_all_items() {

	/*
	*
	*		ARMOR: HELMETS
	*
	*/

	tusk_helm.setItemSprite("\\sprites\\armor\\helmets\\tusk_helm.txt");
	tusk_helm.setItemName("Tusk Helm");
	tusk_helm.setItemType("Helmet");
	tusk_helm.setItemDam(0);
	tusk_helm.setItemDT(2);
	tusk_helm.setItemValue(100);
	all_items.emplace_back(tusk_helm);
	all_blacksmith_items.emplace_back(tusk_helm);

	leather_soldiers_helmet.setItemSprite("\\sprites\\armor\\helmets\\leather_soldiers_helmet.txt");
	leather_soldiers_helmet.setItemName("Leather Soldier\'s Helmet");
	leather_soldiers_helmet.setItemType("Helmet");
	leather_soldiers_helmet.setItemDam(0);
	leather_soldiers_helmet.setItemDT(3);
	leather_soldiers_helmet.setItemValue(100);
	all_items.emplace_back(leather_soldiers_helmet);
	all_blacksmith_items.emplace_back(leather_soldiers_helmet);

	plain_bascinet.setItemSprite("\\sprites\\armor\\helmets\\plain_bascinet.txt");
	plain_bascinet.setItemName("Plain Bascinet");
	plain_bascinet.setItemType("Helmet");
	plain_bascinet.setItemDam(0);
	plain_bascinet.setItemDT(4);
	plain_bascinet.setItemValue(400);
	all_items.emplace_back(plain_bascinet);
	all_blacksmith_items.emplace_back(plain_bascinet);

	mail_coif.setItemSprite("\\sprites\\armor\\helmets\\mail_coif.txt");
	mail_coif.setItemName("Mail Coif");
	mail_coif.setItemType("Helmet");
	mail_coif.setItemDam(0);
	mail_coif.setItemDT(5);
	mail_coif.setItemValue(500);
	all_items.emplace_back(mail_coif);
	all_blacksmith_items.emplace_back(mail_coif);

	iron_soldiers_cap.setItemSprite("\\sprites\\armor\\helmets\\iron_soldiers_cap.txt");
	iron_soldiers_cap.setItemName("Iron Soldier\'s Cap");
	iron_soldiers_cap.setItemType("Helmet");
	iron_soldiers_cap.setItemDam(0);
	iron_soldiers_cap.setItemDT(6);
	iron_soldiers_cap.setItemValue(800);
	all_items.emplace_back(iron_soldiers_cap);
	all_blacksmith_items.emplace_back(iron_soldiers_cap);

	steel_helm.setItemSprite("\\sprites\\armor\\helmets\\steel_helm.txt");
	steel_helm.setItemName("Steel Helm");
	steel_helm.setItemType("Helmet");
	steel_helm.setItemDam(0);
	steel_helm.setItemDT(7);
	steel_helm.setItemValue(1000);
	all_items.emplace_back(steel_helm);
	all_blacksmith_items.emplace_back(steel_helm);

	spiked_great_helm.setItemSprite("\\sprites\\armor\\helmets\\spiked_great_helm.txt");
	spiked_great_helm.setItemName("Spiked Great Helm");
	spiked_great_helm.setItemType("Helmet");
	spiked_great_helm.setItemDam(0);
	spiked_great_helm.setItemDT(8);
	spiked_great_helm.setItemValue(1500);
	all_items.emplace_back(spiked_great_helm);
	all_blacksmith_items.emplace_back(spiked_great_helm);

	frog_mouth_great_helm.setItemSprite("\\sprites\\armor\\helmets\\frog_mouth_great_helm.txt");
	frog_mouth_great_helm.setItemName("Frog-Mouth Great Helm");
	frog_mouth_great_helm.setItemType("Helmet");
	frog_mouth_great_helm.setItemDam(0);
	frog_mouth_great_helm.setItemDT(8);
	frog_mouth_great_helm.setItemValue(2000);
	all_items.emplace_back(frog_mouth_great_helm);
	all_blacksmith_items.emplace_back(frog_mouth_great_helm);

	ancient_helm.setItemSprite("\\sprites\\armor\\helmets\\ancient_helm.txt");
	ancient_helm.setItemName("Ancient Helm");
	ancient_helm.setItemType("Helmet");
	ancient_helm.setItemDam(0);
	ancient_helm.setItemDT(10);
	ancient_helm.setItemValue(3000);
	all_items.emplace_back(ancient_helm);
	all_blacksmith_items.emplace_back(ancient_helm);

	/*
	*
	*		ARMOR: CHEST
	*
	*/

	wool_gambeson.setItemSprite("\\sprites\\armor\\chest\\wool_gambeson.txt");
	wool_gambeson.setItemName("Wool Gambeson");
	wool_gambeson.setItemType("Chest");
	wool_gambeson.setItemDam(0);
	wool_gambeson.setItemDT(6);
	wool_gambeson.setItemValue(200);
	all_items.emplace_back(wool_gambeson);
	all_blacksmith_items.emplace_back(wool_gambeson);

	leather_gambeson.setItemSprite("\\sprites\\armor\\chest\\leather_gambeson.txt");
	leather_gambeson.setItemName("Leather Gambeson");
	leather_gambeson.setItemType("Chest");
	leather_gambeson.setItemDam(0);
	leather_gambeson.setItemDT(8);
	leather_gambeson.setItemValue(200);
	all_items.emplace_back(leather_gambeson);
	all_blacksmith_items.emplace_back(leather_gambeson);

	heavy_padded_wool_gambeson.setItemSprite("\\sprites\\armor\\chest\\heavy_padded_wool_gambeson.txt");
	heavy_padded_wool_gambeson.setItemName("Heavy Padded Wool Gambeson");
	heavy_padded_wool_gambeson.setItemType("Chest");
	heavy_padded_wool_gambeson.setItemDam(0);
	heavy_padded_wool_gambeson.setItemDT(10);
	heavy_padded_wool_gambeson.setItemValue(200);
	all_items.emplace_back(heavy_padded_wool_gambeson);
	all_blacksmith_items.emplace_back(heavy_padded_wool_gambeson);

	leather_brigandine.setItemSprite("\\sprites\\armor\\chest\\leather_brigandine.txt");
	leather_brigandine.setItemName("Leather Brigandine");
	leather_brigandine.setItemType("Chest");
	leather_brigandine.setItemDam(0);
	leather_brigandine.setItemDT(11);
	leather_brigandine.setItemValue(200);
	all_items.emplace_back(leather_brigandine);
	all_blacksmith_items.emplace_back(leather_brigandine);

	heavy_leather_gambeson.setItemSprite("\\sprites\\armor\\chest\\heavy_leather_gambeson.txt");
	heavy_leather_gambeson.setItemName("Heavy Leather Gambeson");
	heavy_leather_gambeson.setItemType("Chest");
	heavy_leather_gambeson.setItemDam(0);
	heavy_leather_gambeson.setItemDT(12);
	heavy_leather_gambeson.setItemValue(200);
	all_items.emplace_back(heavy_leather_gambeson);
	all_blacksmith_items.emplace_back(heavy_leather_gambeson);

	lamellar_cuirass.setItemSprite("\\sprites\\armor\\chest\\lamellar_cuirass.txt");
	lamellar_cuirass.setItemName("Lamellar Cuirass");
	lamellar_cuirass.setItemType("Chest");
	lamellar_cuirass.setItemDam(0);
	lamellar_cuirass.setItemDT(14);
	lamellar_cuirass.setItemValue(400);
	all_items.emplace_back(lamellar_cuirass);
	all_blacksmith_items.emplace_back(lamellar_cuirass);

	light_iron_plate_armor.setItemSprite("\\sprites\\armor\\chest\\light_iron_plate_armor.txt");
	light_iron_plate_armor.setItemName("Light Iron Plate Armor");
	light_iron_plate_armor.setItemType("Chest");
	light_iron_plate_armor.setItemDam(0);
	light_iron_plate_armor.setItemDT(15);
	light_iron_plate_armor.setItemValue(800);
	all_items.emplace_back(light_iron_plate_armor);
	all_blacksmith_items.emplace_back(light_iron_plate_armor);

	light_steel_plate_armor.setItemSprite("\\sprites\\armor\\chest\\light_steel_plate_armor.txt");
	light_steel_plate_armor.setItemName("Light Steel Plate Armor");
	light_steel_plate_armor.setItemType("Chest");
	light_steel_plate_armor.setItemDam(0);
	light_steel_plate_armor.setItemDT(18);
	light_steel_plate_armor.setItemValue(1000);
	all_items.emplace_back(light_steel_plate_armor);
	all_blacksmith_items.emplace_back(light_steel_plate_armor);

	steel_cuirass.setItemSprite("\\sprites\\armor\\chest\\steel_cuirass.txt");
	steel_cuirass.setItemName("Steel Cuirass");
	steel_cuirass.setItemType("Chest");
	steel_cuirass.setItemDam(0);
	steel_cuirass.setItemDT(20);
	steel_cuirass.setItemValue(1500);
	all_items.emplace_back(steel_cuirass);
	all_blacksmith_items.emplace_back(steel_cuirass);

	/*
	*
	*		ARMOR: GLOVES
	*
	*/

	leather_gloves.setItemSprite("\\sprites\\armor\\gloves\\leather_gloves.txt");
	leather_gloves.setItemName("Leather Gloves");
	leather_gloves.setItemType("Gloves");
	leather_gloves.setItemDam(0);
	leather_gloves.setItemDT(1);
	leather_gloves.setItemValue(40);
	all_items.emplace_back(leather_gloves);
	all_blacksmith_items.emplace_back(leather_gloves);

	iron_gauntlets.setItemSprite("\\sprites\\armor\\gloves\\iron_gauntlets.txt");
	iron_gauntlets.setItemName("Iron Gauntlets");
	iron_gauntlets.setItemType("Gloves");
	iron_gauntlets.setItemDam(0);
	iron_gauntlets.setItemDT(3);
	iron_gauntlets.setItemValue(200);
	all_items.emplace_back(iron_gauntlets);
	all_blacksmith_items.emplace_back(iron_gauntlets);

	steel_gauntlets.setItemSprite("\\sprites\\armor\\gloves\\steel_gauntlets.txt");
	steel_gauntlets.setItemName("Steel Gauntlets");
	steel_gauntlets.setItemType("Gloves");
	steel_gauntlets.setItemDam(0);
	steel_gauntlets.setItemDT(3);
	steel_gauntlets.setItemValue(200);
	all_items.emplace_back(steel_gauntlets);
	all_blacksmith_items.emplace_back(steel_gauntlets);

	/*
	*
	*		ARMOR: LEGS
	*
	*/

	leather_tassets.setItemSprite("\\sprites\\armor\\legs\\leather_tassets.txt");
	leather_tassets.setItemName("Leather Tassets");
	leather_tassets.setItemType("Legs");
	leather_tassets.setItemDam(0);
	leather_tassets.setItemDT(1);
	leather_tassets.setItemValue(40);
	all_items.emplace_back(leather_tassets);
	all_blacksmith_items.emplace_back(leather_tassets);

	padded_cloth_chausses.setItemSprite("\\sprites\\armor\\legs\\padded_cloth_chausses.txt");
	padded_cloth_chausses.setItemName("Padded Cloth Chausses");
	padded_cloth_chausses.setItemType("Legs");
	padded_cloth_chausses.setItemDam(0);
	padded_cloth_chausses.setItemDT(1);
	padded_cloth_chausses.setItemValue(40);
	all_items.emplace_back(padded_cloth_chausses);
	all_blacksmith_items.emplace_back(padded_cloth_chausses);

	heavy_leather_chausses.setItemSprite("\\sprites\\armor\\legs\\heavy_leather_chausses.txt");
	heavy_leather_chausses.setItemName("Heavy Leather Chausses");
	heavy_leather_chausses.setItemType("Legs");
	heavy_leather_chausses.setItemDam(0);
	heavy_leather_chausses.setItemDT(1);
	heavy_leather_chausses.setItemValue(40);
	all_items.emplace_back(heavy_leather_chausses);
	all_blacksmith_items.emplace_back(heavy_leather_chausses);

	mail_chausses.setItemSprite("\\sprites\\armor\\legs\\mail_chausses.txt");
	mail_chausses.setItemName("Mail Chausses");
	mail_chausses.setItemType("Legs");
	mail_chausses.setItemDam(0);
	mail_chausses.setItemDT(1);
	mail_chausses.setItemValue(40);
	all_items.emplace_back(mail_chausses);
	all_blacksmith_items.emplace_back(mail_chausses);

	steel_tassets.setItemSprite("\\sprites\\armor\\legs\\steel_tassets.txt");
	steel_tassets.setItemName("Steel Chausses");
	steel_tassets.setItemType("Legs");
	steel_tassets.setItemDam(0);
	steel_tassets.setItemDT(1);
	steel_tassets.setItemValue(40);
	all_items.emplace_back(steel_tassets);
	all_blacksmith_items.emplace_back(steel_tassets);

	/*
	*
	*		ARMOR: BOOTS
	*
	*/

	leather_boots.setItemSprite("\\sprites\\armor\\boots\\leather_boots.txt");
	leather_boots.setItemName("Leather Boots");
	leather_boots.setItemType("Boots");
	leather_boots.setItemDam(0);
	leather_boots.setItemDT(3);
	leather_boots.setItemValue(60);
	all_items.emplace_back(leather_boots);
	all_blacksmith_items.emplace_back(leather_boots);

	fancy_riding_boots.setItemSprite("\\sprites\\armor\\boots\\fancy_riding_boots.txt");
	fancy_riding_boots.setItemName("Fancy Riding Boots");
	fancy_riding_boots.setItemType("Boots");
	fancy_riding_boots.setItemDam(0);
	fancy_riding_boots.setItemDT(4);
	fancy_riding_boots.setItemValue(140);
	all_items.emplace_back(fancy_riding_boots);
	all_blacksmith_items.emplace_back(fancy_riding_boots);

	iron_boots.setItemSprite("\\sprites\\armor\\boots\\iron_boots.txt");
	iron_boots.setItemName("Iron Boots");
	iron_boots.setItemType("Boots");
	iron_boots.setItemDam(0);
	iron_boots.setItemDT(6);
	iron_boots.setItemValue(400);
	all_items.emplace_back(iron_boots);
	all_blacksmith_items.emplace_back(iron_boots);

	steel_boots.setItemSprite("\\sprites\\armor\\boots\\steel_boots.txt");
	steel_boots.setItemName("Steel Boots");
	steel_boots.setItemType("Boots");
	steel_boots.setItemDam(0);
	steel_boots.setItemDT(6);
	steel_boots.setItemValue(400);
	all_items.emplace_back(steel_boots);
	all_blacksmith_items.emplace_back(steel_boots);

	/*
	*
	*		WEAPONS: SWORDS
	*
	*/

	iron_shortsword.setItemSprite("\\sprites\\weapons\\swords\\iron_shortsword.txt");
	iron_shortsword.setItemName("Iron Shortsword");
	iron_shortsword.setItemType("Weapon");
	iron_shortsword.setItemDam(0);
	iron_shortsword.setItemDT(6);
	iron_shortsword.setItemValue(400);
	all_items.emplace_back(iron_shortsword);
	all_blacksmith_items.emplace_back(iron_shortsword);

	iron_scimitar.setItemSprite("\\sprites\\weapons\\swords\\iron_scimitar.txt");
	iron_scimitar.setItemName("Iron Scimitar");
	iron_scimitar.setItemType("Weapon");
	iron_scimitar.setItemDam(0);
	iron_scimitar.setItemDT(6);
	iron_scimitar.setItemValue(400);
	all_items.emplace_back(iron_scimitar);
	all_blacksmith_items.emplace_back(iron_scimitar);

	steel_scimitar.setItemSprite("\\sprites\\weapons\\swords\\steel_scimitar.txt");
	steel_scimitar.setItemName("Steel Scimitar");
	steel_scimitar.setItemType("Weapon");
	steel_scimitar.setItemDam(0);
	steel_scimitar.setItemDT(6);
	steel_scimitar.setItemValue(400);
	all_items.emplace_back(steel_scimitar);
	all_blacksmith_items.emplace_back(steel_scimitar);

	steel_longsword.setItemSprite("\\sprites\\weapons\\swords\\steel_longsword.txt");
	steel_longsword.setItemName("Steel Longsword");
	steel_longsword.setItemType("Weapon");
	steel_longsword.setItemDam(0);
	steel_longsword.setItemDT(6);
	steel_longsword.setItemValue(400);
	all_items.emplace_back(steel_longsword);
	all_blacksmith_items.emplace_back(steel_longsword);

	fine_steel_longsword.setItemSprite("\\sprites\\weapons\\swords\\steel_longsword.txt");
	fine_steel_longsword.setItemName("Steel Longsword");
	fine_steel_longsword.setItemType("Weapon");
	fine_steel_longsword.setItemDam(0);
	fine_steel_longsword.setItemDT(6);
	fine_steel_longsword.setItemValue(400);
	all_items.emplace_back(fine_steel_longsword);
	all_blacksmith_items.emplace_back(fine_steel_longsword);

	steel_claymore.setItemSprite("\\sprites\\weapons\\swords\\steel_claymore.txt");
	steel_claymore.setItemName("Steel Claymore");
	steel_claymore.setItemType("Weapon");
	steel_claymore.setItemDam(0);
	steel_claymore.setItemDT(5);
	steel_claymore.setItemValue(400);
	all_items.emplace_back(steel_claymore);
	all_blacksmith_items.emplace_back(steel_claymore);

	/*
	*
	*		WEAPONS: MACES
	*
	*/

	short_iron_cudgel.setItemSprite("\\sprites\\weapons\\maces\\short_iron_cudgel.txt");
	short_iron_cudgel.setItemName("Short Iron Cudgel");
	short_iron_cudgel.setItemType("Weapon");
	short_iron_cudgel.setItemDam(0);
	short_iron_cudgel.setItemDT(5);
	short_iron_cudgel.setItemValue(400);
	all_items.emplace_back(short_iron_cudgel);
	all_blacksmith_items.emplace_back(short_iron_cudgel);

	iron_mace.setItemSprite("\\sprites\\weapons\\maces\\iron_mace.txt");
	iron_mace.setItemName("Iron Mace");
	iron_mace.setItemType("Weapon");
	iron_mace.setItemDam(0);
	iron_mace.setItemDT(5);
	iron_mace.setItemValue(400);
	all_items.emplace_back(iron_mace);
	all_blacksmith_items.emplace_back(iron_mace);

	steel_mace.setItemSprite("\\sprites\\weapons\\maces\\steel_mace.txt");
	steel_mace.setItemName("Steel Mace");
	steel_mace.setItemType("Weapon");
	steel_mace.setItemDam(0);
	steel_mace.setItemDT(5);
	steel_mace.setItemValue(400);
	all_items.emplace_back(steel_mace);
	all_blacksmith_items.emplace_back(steel_mace);

	steel_mace.setItemSprite("\\sprites\\weapons\\maces\\heavy_steel_morning_star.txt");
	steel_mace.setItemName("Heavy Steel Morning Star");
	steel_mace.setItemType("Weapon");
	steel_mace.setItemDam(0);
	steel_mace.setItemDT(5);
	steel_mace.setItemValue(400);
	all_items.emplace_back(heavy_steel_morning_star);
	all_blacksmith_items.emplace_back(heavy_steel_morning_star);

	/*
	*
	*		WEAPONS: SPEARS
	*
	*/

	simple_spear.setItemSprite("\\sprites\\weapons\\spears\\simple_spear.txt");
	simple_spear.setItemName("Simple Spear");
	simple_spear.setItemType("Weapon");
	simple_spear.setItemDam(0);
	simple_spear.setItemDT(5);
	simple_spear.setItemValue(400);
	all_items.emplace_back(simple_spear);
	all_blacksmith_items.emplace_back(simple_spear);

	iron_spear.setItemSprite("\\sprites\\weapons\\spears\\iron_spear.txt");
	iron_spear.setItemName("Iron Spear");
	iron_spear.setItemType("Weapon");
	iron_spear.setItemDam(0);
	iron_spear.setItemDT(5);
	iron_spear.setItemValue(400);
	all_items.emplace_back(iron_spear);
	all_blacksmith_items.emplace_back(iron_spear);

	steel_spear.setItemSprite("\\sprites\\weapons\\spears\\steel_spear.txt");
	steel_spear.setItemName("Steel Spear");
	steel_spear.setItemType("Weapon");
	steel_spear.setItemDam(0);
	steel_spear.setItemDT(5);
	steel_spear.setItemValue(400);
	all_items.emplace_back(steel_spear);
	all_blacksmith_items.emplace_back(steel_spear);

	/*
	*
	*		WEAPONS: DAGGERS
	*
	*/

	iron_dirk.setItemSprite("\\sprites\\weapons\\daggers\\iron_dirk.txt");
	iron_dirk.setItemName("Iron Dirk");
	iron_dirk.setItemType("Weapon");
	iron_dirk.setItemDam(0);
	iron_dirk.setItemDT(5);
	iron_dirk.setItemValue(400);
	all_items.emplace_back(iron_dirk);
	all_blacksmith_items.emplace_back(iron_dirk);

	steel_dirk.setItemSprite("\\sprites\\weapons\\daggers\\steel_dirk.txt");
	steel_dirk.setItemName("Steel Dirk");
	steel_dirk.setItemType("Weapon");
	steel_dirk.setItemDam(0);
	steel_dirk.setItemDT(5);
	steel_dirk.setItemValue(400);
	all_items.emplace_back(steel_dirk);
	all_blacksmith_items.emplace_back(steel_dirk);

	iron_dagger.setItemSprite("\\sprites\\weapons\\daggers\\iron_dagger.txt");
	iron_dagger.setItemName("Iron Dagger");
	iron_dagger.setItemType("Weapon");
	iron_dagger.setItemDam(0);
	iron_dagger.setItemDT(5);
	iron_dagger.setItemValue(400);
	all_items.emplace_back(iron_dagger);
	all_blacksmith_items.emplace_back(iron_dagger);

	steel_dagger.setItemSprite("\\sprites\\weapons\\daggers\\steel_dagger.txt");
	steel_dagger.setItemName("Steel Dagger");
	steel_dagger.setItemType("Weapon");
	steel_dagger.setItemDam(0);
	steel_dagger.setItemDT(5);
	steel_dagger.setItemValue(400);
	all_items.emplace_back(steel_dagger);
	all_blacksmith_items.emplace_back(steel_dagger);

	long_steel_dagger.setItemSprite("\\sprites\\weapons\\daggers\\long_steel_dagger.txt");
	long_steel_dagger.setItemName("Long Steel Dagger");
	long_steel_dagger.setItemType("Weapon");
	long_steel_dagger.setItemDam(0);
	long_steel_dagger.setItemDT(5);
	long_steel_dagger.setItemValue(400);
	all_items.emplace_back(long_steel_dagger);
	all_blacksmith_items.emplace_back(long_steel_dagger);

	lords_steel_dagger.setItemSprite("\\sprites\\weapons\\daggers\\lords_steel_dagger.txt");
	lords_steel_dagger.setItemName("Lord\'s Steel Dagger");
	lords_steel_dagger.setItemType("Weapon");
	lords_steel_dagger.setItemDam(0);
	lords_steel_dagger.setItemDT(5);
	lords_steel_dagger.setItemValue(400);
	all_items.emplace_back(lords_steel_dagger);
	all_blacksmith_items.emplace_back(lords_steel_dagger);

	/*
	*
	*		WEAPONS: HAMMERS
	*
	*/

	iron_hammer.setItemSprite("\\sprites\\weapons\\daggers\\iron_hammer.txt");
	iron_hammer.setItemName("Iron Hammer");
	iron_hammer.setItemType("Weapon");
	iron_hammer.setItemDam(0);
	iron_hammer.setItemDT(5);
	iron_hammer.setItemValue(400);
	all_items.emplace_back(iron_hammer);
	all_blacksmith_items.emplace_back(iron_hammer);

	crude_iron_maul.setItemSprite("\\sprites\\weapons\\daggers\\crude_iron_maul.txt");
	crude_iron_maul.setItemName("Crude Iron Maul");
	crude_iron_maul.setItemType("Weapon");
	crude_iron_maul.setItemDam(0);
	crude_iron_maul.setItemDT(5);
	crude_iron_maul.setItemValue(400);
	all_items.emplace_back(crude_iron_maul);
	all_blacksmith_items.emplace_back(crude_iron_maul);

	fine_steel_hammer.setItemSprite("\\sprites\\weapons\\daggers\\fine_steel_hammer.txt");
	fine_steel_hammer.setItemName("Fine Steel Hammer");
	fine_steel_hammer.setItemType("Weapon");
	fine_steel_hammer.setItemDam(0);
	fine_steel_hammer.setItemDT(5);
	fine_steel_hammer.setItemValue(400);
	all_items.emplace_back(fine_steel_hammer);
	all_blacksmith_items.emplace_back(fine_steel_hammer);

	steel_warhammer.setItemSprite("\\sprites\\weapons\\daggers\\steel_warhammer.txt");
	steel_warhammer.setItemName("Steel Warhammer");
	steel_warhammer.setItemType("Weapon");
	steel_warhammer.setItemDam(0);
	steel_warhammer.setItemDT(5);
	steel_warhammer.setItemValue(400);
	all_items.emplace_back(steel_warhammer);
	all_blacksmith_items.emplace_back(steel_warhammer);

	/*
	*
	*		WEAPONS: AXES
	*
	*/

	iron_hatchet.setItemSprite("\\sprites\\weapons\\daggers\\iron_hatchet.txt");
	iron_hatchet.setItemName("Iron Hatchet");
	iron_hatchet.setItemType("Weapon");
	iron_hatchet.setItemDam(0);
	iron_hatchet.setItemDT(5);
	iron_hatchet.setItemValue(400);
	all_items.emplace_back(iron_hatchet);
	all_blacksmith_items.emplace_back(iron_hatchet);

	steel_hatchet.setItemSprite("\\sprites\\weapons\\daggers\\steel_hatchet.txt");
	steel_hatchet.setItemName("Steel Hatchet");
	steel_hatchet.setItemType("Weapon");
	steel_hatchet.setItemDam(0);
	steel_hatchet.setItemDT(5);
	steel_hatchet.setItemValue(400);
	all_items.emplace_back(steel_hatchet);
	all_blacksmith_items.emplace_back(steel_hatchet);

	iron_battleaxe.setItemSprite("\\sprites\\weapons\\daggers\\iron_battleaxe.txt");
	iron_battleaxe.setItemName("Iron Battleaxe");
	iron_battleaxe.setItemType("Weapon");
	iron_battleaxe.setItemDam(0);
	iron_battleaxe.setItemDT(5);
	iron_battleaxe.setItemValue(400);
	all_items.emplace_back(iron_battleaxe);
	all_blacksmith_items.emplace_back(iron_battleaxe);

	steel_war_axe.setItemSprite("\\sprites\\weapons\\daggers\\steel_war_axe.txt");
	steel_war_axe.setItemName("Steel War Axe");
	steel_war_axe.setItemType("Weapon");
	steel_war_axe.setItemDam(0);
	steel_war_axe.setItemDT(5);
	steel_war_axe.setItemValue(400);
	all_items.emplace_back(steel_war_axe);
	all_blacksmith_items.emplace_back(steel_war_axe);

	steel_battleaxe.setItemSprite("\\sprites\\weapons\\daggers\\steel_battleaxe.txt");
	steel_battleaxe.setItemName("Steel Battlexe");
	steel_battleaxe.setItemType("Weapon");
	steel_battleaxe.setItemDam(0);
	steel_battleaxe.setItemDT(5);
	steel_battleaxe.setItemValue(400);
	all_items.emplace_back(steel_battleaxe);
	all_blacksmith_items.emplace_back(steel_battleaxe);

	/*
	*
	*		SHIELDS
	*
	*/

	painted_wooden_buckler.setItemSprite("\\sprites\\shields\\painted_wooden_buckler.txt");
	painted_wooden_buckler.setItemName("Painted Wooden Buckler");
	painted_wooden_buckler.setItemType("Shield");
	painted_wooden_buckler.setItemDam(0);
	painted_wooden_buckler.setItemDT(5);
	painted_wooden_buckler.setItemValue(400);
	all_items.emplace_back(painted_wooden_buckler);
	all_blacksmith_items.emplace_back(painted_wooden_buckler);

	iron_round_shield.setItemSprite("\\sprites\\shields\\iron_round_shield.txt");
	iron_round_shield.setItemName("Iron Round Shield");
	iron_round_shield.setItemType("Shield");
	iron_round_shield.setItemDam(0);
	iron_round_shield.setItemDT(5);
	iron_round_shield.setItemValue(400);
	all_items.emplace_back(iron_round_shield);
	all_blacksmith_items.emplace_back(iron_round_shield);

	steel_round_shield.setItemSprite("\\sprites\\shields\\steel_round_shield.txt");
	steel_round_shield.setItemName("Steel Round Shield");
	steel_round_shield.setItemType("Shield");
	steel_round_shield.setItemDam(0);
	steel_round_shield.setItemDT(5);
	steel_round_shield.setItemValue(400);
	all_items.emplace_back(steel_round_shield);
	all_blacksmith_items.emplace_back(steel_round_shield);

	steel_kite_shield.setItemSprite("\\sprites\\shields\\steel_kite_shield.txt");
	steel_kite_shield.setItemName("Steel Kite Shield");
	steel_kite_shield.setItemType("Shield");
	steel_kite_shield.setItemDam(0);
	steel_kite_shield.setItemDT(5);
	steel_kite_shield.setItemValue(400);
	all_items.emplace_back(steel_kite_shield);
	all_blacksmith_items.emplace_back(steel_kite_shield);

	fine_steel_heater_shield.setItemSprite("\\sprites\\shields\\fine_steel_heater_shield.txt");
	fine_steel_heater_shield.setItemName("Fine Steel Heater Shield");
	fine_steel_heater_shield.setItemType("Shield");
	fine_steel_heater_shield.setItemDam(0);
	fine_steel_heater_shield.setItemDT(5);
	fine_steel_heater_shield.setItemValue(400);
	all_items.emplace_back(fine_steel_heater_shield);
	all_blacksmith_items.emplace_back(fine_steel_heater_shield);

	/*
	*
	*		CONSUMABLES: FOOD
	*
	*/

	apple.setItemSprite("\\sprites\\consumables\\food\\apple.txt");
	apple.setItemName("Apple");
	apple.setItemType("Food");
	apple.setItemDam(0);
	apple.setItemDT(6);
	apple.setItemValue(400);
	all_items.emplace_back(apple);
	all_grocer_items.emplace_back(apple);

	cheese_wedge.setItemSprite("\\sprites\\consumables\\food\\cheese_wedge.txt");
	cheese_wedge.setItemName("Cheese Wedge");
	cheese_wedge.setItemType("Food");
	cheese_wedge.setItemDam(0);
	cheese_wedge.setItemDT(6);
	cheese_wedge.setItemValue(400);
	all_items.emplace_back(cheese_wedge);
	all_grocer_items.emplace_back(cheese_wedge);

	fancy_cheese.setItemSprite("\\sprites\\consumables\\food\\fancy_cheese.txt");
	fancy_cheese.setItemName("Fancy Cheese");
	fancy_cheese.setItemType("Food");
	fancy_cheese.setItemDam(0);
	fancy_cheese.setItemDT(6);
	fancy_cheese.setItemValue(400);
	all_items.emplace_back(fancy_cheese);
	all_grocer_items.emplace_back(fancy_cheese);

	fig.setItemSprite("\\sprites\\consumables\\food\\fig.txt");
	fig.setItemName("Fig");
	fig.setItemType("Food");
	fig.setItemDam(0);
	fig.setItemDT(6);
	fig.setItemValue(400);
	all_items.emplace_back(fig);
	all_grocer_items.emplace_back(fig);

	melon.setItemSprite("\\sprites\\consumables\\food\\melon.txt");
	melon.setItemName("Melon");
	melon.setItemType("Food");
	melon.setItemDam(0);
	melon.setItemDT(6);
	melon.setItemValue(400);
	all_items.emplace_back(melon);
	all_grocer_items.emplace_back(melon);

	potatoes.setItemSprite("\\sprites\\consumables\\food\\potatoes.txt");
	potatoes.setItemName("Potatoes");
	potatoes.setItemType("Food");
	potatoes.setItemDam(0);
	potatoes.setItemDT(6);
	potatoes.setItemValue(400);
	all_items.emplace_back(potatoes);
	all_grocer_items.emplace_back(potatoes);

	prime_rib.setItemSprite("\\sprites\\consumables\\food\\prime_rib.txt");
	prime_rib.setItemName("Prime Rib");
	prime_rib.setItemType("Food");
	prime_rib.setItemDam(0);
	prime_rib.setItemDT(6);
	prime_rib.setItemValue(400);
	all_items.emplace_back(prime_rib);
	all_grocer_items.emplace_back(prime_rib);

	tbone_steak.setItemSprite("\\sprites\\consumables\\food\\tbone_steak.txt");
	tbone_steak.setItemName("Prime Rib");
	tbone_steak.setItemType("Food");
	tbone_steak.setItemDam(0);
	tbone_steak.setItemDT(6);
	tbone_steak.setItemValue(400);
	all_items.emplace_back(tbone_steak);
	all_grocer_items.emplace_back(tbone_steak);

	turkey_leg.setItemSprite("\\sprites\\consumables\\food\\turkey_leg.txt");
	turkey_leg.setItemName("Turkey Leg");
	turkey_leg.setItemType("Food");
	turkey_leg.setItemDam(0);
	turkey_leg.setItemDT(6);
	turkey_leg.setItemValue(400);
	all_items.emplace_back(turkey_leg);
	all_grocer_items.emplace_back(turkey_leg);

	wheel_of_cheese.setItemSprite("\\sprites\\consumables\\food\\wheel_of_cheese.txt");
	wheel_of_cheese.setItemName("Wheel of Cheese");
	wheel_of_cheese.setItemType("Food");
	wheel_of_cheese.setItemDam(0);
	wheel_of_cheese.setItemDT(6);
	wheel_of_cheese.setItemValue(400);
	all_items.emplace_back(wheel_of_cheese);
	all_grocer_items.emplace_back(wheel_of_cheese);

	/*
	*
	*		CONSUMABLES: POTIONS
	*
	*/

	rope.setItemSprite("\\sprites\\tools\\rope.txt");
	rope.setItemName("Rope");
	rope.setItemType("Tool");
	rope.setItemDam(0);
	rope.setItemDT(6);
	rope.setItemValue(400);
	all_items.emplace_back(rope);
	all_grocer_items.emplace_back(rope);

	spade.setItemSprite("\\sprites\\tools\\spade.txt");
	spade.setItemName("Spade");
	spade.setItemType("Tool");
	spade.setItemDam(0);
	spade.setItemDT(6);
	spade.setItemValue(400);
	all_items.emplace_back(spade);
	all_grocer_items.emplace_back(spade);

	torch.setItemSprite("\\sprites\\tools\\torch.txt");
	torch.setItemName("Torch");
	torch.setItemType("Tool");
	torch.setItemDam(0);
	torch.setItemDT(6);
	torch.setItemValue(400);
	all_items.emplace_back(torch);
	all_grocer_items.emplace_back(torch);

	/*
	*
	*		CONSUMABLES: POTIONS
	*
	*/

	health_potion.setItemSprite("\\sprites\\consumables\\potions\\health_potion.txt");
	health_potion.setItemName("Health Potion");
	health_potion.setItemType("Potion");
	health_potion.setItemDam(0);
	health_potion.setItemDT(6);
	health_potion.setItemValue(400);
	all_items.emplace_back(health_potion);
	all_grocer_items.emplace_back(health_potion);

	fancy_health_potion.setItemSprite("\\sprites\\consumables\\potions\\fancy_health_potion.txt");
	fancy_health_potion.setItemName("Fancy Health Potion");
	fancy_health_potion.setItemType("Potion");
	fancy_health_potion.setItemDam(0);
	fancy_health_potion.setItemDT(6);
	fancy_health_potion.setItemValue(400);
	all_items.emplace_back(fancy_health_potion);
	all_grocer_items.emplace_back(fancy_health_potion);
}

void Game::initialize_all_towns() {

	/*

			Towns

	*/

	// Thowerd - Named for Todd Howard and the influence of his games on my life
	thowerd.setLocationX(68);
	thowerd.setLocationY(44);
	thowerd.setScreen("\\locations\\towns\\Thowerd_Platz.txt");
	thowerd.setTownAuxScreens("\\locations\\towns\\Thowerd_Smith.txt",
		"\\locations\\towns\\Thowerd_Grocer.txt",
		"\\locations\\towns\\Thowerd_Tavern.txt");
	all_towns.emplace_back(thowerd);

	// Cainton - Named for Tim Cain, lead designer of Fallout (Post-Nuclear CRPG, 1997); Fallout and Fqllout 2 are two of my favorite things ever created
	cainton.setLocationX(92);
	cainton.setLocationY(27);
	cainton.setScreen("\\locations\\towns\\Cainton_Platz.txt");
	cainton.setTownAuxScreens("\\locations\\towns\\Cainton_Smith.txt",
		"\\locations\\towns\\Cainton_Grocer.txt",
		"\\locations\\towns\\Cainton_Tavern.txt");
	all_towns.emplace_back(cainton);
	

	// Prince's Reproach - Named after my cat, Prince. Note the potential dual meanings: is the Prince receiving repraoch, or is he expressing reproach for something/someone? Prince is a gemini, as my partner likes to remind him.
	princes_reproach.setLocationX(106);
	princes_reproach.setLocationY(43);
	princes_reproach.setScreen("\\locations\\towns\\Princes_Reproach_Platz.txt");
	princes_reproach.setTownAuxScreens("\\locations\\towns\\Princes_Reproach_Smith.txt",
		"\\locations\\towns\\Princes_Reproach_Grocer.txt",
		"\\locations\\towns\\Princes_Reproach_Tavern.txt",
		"\\locations\\towns\\Princes_Reproach_Alley.txt");
	all_towns.emplace_back(princes_reproach);

	// Daphnon - Named after my cat, Daphnis. Daphnon is a transliteration of the ancient greek word meaning "Of the laurels" (N.B., ancient greek city names are typically in the genitive plural form).
	daphnon.setLocationX(112);
	daphnon.setLocationY(56);
	daphnon.setScreen("\\locations\\towns\\Daphnon_Platz.txt");
	daphnon.setTownAuxScreens("\\locations\\towns\\Daphnon_Smith.txt",
		"\\locations\\towns\\Daphnon_Grocer.txt",
		"\\locations\\towns\\Daphnon_Tavern.txt",
		"\\locations\\towns\\Daphnon_Alley.txt");
	all_towns.emplace_back(daphnon);

}