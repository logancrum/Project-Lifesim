#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

class Item
{
public:
	Item();
	~Item();

	void printItemSprite();

	// Accessors
	std::string getItemName();

	int getItemDam();
	int getItemDT();

	int getItemValue();

	// Mutators
	void setItemName(std::string);
	void setItemSprite(std::vector<std::string>);

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

	std::vector<std::string> itemSprite;
};