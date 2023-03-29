#include <inventory.h>

Inventory::Inventory() {
	copperBits = 0;
	silverBobs = 0;
	goldCoins = 0;
	platinumChips = 0;
	maxTransaction = 0;
	buyMultiplier =	1;
	sellMultiplier = 1;
}

void Inventory::equipItem(Item itemArg) {
	// Check if there is an item already equipped with itemType matching that of itemArg
	int indexEquipped = getIndexOfEquippedItemOfType(itemArg.getItemType());
	if (indexEquipped == -1) {
		// If no such item is found, simply equip the Item itemArg
		equippedItems.push_back(itemArg);
	}
	else {
		unequipItem(indexEquipped);
		equippedItems.push_back(itemArg);
	}
}

void Inventory::unequipItem(Item itemArg) {
	int indexEquipped = getIndexOfEquippedItemOfType(itemArg.getItemType());
	if (indexEquipped != -1) {
		// getItemName
		std::string itemNameArg = itemArg.getItemName();
		// Move item to the end of the vector
		auto newEnd = std::remove_if(
			equippedItems.begin(),
			equippedItems.end(), 
			[&itemNameArg](auto& item) {return item.getItemName() == itemNameArg;
			}
		);
		// delete the item
		equippedItems.erase(newEnd, equippedItems.end());
	}
}

void Inventory::unequipItem(int indexEquippedArg) {
	if (indexEquippedArg != -1) {
		// getItemName
		std::string itemNameArg = equippedItems.at(indexEquippedArg).getItemName();
		// Move item to the end of the vector
		auto newEnd = std::remove_if(
			equippedItems.begin(),
			equippedItems.end(),
			[&itemNameArg](auto& item) {return item.getItemName() == itemNameArg;
			}
		);
		// delete the item
		equippedItems.erase(newEnd, equippedItems.end());
	}
}

void Inventory::decrementCarriedItem(Item itemArg) {
	std::string itemNameArg = itemArg.getItemName();
	// Check whether there is only one Item itemArg remaining
	if (carriedItemsAndAmounts.find(itemNameArg)->second == 1) {
		carriedItemsAndAmounts.erase(itemNameArg);
	}
	else {
		carriedItemsAndAmounts[itemNameArg] -= 1;
	}
}

void Inventory::incrementCarriedItem(Item itemArg) {
	std::string itemNameArg = itemArg.getItemName();
	carriedItemsAndAmounts[itemNameArg] += 1;
}

int Inventory::getIndexOfEquippedItemOfType(std::string itemTypeArg) {
	// Search across equippedItems for equipped Item of itemType itemTypeArg
	for (int i = 0; i < equippedItems.size(); i++) {
		if (equippedItems.at(i).getItemType() == itemTypeArg) {
			return i;
		}
	}
	// return code -1 means no such itemType itemTypeArg is currently equipped
	return -1;
}

int Inventory::getItemCount(std::string itemNameArg) {
	return carriedItemsAndAmounts[itemNameArg];
}

void Inventory::buyItem(Item itemArg) {
	// Get itemName
	std::string itemNameArg = itemArg.getItemName();

	// Add record of item to carriedItemsAndAmounts
	if (getItemCount(itemNameArg) == 0) {
		carriedItemsAndAmounts[itemNameArg] = 1;
	}
	// else increment item count
	else {
		carriedItemsAndAmounts[itemNameArg] += 1;
	}

	// Transact and calculate change
	int cost = itemArg.getItemValue() * buyMultiplier;
	int change = 0;

	int costCopper = cost % SILVER_VALUE;
	if (copperBits > costCopper) {
		copperBits -= costCopper;
	}
	else {
		copperBits -= costCopper;
		change += -copperBits;
		copperBits = 0;
	}
	cost -= costCopper;

	if (cost > 0) {
		int costSilver = cost % GOLD_VALUE;
		if (silverBobs > costSilver) {
			silverBobs -= costSilver;
		}
		else {
			silverBobs -= costSilver / SILVER_VALUE;
			change += -silverBobs;
			silverBobs = 0;
		}
		cost -= costSilver;
	}

	if (cost > 0) {
		int costGold = cost % PLATINUM_VALUE;
		if (goldCoins > costGold) {
			goldCoins -= costGold;
		}
		else {
			goldCoins -= costGold / GOLD_VALUE;
			change += -goldCoins;
			goldCoins = 0;
		}
		cost -= costGold;
	}

	if (cost > 0) {
		platinumChips -= cost / PLATINUM_VALUE;
	}

	// Increase currency by exact change
	receiveChange(change);
}

void Inventory::sellItem(Item itemArg) {
	int cost = itemArg.getItemValue() * sellMultiplier;
	int change = 0;

	int costCopper = cost % SILVER_VALUE;
	copperBits += costCopper;
	cost -= costCopper;

	if (cost > 0) {
		int costSilver = cost % GOLD_VALUE;
		silverBobs += costSilver / SILVER_VALUE;
		cost -= costSilver;
	}

	if (cost > 0) {
		int costGold = cost % PLATINUM_VALUE;
		goldCoins += cost / GOLD_VALUE;
		cost -= costGold;
	}

	if (cost > 0) {
		platinumChips += cost / PLATINUM_VALUE;
	}
}

void Inventory::receiveChange(int changeArg) {
	int changeCopper = changeArg % SILVER_VALUE;
	copperBits += changeCopper;
	changeArg -= changeCopper;

	if (changeArg > 0) {
		int changeSilver = changeArg % GOLD_VALUE;
		silverBobs += changeSilver / SILVER_VALUE;
		changeArg -= changeSilver;
	}

	if (changeArg > 0) {
		int changeGold = changeArg % PLATINUM_VALUE;
		goldCoins += changeArg / GOLD_VALUE;
		changeArg -= changeGold;
	}
}