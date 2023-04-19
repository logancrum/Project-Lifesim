#pragma once

#include <fstream>
#include <string>
#include <vector>
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
	void initialize_all_inventories();
	void reset_town_inventories();
	void clear_all_inventories();

	// Main menu functions
	void printMain();
	void loadGameMM();
	void newGame();
	void quitGameMM();

	// Game Menu Functions
	void pauseMenu(std::shared_ptr<Player>);
	void quitGame(std::shared_ptr<Player>);
	void loadGame(std::shared_ptr<Player>);
	void saveGame(std::shared_ptr<Player>);

	// Game loop
	void runGame(std::shared_ptr<Player>);

	// Map loop
	void travMap(std::shared_ptr<Player>);

	// Location loop
	std::shared_ptr<Town>  getTown(int playerXArg, int playerYArg);
	void enterTown(std::shared_ptr<Player>, std::shared_ptr<Town>);
	void enterBlacksmith(std::shared_ptr<Town> town, std::shared_ptr<Player>);
	void enterGrocer(std::shared_ptr<Town> town, std::shared_ptr<Player>);
	void enterTavern(std::shared_ptr<Town> town, std::shared_ptr<Player>);
	void enterAlley(std::shared_ptr<Town> town, std::shared_ptr<Player>);

	// Mercantile
	void buy(std::shared_ptr<Inventory> playerInvArg, std::shared_ptr<Inventory> shopInvArg, int auxArg);
	void sell(std::shared_ptr<Inventory> playerInvArg, std::shared_ptr<Inventory> shopInvArg, int auxArg);
	void displayNeutralInventory();

	// Calendar functions
	void incrementDay();
	void printCalendar();

	// cin functions
	int getCleanInt();
	std::string getCleanString();

	// Screen Printers
	void displayMap(std::shared_ptr<Player>);

	// Accessors
	std::string getGameID();

	// Mutators
	void setGameID(std::string gameIDArg);

	std::vector<std::shared_ptr<Town>> all_towns;
	std::vector<std::shared_ptr<Location>> all_locations;

	// All Items and all item types
	std::vector<std::shared_ptr<Item>> all_items{};
	std::vector<std::shared_ptr<Item>> all_blacksmith_items{};
	std::vector<std::shared_ptr<Item>> all_grocer_items{};
	std::vector<std::shared_ptr<Item>> all_tavern_items{};

public:

	/*
	* 
	*		INVENTORIES
	* 
	*/

	// PLAYER INVENTORY
	std::shared_ptr<Inventory> playerInventory = std::make_shared<Inventory>(7, 5, 7, 0, -1, 2, 1, "Player", true);

	// SHOP INVENTORIES
	std::shared_ptr<Inventory> blackSmithInventory = std::make_shared<Inventory>(7, 5, 10, 10, 5000, 1, 2, "Blacksmith", false);
	std::shared_ptr<Inventory> grocerInventory = std::make_shared<Inventory>(7, 5, 10, 10, 1000, 1, 2, "Grocer", false);
	std::shared_ptr<Inventory> tavernInventory = std::make_shared<Inventory>(7, 5, 10, 10, 1000, 1, 2, "Tavern", false);

	// NPC INVENTORIES
	std::shared_ptr<Inventory> pendelInventory = std::make_shared<Inventory>(7, 5, 1, 10, 1000, 1, 2, "Pendel", false);
	std::shared_ptr<Inventory> scharfyInventory = std::make_shared<Inventory>(7, 5, 1, 10, 1000, 1, 2, "Scharfy", false);

	/*
	*
	*		ARMOR: HELMETS
	*
	*/

	std::shared_ptr<Item> tusk_helm = std::make_shared<Item>(
		"Tusk Helm", "Helmet", 0, 2, 75,
		"\\sprites\\armor\\helmets\\tusk_helm.txt"
	);

	std::shared_ptr<Item> leather_soldiers_helmet = std::make_shared<Item>(
		"Leather Soldier\'s Helmet", "Helmet", 0, 3, 100,
		"\\sprites\\armor\\helmets\\leather_soldiers_helmet.txt"
	);

	std::shared_ptr<Item> plain_bascinet = std::make_shared<Item>(
		"Plain Bascinet", "Helmet", 0, 4, 200,
		"\\sprites\\armor\\helmets\\plain_bascinet.txt"
	);

	std::shared_ptr<Item> mail_coif = std::make_shared<Item>(
		"Mail Coif", "Helmet", 0, 5, 500,
		"\\sprites\\armor\\helmets\\mail_coif.txt"
	);

	std::shared_ptr<Item> iron_soldiers_cap = std::make_shared<Item>(
		"Iron Soldier\'s Cap", "Helmet", 0, 6, 800,
		"\\sprites\\armor\\helmets\\iron_soldiers_cap.txt"
	);

	std::shared_ptr<Item> steel_helm = std::make_shared<Item>(
		"Steel Helm", "Helmet", 0, 7, 1000,
		"\\sprites\\armor\\helmets\\steel_helm.txt"
	);

	std::shared_ptr<Item> spiked_great_helm = std::make_shared<Item>(
		"Spiked Great Helm", "Helmet", 0, 8, 1500,
		"\\sprites\\armor\\helmets\\spiked_great_helm.txt"
	);

	std::shared_ptr<Item> frog_mouth_great_helm = std::make_shared<Item>(
		"Frog-Mouth Great Helm", "Helmet", 0, 8, 2000,
		"\\sprites\\armor\\helmets\\frog_mouth_great_helm.txt"
	);

	std::shared_ptr<Item> ancient_helm = std::make_shared<Item>(
		"Ancient Helm", "Helmet", 0, 10, 3000,
		"\\sprites\\armor\\helmets\\ancient_helm.txt"
	);

	/*
	*
	*		ARMOR: CHEST
	*
	*/

	std::shared_ptr<Item> wool_gambeson = std::make_shared<Item>(
		"Wool Gambeson", "Chest", 0, 6, 200,
		"\\sprites\\armor\\chest\\wool_gambeson.txt"
	);

	std::shared_ptr<Item> leather_gambeson = std::make_shared<Item>(
		"Leather Gambeson", "Chest", 0, 8, 250,
		"\\sprites\\armor\\chest\\leather_gambeson.txt"
	);

	std::shared_ptr<Item> heavy_padded_wool_gambeson = std::make_shared<Item>(
		"Heavy Padded Wool Gambeson", "Chest", 0, 10, 300,
		"\\sprites\\armor\\chest\\heavy_padded_wool_gambeson.txt"
	);

	std::shared_ptr<Item> leather_brigandine = std::make_shared<Item>(
		"Leather Brigandine", "Chest", 0, 11, 325,
		"\\sprites\\armor\\chest\\leather_brigandine.txt"
	);

	std::shared_ptr<Item> heavy_leather_gambeson = std::make_shared<Item>(
		"Heavy Leather Gambeson", "Chest", 0, 12, 400,
		"\\sprites\\armor\\chest\\heavy_leather_gambeson.txt"
	);

	std::shared_ptr<Item> lamellar_cuirass = std::make_shared<Item>(
		"Lamellar Cuirass", "Chest", 0, 14, 1000,
		"\\sprites\\armor\\chest\\lamellar_cuirass.txt"
	);

	std::shared_ptr<Item> light_iron_plate_armor = std::make_shared<Item>(
		"Light Iron Plate Armor", "Chest", 0, 15, 1200,
		"\\sprites\\armor\\chest\\light_iron_plate_armor.txt"
	);

	std::shared_ptr<Item> light_steel_plate_armor = std::make_shared<Item>(
		"Light Steel Plate Armor", "Chest", 0, 18, 2000,
		"\\sprites\\armor\\chest\\light_steel_plate_armor.txt"
	);

	std::shared_ptr<Item> steel_cuirass = std::make_shared<Item>(
		"Steel Cuirass", "Chest", 0, 20, 3000,
		"\\sprites\\armor\\chest\\steel_cuirass.txt"
	);

	/*
	*
	*		ARMOR: GLOVES
	*
	*/

	std::shared_ptr<Item> leather_gloves = std::make_shared<Item>(
		"Leather Gloves", "Gloves", 0, 1, 42,
		"\\sprites\\armor\\gloves\\leather_gloves.txt"
	);

	std::shared_ptr<Item> iron_gauntlets = std::make_shared<Item>(
		"Iron Gauntlets", "Gloves", 0, 3, 200,
		"\\sprites\\armor\\gloves\\iron_gauntlets.txt"
	);

	std::shared_ptr<Item> steel_gauntlets = std::make_shared<Item>(
		"Steel Gauntlets", "Gloves", 0, 3, 400,
		"\\sprites\\armor\\gloves\\steel_gauntlets.txt"
	);

	/*
	*
	*		ARMOR: LEGS
	*
	*/

	std::shared_ptr<Item> leather_tassets = std::make_shared<Item>(
		"Leather Tassets", "Legs", 0, 2, 44,
		"\\sprites\\armor\\legs\\leather_tassets.txt"
	);

	std::shared_ptr<Item> padded_cloth_chausses = std::make_shared<Item>(
		"Padded Cloth Chausses", "Legs", 0, 3, 60,
		"\\sprites\\armor\\legs\\padded_cloth_chausses.txt"
	);

	std::shared_ptr<Item> heavy_leather_chausses = std::make_shared<Item>(
		"Heavy Leather Chausses", "Legs", 0, 6, 120,
		"\\sprites\\armor\\legs\\heavy_leather_chausses.txt"
	);

	std::shared_ptr<Item> mail_chausses = std::make_shared<Item>(
		"Mail Chausses", "Legs", 0, 8, 300,
		"\\sprites\\armor\\legs\\mail_chausses.txt"
	);

	std::shared_ptr<Item> steel_tassets = std::make_shared<Item>(
		"Steel Tassets", "Legs", 0, 12, 1000,
		"\\sprites\\armor\\legs\\steel_tassets.txt"
	);

	/*
	*
	*		ARMOR: BOOTS
	*
	*/

	std::shared_ptr<Item> leather_boots = std::make_shared<Item>(
		"Leather Boots", "Boots", 0, 3, 60,
		"\\sprites\\armor\\boots\\leather_boots.txt"
	);

	std::shared_ptr<Item> fancy_riding_boots = std::make_shared<Item>(
		"Fancy Riding Boots", "Boots", 0, 4, 300,
		"\\sprites\\armor\\boots\\fancy_riding_boots.txt"
	);

	std::shared_ptr<Item> iron_boots = std::make_shared<Item>(
		"Iron Boots", "Boots", 0, 6, 400,
		"\\sprites\\armor\\boots\\iron_boots.txt"
	);

	std::shared_ptr<Item> steel_boots = std::make_shared<Item>(
		"Steel Boots", "Boots", 0, 8, 600,
		"\\sprites\\armor\\boots\\steel_boots.txt"
	);

	/*
	*
	*		WEAPONS: SWORDS
	*
	*/

	std::shared_ptr<Item> iron_shortsword = std::make_shared<Item>(
		"Iron Shortsword", "Weapon", 9, 2, 100,
		"\\sprites\\weapons\\swords\\iron_shortsword.txt"
	);

	std::shared_ptr<Item> iron_scimitar = std::make_shared<Item>(
		"Iron Scimitar", "Weapon", 16, 2, 1000,
		"\\sprites\\weapons\\swords\\iron_scimitar.txt"
	);

	std::shared_ptr<Item> steel_scimitar = std::make_shared<Item>(
		"Steel Scimitar", "Weapon", 26, 3, 5700,
		"\\sprites\\weapons\\swords\\steel_scimitar.txt"
	);

	std::shared_ptr<Item> steel_longsword = std::make_shared<Item>(
		"Steel Longsword", "Weapon", 25, 5, 6000,
		"\\sprites\\weapons\\swords\\steel_longsword.txt"
	);

	std::shared_ptr<Item> fine_steel_longsword = std::make_shared<Item>(
		"Fine Steel Longsword", "Weapon", 32, 5, 9000,
		"\\sprites\\weapons\\swords\\fine_steel_longsword.txt"
	);


	std::shared_ptr<Item> reinforced_steel_claymore = std::make_shared<Item>(
		"Reinforced Steel Claymore", "Weapon", 38, 10, 9900,
		"\\sprites\\weapons\\swords\\reinforced_steel_claymore.txt"
	);

	/*
	*
	*		WEAPONS: MACES
	*
	*/

	std::shared_ptr<Item> short_iron_cudgel = std::make_shared<Item>(
		"Short Iron Cudgel", "Weapon", 8, 0, 100,
		"\\sprites\\weapons\\maces\\short_iron_cudgel.txt"
	);

	std::shared_ptr<Item> iron_mace = std::make_shared<Item>(
		"Iron Mace", "Weapon", 17, 0, 990,
		"\\sprites\\weapons\\maces\\iron_mace.txt"
	);

	std::shared_ptr<Item> steel_mace = std::make_shared<Item>(
		"Steel Mace", "Weapon", 26, 0, 5500,
		"\\sprites\\weapons\\maces\\steel_mace.txt"
	);

	std::shared_ptr<Item> heavy_steel_morning_star = std::make_shared<Item>(
		"Heavy Steel Morning Star", "Weapon", 40, 0, 9500,
		"\\sprites\\weapons\\maces\\heavy_steel_morning_star.txt"
	);

	/*
	*
	*		WEAPONS: SPEARS
	*
	*/

	std::shared_ptr<Item> simple_spear = std::make_shared<Item>(
		"Simple Spear", "Weapon", 7, 0, 60,
		"\\sprites\\weapons\\spears\\simple_spear.txt"
	);

	std::shared_ptr<Item> iron_spear = std::make_shared<Item>(
		"Iron Spear", "Weapon", 18, 0, 990,
		"\\sprites\\weapons\\spears\\iron_spear.txt"
	);

	std::shared_ptr<Item> steel_spear = std::make_shared<Item>(
		"Steel Spear", "Weapon", 27, 0, 6000,
		"\\sprites\\weapons\\spears\\steel_spear.txt"
	);

	/*
	*
	*		WEAPONS: DAGGERS
	*
	*/

	std::shared_ptr<Item> iron_dirk = std::make_shared<Item>(
		"Iron Dirk", "Weapon", 5, 0, 50,
		"\\sprites\\weapons\\daggers\\iron_dirk.txt"
	);

	std::shared_ptr<Item> iron_dagger = std::make_shared<Item>(
		"Iron Dagger", "Weapon", 6, 0, 60,
		"\\sprites\\weapons\\daggers\\iron_dagger.txt"
	);


	std::shared_ptr<Item> steel_dirk = std::make_shared<Item>(
		"Steel Dirk", "Weapon", 5, 0, 50,
		"\\sprites\\weapons\\daggers\\steel_dirk.txt"
	);

	std::shared_ptr<Item> steel_dagger = std::make_shared<Item>(
		"Steel Dagger", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\daggers\\steel_dagger.txt"
	);

	std::shared_ptr<Item> long_steel_dagger = std::make_shared<Item>(
		"Long Steel Dagger", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\daggers\\long_steel_dagger.txt"
	);

	std::shared_ptr<Item> lords_steel_dagger = std::make_shared<Item>(
		"Lord's Steel Dagger", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\daggers\\lords_steel_dagger.txt"
	);

	/*
	*
	*		WEAPONS: HAMMERS
	*
	*/std::shared_ptr<Item> iron_hammer = std::make_shared<Item>(
		"Iron Hammer", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\hammers\\iron_hammer.txt"
	);

	std::shared_ptr<Item> crude_iron_maul = std::make_shared<Item>(
		"Crude Iron Maul", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\hammers\\crude_iron_maul.txt"
	);

	std::shared_ptr<Item> fine_steel_hammer = std::make_shared<Item>(
		"Fine Steel Hammer", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\hammers\\fine_steel_hammer.txt"
	);

	std::shared_ptr<Item> reinforced_steel_warhammer = std::make_shared<Item>(
		"Reinforced Steel Warhammer", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\hammers\\reinforced_steel_warhammer.txt"
	);

	/*
	*
	*		WEAPONS: AXES
	*
	*/

	std::shared_ptr<Item> iron_hatchet = std::make_shared<Item>(
		"Iron Hatchet", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\axes\\iron_hatchet.txt"
	);

	std::shared_ptr<Item> steel_hatchet = std::make_shared<Item>(
		"Steel Hatchet", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\axes\\steel_hatchet.txt"
	);

	std::shared_ptr<Item> iron_battleaxe = std::make_shared<Item>(
		"Iron Battleaxe", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\axes\\iron_battleaxe.txt"
	);

	std::shared_ptr<Item> steel_war_axe = std::make_shared<Item>(
		"Steel War Axe", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\axes\\steel_war_axe.txt"
	);

	std::shared_ptr<Item> steel_battleaxe = std::make_shared<Item>(
		"Steel Battlexe", "Weapon", 5, 0, 400,
		"\\sprites\\weapons\\axes\\steel_battleaxe.txt"
	);

	/*
	*
	*		SHIELDS
	*
	*/

	std::shared_ptr<Item> painted_wooden_buckler = std::make_shared<Item>(
		"Painted Wooden Buckler", "Shield", 0, 5, 400,
		"\\sprites\\shields\\painted_wooden_buckler.txt"
	);

	std::shared_ptr<Item> iron_round_shield = std::make_shared<Item>(
		"Iron Round Shield", "Shield", 0, 5, 400,
		"\\sprites\\shields\\iron_round_shield.txt"
	);

	std::shared_ptr<Item> steel_round_shield = std::make_shared<Item>(
		"Steel Round Shield", "Shield", 0, 5, 400,
		"\\sprites\\shields\\steel_round_shield.txt"
	);

	std::shared_ptr<Item> steel_kite_shield = std::make_shared<Item>(
		"Steel Kite Shield", "Shield", 0, 5, 400,
		"\\sprites\\shields\\steel_kite_shield.txt"
	);

	std::shared_ptr<Item> fine_steel_heater_shield = std::make_shared<Item>(
		"Fine Steel Heater Shield", "Shield", 0, 5, 400,
		"\\sprites\\shields\\fine_steel_heater_shield.txt"
	);
	/*
	*
	*		CONSUMABLES: FOOD
	*
	*/

	std::shared_ptr<Item> apple = std::make_shared<Item>(
		"Apple", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\apple.txt"
	);

	std::shared_ptr<Item> cheese_wedge = std::make_shared<Item>(
		"Cheese Wedge", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\cheese_wedge.txt"
	);

	std::shared_ptr<Item> fancy_cheese = std::make_shared<Item>(
		"Fancy Cheese", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\fancy_cheese.txt"
	);

	std::shared_ptr<Item> fig = std::make_shared<Item>(
		"Fig", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\fig.txt"
	);

	std::shared_ptr<Item> melon = std::make_shared<Item>(
		"Melon", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\melon.txt"
	);

	std::shared_ptr<Item> potatoes = std::make_shared<Item>(
		"Potatoes", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\potatoes.txt"
	);

	std::shared_ptr<Item> prime_rib = std::make_shared<Item>(
		"Prime Rib", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\prime_rib.txt"
	);

	std::shared_ptr<Item> tbone_steak = std::make_shared<Item>(
		"T-Bone Steak", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\tbone_steak.txt"
	);

	std::shared_ptr<Item> turkey_leg = std::make_shared<Item>(
		"Turkey Leg", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\turkey_leg.txt"
	);

	std::shared_ptr<Item> wheel_of_cheese = std::make_shared<Item>(
		"Wheel of Cheese", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\wheel_of_cheese.txt"
	);

	std::shared_ptr<Item> barrel_of_oats = std::make_shared<Item>(
		"Barrel of Oats", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\barrel_of_oats.txt"
	);

	std::shared_ptr<Item> barrel_of_beans = std::make_shared<Item>(
		"Barrel of Beans", "Food", 0, 0, 5,
		"\\sprites\\consumables\\food\\barrel_of_beans.txt"
	);

	/*
	*
	*		TOOLS
	*
	*/

	std::shared_ptr<Item> rope = std::make_shared<Item>(
		"Rope", "Tool", 0, 0, 400, "\\sprites\\tools\\rope.txt"
	);

	std::shared_ptr<Item> spade = std::make_shared<Item>(
		"Spade", "Tool", 0, 0, 400, "\\sprites\\tools\\spade.txt"
	);

	std::shared_ptr<Item> torch = std::make_shared<Item>(
		"Torch", "Tool", 0, 0, 400, "\\sprites\\tools\\torch.txt"
	);

	/*
	*
	*		CONSUMABLES: POTIONS
	*
	*/

	std::shared_ptr<Item> health_potion = std::make_shared<Item>(
		"Health Potion", "Potion", 0, 0, 80,
		"\\sprites\\consumables\\potions\\health_potion.txt"
	);

	std::shared_ptr<Item> fancy_health_potion = std::make_shared<Item>(
		"Fancy Health Potion", "Potion", 0, 0, 100,
		"\\sprites\\consumables\\potions\\fancy_health_potion.txt"
	);

	std::shared_ptr<Item> coffee = std::make_shared<Item>(
		"Coffee", "Potion", 0, 0, 10,
		"\\sprites\\consumables\\potions\\coffee.txt"
	);

	std::shared_ptr<Item> beer = std::make_shared<Item>(
		"Beer", "Potion", 0, 0, 10,
		"\\sprites\\consumables\\potions\\beer.txt"
	);

	/*

			Towns

	*/

	// Thowerd - Named for Todd Howard and the influence of his games on my life
	std::shared_ptr<Town> thowerd = std::make_shared<Town>(
		"Thowerd", 68, 44,
		"\\locations\\towns\\Thowerd_Platz.txt",
		"\\locations\\towns\\Thowerd_Smith.txt",
		"\\locations\\towns\\Thowerd_Grocer.txt",
		"\\locations\\towns\\Thowerd_Tavern.txt"
	);
	// Cainton - Named for Tim Cain, lead designer of Fallout (Post-Nuclear CRPG, 1997); Fallout and Fqllout 2 are two of my favorite things ever created
	std::shared_ptr<Town> cainton = std::make_shared<Town>(
		"Cainton", 92, 27,
		"\\locations\\towns\\Cainton_Platz.txt",
		"\\locations\\towns\\Cainton_Smith.txt",
		"\\locations\\towns\\Cainton_Grocer.txt",
		"\\locations\\towns\\Cainton_Tavern.txt"
	);
	// Prince's Reproach - Named after my cat, Prince. Note the potential dual meanings: is the Prince receiving repraoch, or is he expressing reproach for something/someone? Prince is a gemini, as my partner likes to remind him.
	std::shared_ptr<Town> princes_reproach = std::make_shared<Town>(
		"Prince\'s Reproach", 106, 43, 
		"\\locations\\towns\\Princes_Reproach_Platz.txt",
		"\\locations\\towns\\Princes_Reproach_Smith.txt",
		"\\locations\\towns\\Princes_Reproach_Grocer.txt",
		"\\locations\\towns\\Princes_Reproach_Tavern.txt",
		"\\locations\\towns\\Princes_Reproach_Alley.txt"
	);
	// Daphnon - Named after my cat, Daphnis. Daphnon is a transliteration of the ancient greek word meaning "Of the laurels" (N.B., ancient greek city names are typically in the genitive plural form).
	std::shared_ptr<Town> daphnon = std::make_shared<Town>(
		"Daphnon", 112, 56,
		"\\locations\\towns\\Daphnon_Platz.txt",
		"\\locations\\towns\\Daphnon_Smith.txt",
		"\\locations\\towns\\Daphnon_Grocer.txt",
		"\\locations\\towns\\Daphnon_Tavern.txt",
		"\\locations\\towns\\Daphnon_Alley.txt"
	);


};