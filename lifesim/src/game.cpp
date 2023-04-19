#include <game.h>

namespace fs = std::filesystem;

const int MAP_MAX_ROWS = 86;
const int MAP_MAX_COLS = 300;
char gameMap[MAP_MAX_ROWS][MAP_MAX_COLS];
char gameMapCopy[MAP_MAX_ROWS][MAP_MAX_COLS];

Game::Game() {
	day = 1;
	season = "Spring";
	seasonCount = 1;
	year = 300;

	/*
	*
	*		ARMOR: HELMETS
	*
	*/

	all_items.emplace_back(tusk_helm);
	all_blacksmith_items.emplace_back(tusk_helm);

	all_items.emplace_back(leather_soldiers_helmet);
	all_blacksmith_items.emplace_back(leather_soldiers_helmet);

	all_items.emplace_back(plain_bascinet);
	all_blacksmith_items.emplace_back(plain_bascinet);

	all_items.emplace_back(mail_coif);
	all_blacksmith_items.emplace_back(mail_coif);

	all_items.emplace_back(iron_soldiers_cap);
	all_blacksmith_items.emplace_back(iron_soldiers_cap);

	all_items.emplace_back(steel_helm);
	all_blacksmith_items.emplace_back(steel_helm);

	all_items.emplace_back(spiked_great_helm);
	all_blacksmith_items.emplace_back(spiked_great_helm);

	all_items.emplace_back(frog_mouth_great_helm);
	all_blacksmith_items.emplace_back(frog_mouth_great_helm);

	all_items.emplace_back(ancient_helm);
	all_blacksmith_items.emplace_back(ancient_helm);

	/*
	*
	*		ARMOR: CHEST
	*
	*/

	all_items.emplace_back(wool_gambeson);
	all_blacksmith_items.emplace_back(wool_gambeson);

	all_items.emplace_back(leather_gambeson);
	all_blacksmith_items.emplace_back(leather_gambeson);

	all_items.emplace_back(heavy_padded_wool_gambeson);
	all_blacksmith_items.emplace_back(heavy_padded_wool_gambeson);

	all_items.emplace_back(leather_brigandine);
	all_blacksmith_items.emplace_back(leather_brigandine);

	all_items.emplace_back(heavy_leather_gambeson);
	all_blacksmith_items.emplace_back(heavy_leather_gambeson);

	all_items.emplace_back(lamellar_cuirass);
	all_blacksmith_items.emplace_back(lamellar_cuirass);

	all_items.emplace_back(light_iron_plate_armor);
	all_blacksmith_items.emplace_back(light_iron_plate_armor);

	all_items.emplace_back(light_steel_plate_armor);
	all_blacksmith_items.emplace_back(light_steel_plate_armor);

	all_items.emplace_back(steel_cuirass);
	all_blacksmith_items.emplace_back(steel_cuirass);

	/*
	*
	*		ARMOR: GLOVES
	*
	*/

	all_items.emplace_back(leather_gloves);
	all_blacksmith_items.emplace_back(leather_gloves);

	all_items.emplace_back(iron_gauntlets);
	all_blacksmith_items.emplace_back(iron_gauntlets);

	all_items.emplace_back(steel_gauntlets);
	all_blacksmith_items.emplace_back(steel_gauntlets);

	/*
	*
	*		ARMOR: LEGS
	*
	*/

	all_items.emplace_back(leather_tassets);
	all_blacksmith_items.emplace_back(leather_tassets);

	all_items.emplace_back(padded_cloth_chausses);
	all_blacksmith_items.emplace_back(padded_cloth_chausses);

	all_items.emplace_back(heavy_leather_chausses);
	all_blacksmith_items.emplace_back(heavy_leather_chausses);

	all_items.emplace_back(mail_chausses);
	all_blacksmith_items.emplace_back(mail_chausses);

	all_items.emplace_back(steel_tassets);
	all_blacksmith_items.emplace_back(steel_tassets);

	/*
	*
	*		ARMOR: BOOTS
	*
	*/

	all_items.emplace_back(leather_boots);
	all_blacksmith_items.emplace_back(leather_boots);

	all_items.emplace_back(fancy_riding_boots);
	all_blacksmith_items.emplace_back(fancy_riding_boots);

	all_items.emplace_back(iron_boots);
	all_blacksmith_items.emplace_back(iron_boots);

	all_items.emplace_back(steel_boots);
	all_blacksmith_items.emplace_back(steel_boots);

	/*
	*
	*		WEAPONS: SWORDS
	*
	*/

	all_items.emplace_back(iron_shortsword);
	all_blacksmith_items.emplace_back(iron_shortsword);

	all_items.emplace_back(iron_scimitar);
	all_blacksmith_items.emplace_back(iron_scimitar);

	all_items.emplace_back(steel_scimitar);
	all_blacksmith_items.emplace_back(steel_scimitar);

	all_items.emplace_back(steel_longsword);
	all_blacksmith_items.emplace_back(steel_longsword);

	all_items.emplace_back(fine_steel_longsword);
	all_blacksmith_items.emplace_back(fine_steel_longsword);

	all_items.emplace_back(reinforced_steel_claymore);
	all_blacksmith_items.emplace_back(reinforced_steel_claymore);

	/*
	*
	*		WEAPONS: MACES
	*
	*/

	all_items.emplace_back(short_iron_cudgel);
	all_blacksmith_items.emplace_back(short_iron_cudgel);

	all_items.emplace_back(iron_mace);
	all_blacksmith_items.emplace_back(iron_mace);

	all_items.emplace_back(steel_mace);
	all_blacksmith_items.emplace_back(steel_mace);

	all_items.emplace_back(heavy_steel_morning_star);
	all_blacksmith_items.emplace_back(heavy_steel_morning_star);

	/*
	*
	*		WEAPONS: SPEARS
	*
	*/

	all_items.emplace_back(simple_spear);
	all_blacksmith_items.emplace_back(simple_spear);

	all_items.emplace_back(iron_spear);
	all_blacksmith_items.emplace_back(iron_spear);

	all_items.emplace_back(steel_spear);
	all_blacksmith_items.emplace_back(steel_spear);

	/*
	*
	*		WEAPONS: DAGGERS
	*
	*/

	all_items.emplace_back(iron_dirk);
	all_blacksmith_items.emplace_back(iron_dirk);

	all_items.emplace_back(iron_dagger);
	all_blacksmith_items.emplace_back(iron_dagger);

	all_items.emplace_back(steel_dirk);
	all_blacksmith_items.emplace_back(steel_dirk);

	all_items.emplace_back(steel_dagger);
	all_blacksmith_items.emplace_back(steel_dagger);

	all_items.emplace_back(long_steel_dagger);
	all_blacksmith_items.emplace_back(long_steel_dagger);

	all_items.emplace_back(lords_steel_dagger);
	all_blacksmith_items.emplace_back(lords_steel_dagger);

	/*
	*
	*		WEAPONS: HAMMERS
	*
	*/

	all_items.emplace_back(iron_hammer);
	all_blacksmith_items.emplace_back(iron_hammer);

	all_items.emplace_back(crude_iron_maul);
	all_blacksmith_items.emplace_back(crude_iron_maul);

	all_items.emplace_back(fine_steel_hammer);
	all_blacksmith_items.emplace_back(fine_steel_hammer);

	all_items.emplace_back(reinforced_steel_warhammer);
	all_blacksmith_items.emplace_back(reinforced_steel_warhammer);

	/*
	*
	*		WEAPONS: AXES
	*
	*/

	all_items.emplace_back(iron_hatchet);
	all_blacksmith_items.emplace_back(iron_hatchet);

	all_items.emplace_back(steel_hatchet);
	all_blacksmith_items.emplace_back(steel_hatchet);

	all_items.emplace_back(iron_battleaxe);
	all_blacksmith_items.emplace_back(iron_battleaxe);

	all_items.emplace_back(steel_war_axe);
	all_blacksmith_items.emplace_back(steel_war_axe);

	all_items.emplace_back(steel_battleaxe);
	all_blacksmith_items.emplace_back(steel_battleaxe);

	/*
	*
	*		SHIELDS
	*
	*/

	all_items.emplace_back(painted_wooden_buckler);
	all_blacksmith_items.emplace_back(painted_wooden_buckler);

	all_items.emplace_back(iron_round_shield);
	all_blacksmith_items.emplace_back(iron_round_shield);

	all_items.emplace_back(steel_round_shield);
	all_blacksmith_items.emplace_back(steel_round_shield);

	all_items.emplace_back(steel_kite_shield);
	all_blacksmith_items.emplace_back(steel_kite_shield);

	all_items.emplace_back(fine_steel_heater_shield);
	all_blacksmith_items.emplace_back(fine_steel_heater_shield);
	/*
	*
	*		CONSUMABLES: FOOD
	*
	*/

	all_items.emplace_back(apple);
	all_grocer_items.emplace_back(apple);

	all_items.emplace_back(cheese_wedge);
	all_grocer_items.emplace_back(cheese_wedge);

	all_items.emplace_back(fancy_cheese);
	all_grocer_items.emplace_back(fancy_cheese);

	all_items.emplace_back(fig);
	all_grocer_items.emplace_back(fig);

	all_items.emplace_back(melon);
	all_grocer_items.emplace_back(melon);

	all_items.emplace_back(potatoes);
	all_grocer_items.emplace_back(potatoes);

	all_items.emplace_back(prime_rib);
	all_grocer_items.emplace_back(prime_rib);

	all_items.emplace_back(tbone_steak);
	all_grocer_items.emplace_back(tbone_steak);

	all_items.emplace_back(turkey_leg);
	all_grocer_items.emplace_back(turkey_leg);

	all_items.emplace_back(wheel_of_cheese);
	all_grocer_items.emplace_back(wheel_of_cheese);

	all_items.emplace_back(barrel_of_oats);
	all_items.emplace_back(barrel_of_beans);


	/*
	*
	*		TOOLA
	*
	*/

	all_items.emplace_back(rope);
	all_grocer_items.emplace_back(rope);

	all_items.emplace_back(spade);
	all_grocer_items.emplace_back(spade);

	all_items.emplace_back(torch);
	all_grocer_items.emplace_back(torch);

	/*
	*
	*		CONSUMABLES: POTIONS
	*
	*/

	all_items.emplace_back(health_potion);
	all_grocer_items.emplace_back(health_potion);

	all_items.emplace_back(fancy_health_potion);
	all_grocer_items.emplace_back(fancy_health_potion);

	all_items.emplace_back(coffee);
	all_tavern_items.emplace_back(coffee);

	all_items.emplace_back(beer);
	all_tavern_items.emplace_back(beer);


	/*

			Towns

	*/

	all_towns.emplace_back(thowerd);
	all_towns.emplace_back(cainton);
	all_towns.emplace_back(princes_reproach);
	all_towns.emplace_back(daphnon);
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
	//Initialize the game map
	initMap();

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
	std::string userString = "";
	bool failed = true;

	// Get rid of failure state
	std::cin.clear();

	// Discard 'bad' character(s) 
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	while (failed == true) {
		std::getline(std::cin, userString, '\n');

		if (std::cin.fail()) {
			std::cout << "==================================================" << std::endl;
			std::cout << "               ERROR! Invalid Input               " << std::endl;
			std::cout << "==================================================" << std::endl;
			std::cout << std::endl;


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
				std::shared_ptr<Player> loaded = std::make_shared<Player>();

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

				// Clear the inventories
				clear_all_inventories();

				// Use an int to count lines
				//		Line  0. Player Stats
				//		      1. Player carriedItems
				//		      2. Player equippedItems
				//		      3. player purse
				//		      4. blacksmith carriedItems
				//		      5. blacksmith maxTransaction
				//		      6. grocer carriedItems
				//		      7. grocer maxTransaction
				//		      8. tavern carriedItems
				//		      9. tavern maxTransaction
				//		     10. pendel carriedItems
				//		     11. pendel maxTransaction
				//		     12. scharfy carriedItems
				//		     13. scharfy maxTransaction
				int lineCount = 0;

				// Read each line of the file and extract data into variables
				std::string line;
				while (std::getline(file, line)) {
					//			line 0: Player stats
					if (lineCount == 0) {
						// Declare variables to store data
						std::string s1, s2, s3, s4, s5, s6;
						std::string throwaway;
						// Extract data from each column and store in variables
						std::istringstream iss(line);
						std::getline(iss, s1, ',');
						std::getline(iss, s2, ',');
						std::getline(iss, s3, ',');
						std::getline(iss, s4, ',');
						std::getline(iss, s5, ',');
						std::getline(iss, s6, ',');
						std::getline(iss, throwaway, '\n');

						// Set name
						loaded->setName(s1);
						// Set isSpecial
						if (s2 == "true") {
							loaded->setIsSpecial(true);
						}
						else {
							loaded->setIsSpecial(false);
						}
						// Set hp
						loaded->setHP(stoi(s3));
						// Set maxHP
						loaded->setMaxHP(stoi(s4));

						loaded->setPlayerX(stoi(s5));
						loaded->setPlayerY(stoi(s6));
					}
					//			line 1: player carriedItems
					if (lineCount == 1) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_items.size(); i++) {
								if (all_items.at(i)->getItemName() == itemName) {
									playerInventory->incrementCarriedItem(all_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 2: player equippedItems
					if (lineCount == 2) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_blacksmith_items.size(); i++) {
								if (all_blacksmith_items.at(i)->getItemName() == itemName) {
									playerInventory->equipItem(all_blacksmith_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 3: player purse
					if (lineCount == 3) {
						std::istringstream iss(line);
						std::string s1, s2, s3, s4;
						std::string throwaway;
						// read in purse data
						std::getline(iss, s1, ',');
						std::getline(iss, s2, ',');
						std::getline(iss, s3, ',');
						std::getline(iss, s4, ',');
						playerInventory->setCurrency(stoi(s1), stoi(s2), stoi(s3), stoi(s4));
						std::getline(iss, throwaway, '\n');
					}
					//			line 4: blacksmith carriedItems
					if (lineCount == 4) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_blacksmith_items.size(); i++) {
								if (all_blacksmith_items.at(i)->getItemName() == itemName) {
									blackSmithInventory->incrementCarriedItem(all_blacksmith_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 5: blacksmith maxTransaction
					if (lineCount == 5) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						blackSmithInventory->setMaxTransaction(stoi(maxTransStr));
					}
					//			line 6: grocer carriedItems
					if (lineCount == 6) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_grocer_items.size(); i++) {
								if (all_grocer_items.at(i)->getItemName() == itemName) {
									grocerInventory->incrementCarriedItem(all_grocer_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 7: grocer maxTransaction
					if (lineCount == 7) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						grocerInventory->setMaxTransaction(stoi(maxTransStr));
					}
					//			line 8: tavern carriedItems
					if (lineCount == 8) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_tavern_items.size(); i++) {
								if (all_tavern_items.at(i)->getItemName() == itemName) {
									tavernInventory->incrementCarriedItem(all_tavern_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 9: tavern maxTransaction
					if (lineCount == 9) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						tavernInventory->setMaxTransaction(stoi(maxTransStr));
					}
					//			line 10: pendel carriedItems
					if (lineCount == 10) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							pendelInventory->incrementCarriedItem(barrel_of_oats);
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 11: pendel maxTransaction
					if (lineCount == 11) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						pendelInventory->setMaxTransaction(stoi(maxTransStr));
					}
					//			line 12: scharfy carriedItems
					if (lineCount == 12) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							scharfyInventory->incrementCarriedItem(barrel_of_beans);
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 13: scharfy maxTransaction
					if (lineCount == 13) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						scharfyInventory->setMaxTransaction(stoi(maxTransStr));
					}

					// Increment lineCount after each line is loaded
					lineCount++;
				}

				for (int i = 0; i < all_towns.size(); i++) {
					all_towns.at(i)->setBlacksmithInv(blackSmithInventory);
					all_towns.at(i)->setGrocerInv(grocerInventory);
					all_towns.at(i)->setTavernInv(tavernInventory);
					if (all_towns.at(i)->getLocationName() == "Daphnon") {
						all_towns.at(i)->setAux4Inv(scharfyInventory);
					}
					if (all_towns.at(i)->getLocationName() == "Prince\'s Reproach") {
						all_towns.at(i)->setAux4Inv(pendelInventory);
					}
				}

				// Close the file stream
				file.close();

				// Welcome the player back
				std::cout << "Welcome back, " << loaded->getName() << "!" << std::endl;

				// Start the game with the loaded player data
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


void Game::loadGame(std::shared_ptr<Player> set) {

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
				std::shared_ptr<Player> loaded = std::make_shared<Player>();

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

				// Clear the inventories
				clear_all_inventories();

				// Use an int to count lines
				//		Line  0. Player Stats
				//		      1. Player carriedItems
				//		      2. Player equippedItems
				//		      3. player purse
				//		      4. blacksmith carriedItems
				//		      5. blacksmith maxTransaction
				//		      6. grocer carriedItems
				//		      7. grocer maxTransaction
				//		      8. tavern carriedItems
				//		      9. tavern maxTransaction
				//		     10. pendel carriedItems
				//		     11. pendel maxTransaction
				//		     12. scharfy carriedItems
				//		     13. scharfy maxTransaction
				int lineCount = 0;

				// Read each line of the file and extract data into variables
				std::string line;
				while (std::getline(file, line)) {
					//			line 0: Player stats
					if (lineCount == 0) {
						// Declare variables to store data
						std::string s1, s2, s3, s4, s5, s6;
						std::string throwaway;
						// Extract data from each column and store in variables
						std::istringstream iss(line);
						std::getline(iss, s1, ',');
						std::getline(iss, s2, ',');
						std::getline(iss, s3, ',');
						std::getline(iss, s4, ',');
						std::getline(iss, s5, ',');
						std::getline(iss, s6, ',');
						std::getline(iss, throwaway, '\n');

						// Set name
						loaded->setName(s1);
						// Set isSpecial
						if (s2 == "true") {
							loaded->setIsSpecial(true);
						}
						else {
							loaded->setIsSpecial(false);
						}
						// Set hp
						loaded->setHP(stoi(s3));
						// Set maxHP
						loaded->setMaxHP(stoi(s4));

						loaded->setPlayerX(stoi(s5));
						loaded->setPlayerY(stoi(s6));
					}
					//			line 1: player carriedItems
					if (lineCount == 1) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_items.size(); i++) {
								if (all_items.at(i)->getItemName() == itemName) {
									playerInventory->incrementCarriedItem(all_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 2: player equippedItems
					if (lineCount == 2) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_blacksmith_items.size(); i++) {
								if (all_blacksmith_items.at(i)->getItemName() == itemName) {
									playerInventory->equipItem(all_blacksmith_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 3: player purse
					if (lineCount == 3) {
						std::istringstream iss(line);
						std::string s1, s2, s3, s4;
						std::string throwaway;
						// read in purse data
						std::getline(iss, s1, ',');
						std::getline(iss, s2, ',');
						std::getline(iss, s3, ',');
						std::getline(iss, s4, ',');
						playerInventory->setCurrency(stoi(s1), stoi(s2), stoi(s3), stoi(s4));
						std::getline(iss, throwaway, '\n');
					}
					//			line 4: blacksmith carriedItems
					if (lineCount == 4) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_blacksmith_items.size(); i++) {
								if (all_blacksmith_items.at(i)->getItemName() == itemName) {
									blackSmithInventory->incrementCarriedItem(all_blacksmith_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 5: blacksmith maxTransaction
					if (lineCount == 5) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						blackSmithInventory->setMaxTransaction(stoi(maxTransStr));
					}
					//			line 6: grocer carriedItems
					if (lineCount == 6) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_grocer_items.size(); i++) {
								if (all_grocer_items.at(i)->getItemName() == itemName) {
									grocerInventory->incrementCarriedItem(all_grocer_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 7: grocer maxTransaction
					if (lineCount == 7) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						grocerInventory->setMaxTransaction(stoi(maxTransStr));
					}
					//			line 8: tavern carriedItems
					if (lineCount == 8) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							for (int i = 0; i < all_tavern_items.size(); i++) {
								if (all_tavern_items.at(i)->getItemName() == itemName) {
									tavernInventory->incrementCarriedItem(all_tavern_items.at(i));
								}
							}
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 9: tavern maxTransaction
					if (lineCount == 9) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						tavernInventory->setMaxTransaction(stoi(maxTransStr));
					}
					//			line 10: pendel carriedItems
					if (lineCount == 10) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							pendelInventory->incrementCarriedItem(barrel_of_oats);
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 11: pendel maxTransaction
					if (lineCount == 11) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						pendelInventory->setMaxTransaction(stoi(maxTransStr));
					}
					//			line 12: scharfy carriedItems
					if (lineCount == 12) {
						std::istringstream iss(line);
						std::string itemName;
						std::string throwaway;
						while (std::getline(iss, itemName, ',')) {
							scharfyInventory->incrementCarriedItem(barrel_of_beans);
						}
						// Call getline() to clear the newline
						std::getline(iss, throwaway, '\n');
					}
					//			line 13: scharfy maxTransaction
					if (lineCount == 13) {
						std::istringstream iss(line);
						std::string maxTransStr;
						std::string throwaway;
						std::getline(iss, maxTransStr, ',');
						std::getline(iss, throwaway, '\n');
						scharfyInventory->setMaxTransaction(stoi(maxTransStr));
					}

					// Increment lineCount after each line is loaded
					lineCount++;
				}

				for (int i = 0; i < all_towns.size(); i++) {
					all_towns.at(i)->setBlacksmithInv(blackSmithInventory);
					all_towns.at(i)->setGrocerInv(grocerInventory);
					all_towns.at(i)->setTavernInv(tavernInventory);
					if (all_towns.at(i)->getLocationName() == "Daphnon") {
						all_towns.at(i)->setAux4Inv(scharfyInventory);
					}
					if (all_towns.at(i)->getLocationName() == "Prince\'s Reproach") {
						all_towns.at(i)->setAux4Inv(pendelInventory);
					}
				}

				// Close the file stream
				file.close();

				// Welcome the player back
				std::cout << "Welcome back, " << loaded->getName() << "!" << std::endl;

				// Start the game with the loaded player data
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
	std::shared_ptr<Player> player = std::make_shared<Player>();
	// Initialize all inventories at start of new game

	// Clear then initialize all inventories
	clear_all_inventories();
	initialize_all_inventories();

	system("CLS");

	std::cout << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << std::endl;
	std::cout << "                What is your name?                " << std::endl;
	std::cout << std::endl;
	std::cout << "Enter: ";
	player->setName(getCleanString());
	player->setIsSpecial();
	player->setMaxHP(100);
	player->setHP(100);

	system("CLS");

	std::cout << "Welcome to Mundane, " << player->getName() << "!" << std::endl;

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

void Game::quitGame(std::shared_ptr<Player> setPlayer) {

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
	// Clear all inventories
	clear_all_inventories();
	// Return to main menu
	start();
}

void Game::saveGame(std::shared_ptr<Player> set) {
	// Get gameID from player
	std::cout << "               Name your save file:               " << std::endl;
	std::cout << std::endl;
	std::cout << "==================================================" << std::endl;

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, gameID, '\n');

	for (int i = 0; i < gameID.size(); i++) {
		if (gameID[i] == ' ') {
			gameID[i] = '_';
		}
	}

	// Get the user's documents folder
	char* documentsPath = nullptr;
	size_t bufferSize = 0;
	_dupenv_s(&documentsPath, &bufferSize, "USERPROFILE");
	if (documentsPath == nullptr) {
		std::cerr << "Error: Unable to determine documents folder." << std::endl;
		return;
	}

	// Create path if needed
	std::string folderName = std::string(documentsPath) + "\\Documents\\Mundane\\savegames\\";
	if (!std::filesystem::exists(folderName)) {
		if (!std::filesystem::create_directories(folderName)) {
			std::cerr << "Error: Failed to create directory." << std::endl;
			return;
		}
	}

	// Name save file according to user input
	std::string fileName = folderName + gameID + ".csv";

	std::filesystem::perms permissions = std::filesystem::status(folderName).permissions();
	if ((permissions & std::filesystem::perms::owner_write) != std::filesystem::perms::owner_write) {
		std::cerr << "Error: The program does not have write permissions for the directory." << std::endl;
		return;
	}

	// Generate a csv with player data, so players can pick up where they left off
	std::cout << std::endl << fileName << std::endl;
	std::fstream saveFile;
	saveFile.open(fileName, std::ios::out);
	if (!saveFile.is_open()) {
		std::cerr << "Error: Unable to create save file." << std::endl;
		return;
	}
	if (!saveFile.is_open()) {
		std::cerr << "Error: Unable to create save file." << std::endl;
		return;
	}


	// Write player data to csv 
	saveFile << set->getName() << ",";
	saveFile << set->getIsSpecial() << ",";
	saveFile << set->getHP() << ",";
	saveFile << set->getMaxHP() << ",";
	saveFile << set->getPlayerX() << ",";
	saveFile << set->getPlayerY() << ",";
	saveFile << "\n";

	// Write player inventory data to csv
	//		carriedItems:
	for (int i = 0; i < playerInventory->getCarriedItems().size(); i++) {
		saveFile << playerInventory->getCarriedItems().at(i)->getItemName() << ",";
	}
	saveFile << "\n";
	//		equippedItems
	for (int i = 0; i < playerInventory->getEquippedItems().size(); i++) {
		saveFile << playerInventory->getEquippedItems().at(i)->getItemName() << ",";
	}
	saveFile << "\n";
	//		purse
	saveFile << playerInventory->getCopper() << ",";
	saveFile << playerInventory->getSilver() << ",";
	saveFile << playerInventory->getGold() << ",";
	saveFile << playerInventory->getPlatinum() << "," << "\n";


	// Write vendor inventory data to csv
	//		blacksmith:
	for (int i = 0; i < blackSmithInventory->getCarriedItems().size(); i++) {
		saveFile << blackSmithInventory->getCarriedItems().at(i)->getItemName() << ",";
	}
	saveFile << "\n";
	saveFile << blackSmithInventory->getMaxTransaction() << "," << "\n";

	//		grocer
	for (int i = 0; i < grocerInventory->getCarriedItems().size(); i++) {
		saveFile << grocerInventory->getCarriedItems().at(i)->getItemName() << ",";
	}
	saveFile << "\n";
	saveFile << grocerInventory->getMaxTransaction() << "," << "\n";

	//		tavern
	for (int i = 0; i < tavernInventory->getCarriedItems().size(); i++) {
		saveFile << tavernInventory->getCarriedItems().at(i)->getItemName() << ",";
	}
	saveFile << "\n";
	saveFile << tavernInventory->getMaxTransaction() << "," << "\n";

	//		pendel
	for (int i = 0; i < pendelInventory->getCarriedItems().size(); i++) {
		saveFile << pendelInventory->getCarriedItems().at(i)->getItemName() << ",";
	}
	saveFile << "\n";
	saveFile << pendelInventory->getMaxTransaction() << "," << "\n";

	// scharfy
	for (int i = 0; i < scharfyInventory->getCarriedItems().size(); i++) {
		saveFile << scharfyInventory->getCarriedItems().at(i)->getItemName() << ",";
	}
	saveFile << "\n";
	saveFile << scharfyInventory->getMaxTransaction() << "," << "\n";



	// TODO: Include additional player data, as well as inventory data

	// Close the file
	saveFile.close();
	// Print success message
	std::cout << "Game \'" << gameID << "\' has been saved." << std::endl;
}

void Game::pauseMenu(std::shared_ptr<Player> set) {
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

void Game::runGame(std::shared_ptr<Player> set) {
	bool gameRunning = true;
	while (gameRunning) {
		std::cout << "                     Options:                     " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << "                                                  " << std::endl;
		std::cout << "                 1: Pause Menu                    " << std::endl;
		std::cout << "                 2: Journal                       " << std::endl;
		std::cout << "                 3: Stats                         " << std::endl;
		std::cout << "                 4: Inventory                     " << std::endl;
		std::cout << "                 5: Move Player                   " << std::endl;
		std::cout << "                                                  " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << std::endl;
		std::cout << "Name: " << set->getName() << " | ";
		set->printHP();
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
			std::cout << "Sorry! The \'Stats\' logic has not yet been created... Coming soon!" << std::endl;
			break;
		case 4:
			system("CLS");
			displayNeutralInventory();
			break;
		case 5:
			system("CLS");
			travMap(set);
		default:
			break;
		}
	}
}

void Game::travMap(std::shared_ptr<Player> set) {

	bool mapTime = true;

	system("CLS");
	std::cin.clear();

	displayMap(set);

	while (mapTime) {
		// Different switch options, message depending on Player Location on map
		if (gameMap[set->getPlayerY()][set->getPlayerX()] == 'V') {
			std::cout << "Enter WASD movement command, Q to Quit, or I to enter the town: ";
			char travChoice = _getch();

			if (tolower(travChoice) == 's') {
				if (gameMap[set->getPlayerY() + 1][set->getPlayerX()] != '@') {
					// Move South
					incrementDay();
					set->incPlayerY();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'a') {
				if (gameMap[set->getPlayerY()][set->getPlayerX() - 1] != '@') {
					// Move West
					incrementDay();
					set->decPlayerX();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'w') {
				if (gameMap[set->getPlayerY() - 1][set->getPlayerX()] != '@') {
					// Move North
					incrementDay();
					set->decPlayerY();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'd') {
				if (gameMap[set->getPlayerY()][set->getPlayerX() + 1] != '@') {
					// Move East
					incrementDay();
					set->incPlayerX();
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
				enterTown(set, getTown(set->getPlayerX(), set->getPlayerY()));
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
				if (gameMap[set->getPlayerY() + 1][set->getPlayerX()] != '@') {
					// Move North
					incrementDay();
					set->incPlayerY();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'a') {
				if (gameMap[set->getPlayerY()][set->getPlayerX() - 1] != '@') {
					// Move West
					incrementDay();
					set->decPlayerX();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'w') {
				if (gameMap[set->getPlayerY() - 1][set->getPlayerX()] != '@') {
					// Move South
					incrementDay();
					set->decPlayerY();
				}
				// Display Map
				system("CLS");
				displayMap(set);
			}
			else if (tolower(travChoice) == 'd') {
				if (gameMap[set->getPlayerY()][set->getPlayerX() + 1] != '@') {
					// Move East
					incrementDay();
					set->incPlayerX();
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

		// Reset inventories
	}
}

std::shared_ptr<Town> Game::getTown(int playerXArg, int playerYArg) {
	for (int i = 0; i < all_towns.size(); i++) {
		if ((all_towns.at(i)->getLocationX() == playerXArg) && (all_towns.at(i)->getLocationY() == playerYArg)) {
			return all_towns.at(i);
		}
	}
}

// Function to display the map
void Game::displayMap(std::shared_ptr<Player> set) {
	// std::vector<std::string> mapStrings;

	for (int i = 0; i < MAP_MAX_ROWS; i++) {
		std::string mapString = "";
		for (int j = 0; j < MAP_MAX_COLS; j++) {
			if (i == set->getPlayerY() && j == set->getPlayerX()) {
				mapString += 'P';
			}
			else {
				mapString += gameMap[i][j];
			}
		}
		std::cout << mapString << std::endl;
	}

	std::cout << std::endl;
	std::cout << set->getPlayerX() << " | " << set->getPlayerY() << std::endl;
	printCalendar();
}

void Game::enterTown(std::shared_ptr<Player> set, std::shared_ptr<Town> townArg) {

	char townChoice;
	set->setInTownTrue();

	if (townArg->getTownAuxScreens().size() == 3) {

		while (set->getInTown()) {
			std::cin.clear();

			townArg->printScreen();
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
				set->setInTownFalse();
				travMap(set);
			}
			else {
				system("CLS");
				townArg->printScreen();
				std::cout << "State your business: ";
				townChoice = _getch();
			}
		}
	}
	else if (townArg->getTownAuxScreens().size() == 4) {
		while (set->getInTown()) {
			std::cin.clear();

			townArg->printScreen();
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
				enterAlley(townArg, set);
			}
			else if (townChoice == '5') {
				set->setInTownFalse();
				travMap(set);
			}
			else {
				system("CLS");
				townArg->printScreen();
				std::cout << "State your business: ";
				townChoice = _getch();
			}
		}
	}
}

void Game::enterBlacksmith(std::shared_ptr<Town> townArg, std::shared_ptr<Player> set) {

	bool inSmith = true;

	char smithChoice;
	char stalling;

	while (inSmith) {

		std::cin.clear();
		townArg->printBlacksmith();
		std::cout << "State your business: ";

		smithChoice = _getch();

		switch (smithChoice) {
		case '1':
			system("CLS");
			buy(playerInventory, townArg->getBlacksmithInv(), 1);
			break;
		case '2':
			system("CLS");
			sell(playerInventory, townArg->getBlacksmithInv(), 1);
			break;
		case '3':
			system("CLS");
			std::cin.clear();
			std::cout << "\'Chat\' logic not yet implemented )\':" << std::endl;
			std::cout << "Press any alphanumerical key to return to the alley menu." << std::endl;
			stalling = _getch();
			break;
		case '4':
			system("CLS");
			inSmith = false;
			enterTown(set, townArg);
			break;
		default:
			break;
		}
	}
}

void Game::enterGrocer(std::shared_ptr<Town> townArg, std::shared_ptr<Player> set) {

	bool inGrocer = true;

	char grocerChoice;
	char stalling;

	while (inGrocer) {

		std::cin.clear();
		townArg->printGrocer();
		std::cout << "State your business: ";

		grocerChoice = _getch();

		switch (grocerChoice) {
		case '1':
			system("CLS");
			buy(playerInventory, townArg->getGrocerInv(), 2);
			break;
		case '2':
			system("CLS");
			sell(playerInventory, townArg->getGrocerInv(), 2);
			break;
		case '3':
			system("CLS");
			std::cin.clear();
			std::cout << "\'Chat\' logic not yet implemented )\':" << std::endl;
			std::cout << "Press any alphanumerical key to return to the alley menu." << std::endl;
			stalling = _getch();
			break;
		case '4':
			system("CLS");
			inGrocer = false;
			enterTown(set, townArg);
			break;
		default:
			break;
		}
	}
}

void Game::enterTavern(std::shared_ptr<Town> townArg, std::shared_ptr<Player> set) {

	bool inTavern = true;

	char tavernChoice;
	char stalling;

	while (inTavern) {

		std::cin.clear();
		townArg->printTavern();
		std::cout << "State your business: ";

		tavernChoice = _getch();

		switch (tavernChoice) {
		case '1':
			buy(playerInventory, townArg->getTavernInv(), 3);
			break;
		case '2':
			system("CLS");
			std::cin.clear();
			std::cout << "\'Chat\' logic not yet implemented )\':" << std::endl;
			std::cout << "Press any alphanumerical key to return to the alley menu." << std::endl;
			stalling = _getch();
			break;
		case '3':
			system("CLS");
			std::cin.clear();
			std::cout << "\'Rent\' logic not yet implemented )\':" << std::endl;
			std::cout << "Press any alphanumerical key to return to the alley menu." << std::endl;
			stalling = _getch();
			break;
		case '4':
			inTavern = false;
			enterTown(set, townArg);
			break;
		default:
			break;
		}
	}
}

void Game::enterAlley(std::shared_ptr<Town> townArg, std::shared_ptr<Player> set) {

	bool inAlley = true;

	char alleyChoice;
	char stalling;

	while (inAlley) {

		std::cin.clear();
		townArg->printAux4();
		std::cout << "State your business: ";

		alleyChoice = _getch();

		switch (alleyChoice) {
		case '1':
			buy(playerInventory, townArg->getAux4Inv(), 4);
			break;
		case '2':
			system("CLS");
			std::cin.clear();
			std::cout << "\'Chat\' logic not yet implemented )\':" << std::endl;
			std::cout << "Press any alphanumerical key to return to the alley menu." << std::endl;
			stalling = _getch();
			break;
		case '3':
			system("CLS");
			std::cin.clear();
			std::cout << "\'Torch\' logic not yet implemented )\':" << std::endl;
			std::cout << "Press any alphanumerical key to return to the alley menu." << std::endl;
			stalling = _getch();
			break;
		case '4':
			inAlley = false;
			enterTown(set, townArg);
			break;
		default:
			break;
		}
	}
}

void Game::buy(std::shared_ptr<Inventory> playerInvArg, std::shared_ptr<Inventory> shopInvArg, int auxArg) {
	system("CLS");
	bool buying = true;

	// Clear out cin
	std::cin.clear();

	// Clear out any remaining characters in the input stream
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (buying) {
		// Clear the screen
		system("CLS");

		std::string buyChoice;

		// Print trade UI
		playerInvArg->printInventoryBuy();
		std::cout << std::endl << std::endl;
		shopInvArg->printInventorySell();
		std::cout << std::endl << std::endl;

		std::cout << std::endl << "Enter a number to buy an item, enter 0 to quit: ";
		auto inventorySize = shopInvArg->getFoundItems().size();

		// Get user input as string, convert to int; if 0, return to shop screen
		std::getline(std::cin, buyChoice, '\n');
		int indexChoice = stoi(buyChoice) - 1;


		if (indexChoice == -1) {
			buying = false;

		}
		else if ((indexChoice < inventorySize) && (indexChoice >= 0)) {
			if (playerInvArg->getTotalPurse()
				>= (shopInvArg->getFoundItem(indexChoice)->getItemValue() * shopInvArg->getSellMult())) {
				playerInvArg->buyItem(shopInvArg->getFoundItem(indexChoice));
				shopInvArg->sellItem(indexChoice);
			}
		}

	}
}

void Game::sell(std::shared_ptr<Inventory> playerInvArg, std::shared_ptr<Inventory> shopInvArg, int auxArg) {
	// Clear the screen
	system("CLS");

	bool selling = true;

	// Clear out cin
	std::cin.clear();

	// Clear out any remaining characters in the input stream
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (selling) {
		// Clear the screen
		system("CLS");

		std::string sellChoice;

		// Print trade UI
		shopInvArg->printInventoryBuy();
		std::cout << std::endl << std::endl;
		playerInvArg->printInventorySell();
		std::cout << std::endl << std::endl;

		std::cout << std::endl << "Enter a number to sell an item, enter 0 to quit: ";
		auto inventorySize = playerInvArg->getFoundItems().size();

		// Get user input as string, convert to int; if 0, return to shop screen
		std::getline(std::cin, sellChoice, '\n');
		int indexChoice = stoi(sellChoice) - 1;

		// Initialize Item instance
		std::shared_ptr<Item> itemChoice;

		// Check whether to exit (entry is 0)
		if (indexChoice == -1) {
			selling = false;
			// Return to shop screen
		}
		// Check whether index choice is in bounds
		else if ((indexChoice < inventorySize) && (indexChoice >= 0)) {
			itemChoice = playerInvArg->getFoundItem(indexChoice);

			if ((itemChoice->getItemValue() * shopInvArg->getBuyMult()) <= shopInvArg->getMaxTransaction()) {
				switch (auxArg) {
				case 1:
					if ((itemChoice->getItemType() == "Weapon") ||
						(itemChoice->getItemType() == "Boots") ||
						(itemChoice->getItemType() == "Legs") ||
						(itemChoice->getItemType() == "Gloves") ||
						(itemChoice->getItemType() == "Chest") ||
						(itemChoice->getItemType() == "Shield") ||
						(itemChoice->getItemType() == "Helmet")) {

						shopInvArg->buyItem(itemChoice);
						playerInvArg->sellItem(itemChoice);

						system("CLS");
					}
					else {
						system("CLS");
						std::cout << std::endl << shopInvArg->getBelongsTo() << " does not buy "
							<< itemChoice->getItemType() << "." << std::endl << std::endl;
					}
					break;
				case 2:
					if ((itemChoice->getItemType() == "Food") ||
						(itemChoice->getItemType() == "Potion") ||
						(itemChoice->getItemType() == "Tool")) {

						shopInvArg->buyItem(itemChoice);
						playerInvArg->sellItem(itemChoice);

						system("CLS");
					}
					else {
						system("CLS");
						std::cout << std::endl << shopInvArg->getBelongsTo() << " does not buy "
							<< itemChoice->getItemType() << "." << std::endl << std::endl;
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

void Game::displayNeutralInventory() {
	system("CLS");
	bool testingNeutral = true;

	// Clear out cin
	std::cin.clear();

	// Clear out any remaining characters in the input stream
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Variables for the sprite display loop
	bool displaying = true;
	std::string displayKey;

	while (testingNeutral) {
		system("CLS");

		std::string testChoice;
		int indexChoice;

		// Print the inventory with Neutral multipliers
		playerInventory->printInventoryNeutral();

		// Get inventory size for handling out-of-bounds input
		auto inventorySize = playerInventory->getFoundItems().size();

		// Prompt and get/handle input
		std::cout << "Enter a number to display an item sprite, 0 to quit: ";
		std::getline(std::cin, testChoice, '\n');
		indexChoice = stoi(testChoice) - 1;

		if (indexChoice == -1) {
			system("CLS");
			testingNeutral = false;
			// Return to shop screen
		}
		if ((indexChoice < inventorySize) && (indexChoice >= 0)) {
			displaying = true;
			while (displaying) {
				// Display the item at foundItems[indexChoice]
				system("CLS");

				// Clear out cin
				std::cin.clear();
				std::shared_ptr itemChoice = playerInventory->getFoundItem(indexChoice);
				itemChoice->printItemSprite();
				std::cout << "           " << itemChoice->getItemName() << " | Type: " << itemChoice->getItemType() <<
					" | Dam: " << itemChoice->getItemDam() << " | DT: " << itemChoice->getItemDT() << " | Value: " <<
					itemChoice->getItemValue();

				// Check whether Item is equippable
				if ((itemChoice->getItemType() == "Weapon") ||
					(itemChoice->getItemType() == "Boots") ||
					(itemChoice->getItemType() == "Legs") ||
					(itemChoice->getItemType() == "Gloves") ||
					(itemChoice->getItemType() == "Chest") ||
					(itemChoice->getItemType() == "Shield") ||
					(itemChoice->getItemType() == "Helmet")) {
					bool itemChoiceEquipped = false;

					// Check whether equippable Item is equipped
					for (int i = 0; i < playerInventory->getEquippedItems().size(); i++) {
						if (itemChoice->getItemName() == playerInventory->getEquippedItems().at(i)->getItemName()) {
							itemChoiceEquipped = true;
						}
					}

					// If equipped, prompt user to unequip
					if (itemChoiceEquipped) {
						std::cout << " | Equipped" << std::endl << std::endl << "Press 1 to unequip, 0 to exit. ";
						char displayKey = _getch();

						switch (displayKey) {
						case '0':
							system("CLS");
							displaying = false;
							break;
						case '1':
							playerInventory->unequipItem(itemChoice);
							break;
						}
					}

					// Else prompt user to equip Item
					else {
						std::cout << std::endl << std::endl << "Press 1 to equip, 0 to exit. ";
						char displayKey = _getch();

						switch (displayKey) {
						case '0':
							system("CLS");
							displaying = false;
						case '1':
							playerInventory->equipItem(itemChoice);
							break;
						}
					}
				}
				// Item is not equippable
				else {
					std::cout << std::endl << "Press any alphanumerical key to exit. ";
					char displayKey = _getch();
				}
			}
		}
	}
}

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
		// reset_vendor_inventories every two weeks
		reset_town_inventories();
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

void Game::initialize_all_inventories() {

	srand((int)time(0));

	for (int i = 0; i < all_items.size(); i++) {
		playerInventory->incrementCarriedItem(all_items.at(i));
	}

	for (int i = 0; i < 6; i++) {
		int randS = (std::rand() % all_blacksmith_items.size());
		blackSmithInventory->incrementCarriedItem(all_blacksmith_items.at(randS));
	}

	// Grocery items
	for (int i = 0; i < 50; i++) {
		int randG = (std::rand() % all_grocer_items.size());
		grocerInventory->incrementCarriedItem(all_grocer_items.at(randG));
	}


	// Beer and Coffee for the Tavern
	for (int i = 0; i < 40; i++) {
		tavernInventory->incrementCarriedItem(beer);
		tavernInventory->incrementCarriedItem(coffee);
	}

	// Pendel and Scharfy
	for (int i = 0; i < 50; i++) {
		pendelInventory->incrementCarriedItem(barrel_of_oats);
		scharfyInventory->incrementCarriedItem(barrel_of_beans);
	}

	for (int i = 0; i < all_towns.size(); i++) {
		all_towns.at(i)->setBlacksmithInv(blackSmithInventory);
		all_towns.at(i)->setGrocerInv(grocerInventory);
		all_towns.at(i)->setTavernInv(tavernInventory);
		if (all_towns.at(i)->getLocationName() == "Daphnon") {
			all_towns.at(i)->setAux4Inv(scharfyInventory);
		}
		if (all_towns.at(i)->getLocationName() == "Prince\'s Reproach") {
			all_towns.at(i)->setAux4Inv(pendelInventory);
		}
	}
}

void Game::reset_town_inventories() {
	srand((int)time(0));

	for (auto item : blackSmithInventory->getCarriedItems()) {
		blackSmithInventory->decrementCarriedItem(item);
	}

	for (auto item : grocerInventory->getCarriedItems()) {
		grocerInventory->decrementCarriedItem(item);
	}

	for (auto item : tavernInventory->getCarriedItems()) {
		tavernInventory->decrementCarriedItem(item);
	}

	for (auto item : pendelInventory->getCarriedItems()) {
		pendelInventory->decrementCarriedItem(item);
	}

	for (auto item : scharfyInventory->getCarriedItems()) {
		scharfyInventory->decrementCarriedItem(item);
	}

	blackSmithInventory->setCurrency(7, 5, 10, 10);
	grocerInventory->setCurrency(7, 5, 10, 10);
	tavernInventory->setCurrency(7, 5, 10, 10);
	pendelInventory->setCurrency(7, 5, 10, 10);
	scharfyInventory->setCurrency(7, 5, 10, 10);

	blackSmithInventory->setMaxTransaction(5000);
	grocerInventory->setMaxTransaction(300);
	tavernInventory->setMaxTransaction(500);
	pendelInventory->setMaxTransaction(1000);
	scharfyInventory->setMaxTransaction(1000);

	for (int i = 0; i < 6; i++) {
		int randS = (std::rand() % all_blacksmith_items.size());
		blackSmithInventory->incrementCarriedItem(all_blacksmith_items.at(randS));
	}

	for (int i = 0; i < 50; i++) {
		int randG = (std::rand() % all_grocer_items.size());
		grocerInventory->incrementCarriedItem(all_grocer_items.at(randG));
	}

	for (int i = 0; i < 40; i++) {
		tavernInventory->incrementCarriedItem(beer);
		tavernInventory->incrementCarriedItem(coffee);
	}

	// Pendel and Scharfy
	for (int i = 0; i < 50; i++) {
		pendelInventory->incrementCarriedItem(barrel_of_oats);
		scharfyInventory->incrementCarriedItem(barrel_of_beans);
	}

	for (int i = 0; i < all_towns.size(); i++) {
		all_towns.at(i)->setBlacksmithInv(blackSmithInventory);
		all_towns.at(i)->setGrocerInv(grocerInventory);
		all_towns.at(i)->setTavernInv(tavernInventory);
		if (all_towns.at(i)->getLocationName() == "Daphnon") {
			all_towns.at(i)->setAux4Inv(scharfyInventory);
		}
		if (all_towns.at(i)->getLocationName() == "Prince\'s Reproach") {
			all_towns.at(i)->setAux4Inv(pendelInventory);
		}
	}
}


void Game::clear_all_inventories() {
	srand((int)time(0));

	for (auto item : blackSmithInventory->getCarriedItems()) {
		blackSmithInventory->decrementCarriedItem(item);
	}

	for (auto item : grocerInventory->getCarriedItems()) {
		grocerInventory->decrementCarriedItem(item);
	}

	for (auto item : tavernInventory->getCarriedItems()) {
		tavernInventory->decrementCarriedItem(item);
	}

	for (auto item : pendelInventory->getCarriedItems()) {
		pendelInventory->decrementCarriedItem(item);
	}

	for (auto item : scharfyInventory->getCarriedItems()) {
		scharfyInventory->decrementCarriedItem(item);
	}

	for (auto item : playerInventory->getCarriedItems()) {
		playerInventory->decrementCarriedItem(item);
	}

	for (int i = 0; i < all_towns.size(); i++) {
		all_towns.at(i)->setBlacksmithInv(blackSmithInventory);
		all_towns.at(i)->setGrocerInv(grocerInventory);
		all_towns.at(i)->setTavernInv(tavernInventory);
		if (all_towns.at(i)->getLocationName() == "Daphnon") {
			all_towns.at(i)->setAux4Inv(scharfyInventory);
		}
		if (all_towns.at(i)->getLocationName() == "Prince\'s Reproach") {
			all_towns.at(i)->setAux4Inv(pendelInventory);
		}
	}
}