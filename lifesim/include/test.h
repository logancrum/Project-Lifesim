#pragma once
#include <game.h>

#include <cctype>  // provides the tolower() function for char
#include <conio.h> // handles keyboard input via getch()

class Test {
public:
	Test() {}
	~Test() {}

	Game testGame;
	Player testPlayer;
	Inventory testPlayerInventory;
	Inventory testShopInventory;
	Item frog_mouth_great_helm;
	Item mail_coif;
	Item steel_dagger;

	void setupTests() {
		std::cout << "THIS IS A TEST" << std::endl;

		testPlayerInventory.setBelongsTo("Player (TEST)");
		testShopInventory.setBelongsTo("Shop (TEST)");
		testShopInventory.setMaxTransaction(10000);

		// Frog Mouth Great Helm
		frog_mouth_great_helm.setItemSprite("\\sprites\\armor\\helmets\\frog_mouth_great_helm.txt");
		frog_mouth_great_helm.setItemName("Frog-Mouth Great Helm");
		frog_mouth_great_helm.setItemType("Helmet");
		frog_mouth_great_helm.setItemDam(0);
		frog_mouth_great_helm.setItemDT(5);
		frog_mouth_great_helm.setItemValue(2000);

		// Mail Coif
		mail_coif.setItemSprite("\\sprites\\armor\\helmets\\mail_coif.txt");
		mail_coif.setItemName("Mail Coif");
		mail_coif.setItemType("Helmet");
		mail_coif.setItemDam(0);
		mail_coif.setItemDT(2);
		mail_coif.setItemValue(800);

		// Iron Dagger
		steel_dagger.setItemName("Steel Dagger");
		steel_dagger.setItemSprite("\\sprites\\weapons\\daggers\\steel_dagger.txt");
		steel_dagger.setItemType("Blade");
		steel_dagger.setItemDam(5);
		steel_dagger.setItemDT(0);
		steel_dagger.setItemValue(200);

		testPlayerInventory.setCurrency(77, 20, 30, 10);
		testShopInventory.setCurrency(9999, 100, 100, 100);

		testPlayerInventory.setBuyMult(2);
		testPlayerInventory.setSellMult(1);

		testShopInventory.setBuyMult(1);
		testShopInventory.setSellMult(2);

		testShopInventory.incrementCarriedItem(frog_mouth_great_helm);
		testShopInventory.incrementCarriedItem(frog_mouth_great_helm);
		testShopInventory.incrementCarriedItem(frog_mouth_great_helm);

		testShopInventory.incrementCarriedItem(mail_coif);
		testShopInventory.incrementCarriedItem(mail_coif);
		testShopInventory.incrementCarriedItem(mail_coif);

		for (int i = 0; i < 200; i++) {
			testPlayerInventory.incrementCarriedItem(mail_coif);
		}
		testPlayerInventory.incrementCarriedItem(frog_mouth_great_helm);
		testPlayerInventory.incrementCarriedItem(frog_mouth_great_helm);
		testPlayerInventory.incrementCarriedItem(frog_mouth_great_helm);

		for (int i = 0; i < 10; i++) {
			testPlayerInventory.incrementCarriedItem(steel_dagger);
		}

		runTests();
	}

	int runTests() {
		bool testingInv = true;
		char testChoice;
		while (testingInv) {
			system("CLS");
			std::cout << "b: testBuy, s: testSell, i: see Player inv, r: reset test, q: quit";
			testChoice = _getch();
			switch (testChoice) {
			case 'b':
			case 'B':
				testBuy();
				break;
			case 's':
			case 'S':
				testSell();
				break;
			case 'i':
			case 'I':
				testNeutral();
				break;
			case 'r':
			case 'R':
				setupTests();
				break;
			case 'q':
			case 'Q':
				return 1;
				break;
			}
		}
		return -1;
	}

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

	void testNeutral() {
		system("CLS");
		bool testingNeutral = true;
		std::string testChoice;
		int indexChoice;
		

		// Variables for the sprite display loop
		bool displaying = true;
		std::string displayKey;

		while (testingNeutral) {
			system("CLS");
			testPlayerInventory.printInventoryNeutral();
			auto inventorySize = testPlayerInventory.getFoundItems().size();
			std::cout << "Enter a number to display an item sprite, 0 to quit: ";
			std::cin >> testChoice;
			indexChoice = stoi(testChoice) - 1;
			if (indexChoice == -1) {
				testingNeutral = false;
				// Return to shop screen
				runTests();
			}
			if ((indexChoice < inventorySize) && (indexChoice >= 0)) {
				displaying = true;
				while (displaying) {
					// Display the item at foundItems[indexChoice]
					system("CLS");
					testPlayerInventory.getFoundItem(indexChoice).printItemSprite();
					std::cout << std::endl << "Press 0 to exit. ";
					std::cin >> displayKey;
					if (displayKey == "0") {
						displaying = false;
					}
				}
				
			}
		}
	}
};