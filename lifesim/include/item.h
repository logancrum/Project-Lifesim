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

	bool operator==(const Item& other) const {
		return this->itemName == other.itemName;
	}

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
	void setItemType(std::string);
	void setItemDam(int);
	void setItemDT(int);
	void setItemValue(int);

	void setItemSprite(std::string);

private:
	std::string itemName;

	// Item type determines equippable (chest/head/legs etc...) or consumable
	std::string itemType;
	// TYPES: H = Head, C = Chest, L = Legs, G = Gloves, F = Feet, W = Weapon, S = Shield, P = Potion
	
	// For weapons
	int itemDam;
	// For shields and armor
	int itemDT;
	int itemValue;

	std::vector<std::string> itemSprite {};
};