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
	// Else no such Item equipped
}

void Inventory::unequipItem(int indexEquippedArg) {
	if (indexEquippedArg != -1) {
		// getItemName
		Item itemArg = equippedItems.at(indexEquippedArg);
		// locate item in the carriedItems vector
		auto it = std::find(equippedItems.begin(), equippedItems.end(), itemArg);

		// If the element was found, erase it
		if (it != equippedItems.end()) {
			equippedItems.erase(it);
		}
	}
}

void Inventory::decrementCarriedItem(Item itemArg) {
	// FIRST: Try to unequip the item
	unequipItem(itemArg);

	std::string itemNameArg = itemArg.getItemName();
	// SECOND: Check whether there is only one Item itemArg remaining
	if (carriedItemsAndAmounts.find(itemNameArg)->second == 1) {
		// If only one, erase the record 
		carriedItemsAndAmounts.erase(itemNameArg);
	}
	else {
		// Else decrement the item count
		carriedItemsAndAmounts[itemNameArg] -= 1;
	}
	// THIRD: locate item in the carriedItems vector
	auto it = std::find(carriedItems.begin(), carriedItems.end(), itemArg);

	// If the element was found, erase it
	if (it != carriedItems.end()) {
		carriedItems.erase(it);
	}
}

void Inventory::incrementCarriedItem(Item itemArg) {
	std::string itemNameArg = itemArg.getItemName();
	// Add record of item to carriedItemsAndAmounts
	if (getItemCount(itemNameArg) == 0) {
		carriedItemsAndAmounts[itemNameArg] = 1;
	}
	// else increment item count
	else {
		carriedItemsAndAmounts[itemNameArg] += 1;
	}
	// And add item to the carriedItems vector
	carriedItems.push_back(itemArg);
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

std::vector<Item> Inventory::getFoundItems() {
	return foundItems;
}

Item Inventory::getFoundItem(int indexArg) {
	return foundItems.at(indexArg);
}

Item Inventory::getCarriedItem(int indexArg) {
	return carriedItems.at(indexArg);
}

std::vector<Item> Inventory::getCarriedItems() {
	return carriedItems;
}

Item Inventory::getEquippedItem(int indexArg) {
	return equippedItems.at(indexArg);
}

std::vector<Item> Inventory::getEquippedItems() {
	return equippedItems;
}

int Inventory::getSellMult() {
	return sellMultiplier;
}

void Inventory::buyItem(Item itemArg) {

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

	// If applicable (shops/traders only), decrease maxTransaction
	if (maxTransaction > 0) {
		maxTransaction -= cost;
	}

	// Add item to the inventory
	incrementCarriedItem(itemArg);
}

// FIXME: This function might need to be deprecated due to the new: void sellItem(int) (SEE DIRECTLY BELOW)
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

	// If applicable (shops/traders only), increase maxTransaction
	if (maxTransaction > 0) {
		maxTransaction += cost;
	}

	// Remove one itemArg from inventory
	decrementCarriedItem(itemArg);
}

void Inventory::sellItem(int indexArg) {
	if ((indexArg < foundItems.size()) && (indexArg >= 0)) {
		Item itemArg = foundItems.at(indexArg);
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

		// If applicable (shops/traders only), increase maxTransaction
		if (maxTransaction > 0) {
			maxTransaction += cost;
		}

		// Remove one itemArg from inventory
		decrementCarriedItem(itemArg);
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

int Inventory::getTotalPurse() {
	auto totalPurseTemp = (copperBits * COPPER_VALUE)
		+ (silverBobs * SILVER_VALUE)
		+ (goldCoins * GOLD_VALUE)
		+ (platinumChips * PLATINUM_VALUE);

	if (totalPurseTemp >= 999999) {
		return 999999;
	}
	else { 
		return totalPurseTemp;
	}
}

std::string Inventory::getInventoryHeader() {
	std::string header = belongsTo; 
	header += "\n\'s Inventory \n";
	header += "________________________________________________________________________________________________\n";
	header += "\n";
	return header;
}

void Inventory::printInventorySell() {
	// Print the header
	std::cout << " |      Selling From: " << getInventoryHeader() << std::endl;
	
	foundItems.clear();

	int lineNo = 1;
	for (int i = 0; i < carriedItems.size(); i++) {
		bool itemFound = false;
		for (int j = 0; j < foundItems.size(); j++) {
			if (carriedItems.at(i) == foundItems.at(j)) {
				itemFound = true;
			}
		}
		if (itemFound == false) {
			// Add item to list of found item names
			foundItems.push_back(carriedItems.at(i));
			// Print single line with item data
			std::cout << " |      " << lineNo << ".";
			printItemLineSell(carriedItems.at(i));
			lineNo++;
		}
	}

	// Print the footer
	std::cout << "________________________________________________________________________________________________\n";
	std::cout << getInventoryFooterSell();
}

void Inventory::printItemLineSell(Item itemArg) {
	// Print the itemName and the amount on hand END WITH " | "
	std::cout << std::setw(22) << std::right << itemArg.getItemName();
	std::cout << " | "; 
	std::cout << std::setw(5) << std::right << carriedItemsAndAmounts[itemArg.getItemName()];
	std::cout << " | ";

	// Print the itemType and the damage/defense END WITH " | "
	std::cout << std::setw(6) << std::left << itemArg.getItemType();
	std::cout << " | ";
	// Two if statements: 
	//		Some items will have both Dam and DT ratings, e.g., spiked shields or large swords with crossguards
	if (itemArg.getItemDam() != 0) {
		std::cout << "Damage: ";
		std::cout << std::setw(3) << std::right << itemArg.getItemDam();
		std::cout << " | ";
	}
	else {
		std::cout << "            | ";
	}
	if (itemArg.getItemDT() != 0) {
		std::cout << "Defense: ";
		std::cout << std::setw(3) << std::right << itemArg.getItemDT();
		std::cout << " | ";
	}
	else {
		std::cout << "             | ";
	}

	// Print itemValue, END WITH NEWLINE
	std::cout << "Value: ";
	std::cout << std::right << std::setw(5) << itemArg.getItemValue() * sellMultiplier;
	std::cout << " | " << std::endl;
}

void Inventory::printInventoryBuy() {
	// Print the Header
	std::cout << " |      " << "Buying From: " << getInventoryHeader() << std::endl;

	// Use this vector to avoid printing repeat items
	foundItems.clear();
	int lineNo = 1;
	for (int i = 0; i < carriedItems.size(); i++) {
		bool itemFound = false;
		for (int j = 0; j < foundItems.size(); j++) {
			if (carriedItems.at(i) == foundItems.at(j)) {
				itemFound = true;
			}
		}
		if (itemFound == false) {
			// Add item to list of found item names
			foundItems.push_back(carriedItems.at(i));
			// Print single line with item data
			std::cout << " |      " << lineNo << ".";
			printItemLineBuy(carriedItems.at(i));
			lineNo++;
		}
	}
	// Print the footer
	std::cout << "________________________________________________________________________________________________\n";
	std::cout << getInventoryFooterBuy();
}

void Inventory::printItemLineBuy(Item itemArg) {
	// Print the itemName and the amount on hand END WITH " | "
	std::cout << std::setw(22) << std::right << itemArg.getItemName();
	std::cout << " | ";
	std::cout << std::setw(5) << std::right << carriedItemsAndAmounts[itemArg.getItemName()];
	std::cout << " | ";

	// Print the itemType and the damage/defense END WITH " | "
	std::cout << std::setw(6) << std::left << itemArg.getItemType();
	std::cout << " | ";
	// Two if statements: 
	//		Some items will have both Dam and DT ratings, e.g., spiked shields or large swords with crossguards
	if (itemArg.getItemDam() != 0) {
		std::cout << "Damage: ";
		std::cout << std::setw(3) << std::right << itemArg.getItemDam();
		std::cout << " | ";
	}
	else {
		std::cout << "            | ";
	}
	if (itemArg.getItemDT() != 0) {
		std::cout << "Defense: ";
		std::cout << std::setw(3) << std::right << itemArg.getItemDT();
		std::cout << " | ";
	}
	else {
		std::cout << "             | ";
	}

	// Print itemValue, END WITH NEWLINE
	std::cout << "Value: ";
	std::cout << std::right << std::setw(5) << itemArg.getItemValue() * buyMultiplier;
	std::cout << " | " << std::endl;
}

void Inventory::printInventoryNeutral() {
	// Print the Header
	std::cout << " |      " << getInventoryHeader() << std::endl;

	// Use this vector to avoid printing repeat items
	foundItems.clear();
	int lineNo = 1;
	for (int i = 0; i < carriedItems.size(); i++) {
		bool itemFound = false;
		for (int j = 0; j < foundItems.size(); j++) {
			if (carriedItems.at(i) == foundItems.at(j)) {
				itemFound = true;
			}
		}
		if (itemFound == false) {
			// Add item to list of found item names
			foundItems.push_back(carriedItems.at(i));
			// Print single line with item data
			std::cout << " |      " << lineNo << ".";
			printItemLineBuy(carriedItems.at(i));
			lineNo++;
		}
	}
	// Print the footer
	std::cout << "________________________________________________________________________________________________\n";
	std::cout << getInventoryFooterNeutral();
}

void Inventory::printItemLineNeutral(Item itemArg) {
	// Print the itemName and the amount on hand END WITH " | "
	std::cout << std::setw(22) << std::right << itemArg.getItemName();
	std::cout << " | ";
	std::cout << std::setw(5) << std::right << carriedItemsAndAmounts[itemArg.getItemName()];
	std::cout << " | ";

	// Print the itemType and the damage/defense END WITH " | "
	std::cout << std::setw(6) << std::left << itemArg.getItemType();
	std::cout << " | ";
	// Two if statements: 
	//		Some items will have both Dam and DT ratings, e.g., spiked shields or large swords with crossguards
	if (itemArg.getItemDam() != 0) {
		std::cout << "Damage: ";
		std::cout << std::setw(3) << std::right << itemArg.getItemDam();
		std::cout << " | ";
	}
	else {
		std::cout << "            | ";
	}
	if (itemArg.getItemDT() != 0) {
		std::cout << "Defense: ";
		std::cout << std::setw(3) << std::right << itemArg.getItemDT();
		std::cout << " | ";
	}
	else {
		std::cout << "             | ";
	}

	// Print itemValue, END WITH NEWLINE
	std::cout << "Value: ";
	std::cout << std::right << std::setw(5) << itemArg.getItemValue();
	std::cout << " | " << std::endl;
}

std::string Inventory::getInventoryFooterNeutral() {
	std::string footerSum = " |      ";
	footerSum += "Sum of moneys : ";
	int sum = 0;
	// Get
	sum += copperBits * COPPER_VALUE;
	sum += silverBobs * SILVER_VALUE;
	sum += goldCoins * GOLD_VALUE;
	sum += platinumChips * PLATINUM_VALUE;
	std::string sumStr = std::to_string(sum);
	// footerSum.append(" " + std::to_string(sum) + "\n");
	footerSum += sumStr + "\n";

	std::string footerPurse = " |      Purse: ";
	std::string purseC = std::to_string(copperBits);
	std::string purseS = std::to_string(silverBobs);
	std::string purseG = std::to_string(goldCoins);
	std::string purseP = std::to_string(platinumChips);
	
	// bool last will help determine whether to write a comma + space
	bool last = false;
	if (copperBits > 0) {
		footerPurse += purseC + " Copper Bits";
		last = true;
	}
	if (silverBobs > 0) {
		if (last) {
			footerPurse += ", " + purseS + " Silver Bobs";
		}
		else {
			footerPurse += purseS + " Silver Bobs";
		}
	}
	if (goldCoins > 0) {
		if (last) {
			footerPurse += ", " + purseG + " Gold Coins";
		}
		else {
			footerPurse += purseG + " Gold Coins";
		}
	}
	if (platinumChips > 0) {
		if (last) {
			footerPurse += ", " + purseP + " Platinum Chips";
		}
		else {
			footerPurse += purseP + " Platinum Chips";
		}
	}
	footerPurse += "\n";
	
	std::string footer = footerSum + footerPurse;
	return footer;
}

std::string Inventory::getInventoryFooterSell() {
	std::string footerSum = " |      ";
	footerSum += "Sum of moneys : ";
	int sum = 0;
	// Get
	sum += copperBits * COPPER_VALUE;
	sum += silverBobs * SILVER_VALUE;
	sum += goldCoins * GOLD_VALUE;
	sum += platinumChips * PLATINUM_VALUE;
	std::string sumStr = std::to_string(sum);
	footerSum += sumStr + "\n";

	std::string footerPurse = "Purse: ";
	std::string purseC = std::to_string(copperBits);
	std::string purseS = std::to_string(silverBobs);
	std::string purseG = std::to_string(goldCoins);
	std::string purseP = std::to_string(platinumChips);

	// bool last will help determine whether to write a comma + space
	bool last = false;
	if (copperBits > 0) {
		footerPurse += purseC + " Copper Bits";
		last = true;
	}
	if (silverBobs > 0) {
		if (last) {
			footerPurse += ", " + purseS + " Silver Bobs";
		}
		else {
			footerPurse += purseS + " Silver Bobs";
		}
	}
	if (goldCoins > 0) {
		if (last) {
			footerPurse += ", " + purseG + " Gold Coins";
		}
		else {
			footerPurse += purseG + " Gold Coins";
		}
	}
	if (platinumChips > 0) {
		if (last) {
			footerPurse += ", " + purseP + " Platinum Chips";
		}
		else {
			footerPurse += purseP + " Platinum Chips";
		}
	}
	footerPurse += "\n";

	std::string footer = footerSum + footerPurse;
	return footer;
}

std::string Inventory::getInventoryFooterBuy() {
	std::string footerSum = " |      ";
	footerSum += "Maximum Transaction: ";
	int sum = 0;
	// Get
	sum += copperBits * COPPER_VALUE;
	sum += silverBobs * SILVER_VALUE;
	sum += goldCoins * GOLD_VALUE;
	sum += platinumChips * PLATINUM_VALUE;
	std::string sumStr = std::to_string(sum);
	footerSum += sumStr + "\n";
	return footerSum;
}


// Mutators
void Inventory::setCurrency(int copperArg, int silverArg, int goldArg, int platArg) {
	copperBits = copperArg;
	silverBobs = silverArg;
	goldCoins = goldArg;
	platinumChips = platArg;
}

void Inventory::setMaxTransaction(int maxTransArg) {
	maxTransaction = maxTransArg;
}

void Inventory::setBuyMult(int multArg) {
	buyMultiplier = multArg;
}

void Inventory::setSellMult(int multArg) {
	sellMultiplier = multArg;
}

void Inventory::setBelongsTo(std::string belongsToArg) {
	belongsTo = belongsToArg;
}