#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class Item {
public:
	Item();
	~Item();

	void printItemSprite();

	// Accessors
	std::string getItemName();
	std::string getItemType();

	int getItemDam();
	int getItemDT();

	int getItemValue();

	Item getItem(std::string itemNameArg);

	// Mutators
	void setItemName(std::string);
	void setItemSprite(std::string);

private:
	
	// For weapons
	int itemDam;
	// For shields and armor
	int itemDT;
	int itemValue;

	std::string itemName;

	// Item type determines equippable (chest/head/legs etc...) or consumable
	std::string itemType; 
	// TYPES: H = Head, C = Chest, L = Legs, G = Gloves, F = Feet, W = Weapon, S = Shield, P = Potion

	std::vector<std::string> itemSprite {};
};