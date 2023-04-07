#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include <cctype>  // provides the tolower() function for char
#include <conio.h> // handles keyboard input via getch()
#include <cstdlib> // for _dupenv_s

#include <town.h>
#include <player.h>

class Game {
public:
	Game();
	~Game();


private:
	std::string gameID;

	// Calendar elements
	int day;
	int year;
	std::string season;
	int seasonCount;

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
	Town getTown(int playerXArg, int playerYArg);
	void enterTown(Player, Town);
	void enterBlacksmith(Town, Player);
	void enterGrocer(Town, Player);
	void enterTavern(Town, Player);
	void enterAlley(Town, Player);

	// Calendar functions
	void incrementDay();
	void printCalendar();

	// cin functions
	int getCleanInt();
	std::string getCleanString();

	// Screen Printers
	void displayMap(Player);

	// Accessors
	std::string getGameID();

	// Mutators
	void setGameID(std::string set);

	std::vector<Town> all_towns;
	std::vector<Location> all_locations;

	// All Items and all item types
	std::vector<Item> all_items{};
	std::vector<Item> all_blacksmith_items{};
	std::vector<Item> all_grocer_items{};
	std::vector<Item> all_tavern_items{};

private:
	// Blacksmith Items

	//		Armor
	//			Helmets
	Item ancient_helm;
	Item iron_soldiers_cap;
	Item leather_soldiers_helmet;
	Item spiked_great_helm;
	Item plain_bascinet;
	Item tusk_helm;
	Item steel_helm;
	Item frog_mouth_great_helm;
	Item mail_coif;
	//			Chest
	Item heavy_leather_gambeson;
	Item heavy_padded_wool_gambeson;
	Item leather_gambeson;
	Item wool_gambeson;
	Item lamellar_cuirass;
	Item leather_brigandine;
	Item light_iron_plate_armor;
	Item light_steel_plate_armor;
	Item steel_cuirass;
	//			Legs
	Item heavy_leather_chausses;
	Item leather_tassets;
	Item mail_chausses;
	Item padded_cloth_chausses;
	Item steel_tassets;
	//			Gloves
	Item iron_gauntlets;
	Item steel_gauntlets;
	Item leather_gloves;
	//			Boots
	Item fancy_riding_boots;
	Item leather_boots;
	Item iron_boots;
	Item steel_boots;

	//		Weapons
	//			Swords
	Item fine_steel_longsword;
	Item iron_scimitar;
	Item iron_shortsword;
	Item steel_claymore;
	Item steel_longsword;
	Item steel_scimitar;
	//			Maces
	Item steel_mace;
	Item short_iron_cudgel;
	Item iron_mace;
	Item heavy_steel_morning_star;
	//			Spears
	Item iron_spear;
	Item simple_spear;
	Item steel_spear;
	//			Daggers
	Item iron_dirk;
	Item iron_dagger;
	Item steel_dirk;
	Item long_steel_dagger;
	Item steel_dagger;
	Item lords_steel_dagger;
	//			Axes
	Item iron_hatchet;
	Item steel_hatchet;
	Item steel_war_axe;
	Item iron_battleaxe;
	Item steel_battleaxe;
	//			Hammers
	Item iron_hammer;
	Item fine_steel_hammer;
	Item crude_iron_maul;
	Item steel_warhammer;

	//		Shields
	Item painted_wooden_buckler;
	Item iron_round_shield;
	Item steel_round_shield;
	Item steel_kite_shield;
	Item fine_steel_heater_shield;

	// Tools
	Item rope;
	Item spade;
	Item torch;

	// Consumable Items
	//		Food
	Item apple;
	Item cheese_wedge;
	Item fancy_cheese;
	Item fig;
	Item melon;
	Item potatoes;
	Item prime_rib;
	Item tbone_steak;
	Item turkey_leg;
	Item wheel_of_cheese;
	//		Potions
	Item fancy_health_potion;
	Item health_potion;

	// Towns

	// Prince's Reproach - Named after my cat, Prince. Note the potential dual meanings: is the Prince receiving repraoch, or is he expressing reproach for something/someone? Prince is a gemini, as my partner likes to remind him.
	Town princes_reproach;
	// Daphnon - Named after my cat, Daphnis. Daphnon is a transliteration of the ancient greek word meaning "Of the laurels" (N.B., ancient greek city names are typically in the genitive plural form).
	Town daphnon; 

	// Thowerd - Named for Todd Howard and the influence of his games on my life. I had to do it.
	Town thowerd;
	// Cainton - Named for Tim Cain, lead designer of Fallout (Post-Nuclear CRPG, 1997). Fallout and Fallout 2 are two of my favorite things ever created.
	Town cainton;
};