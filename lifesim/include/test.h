#pragma once
#include <game.h>

#include <cctype>  // provides the tolower() function for char
#include <conio.h> // handles keyboard input via getch()

class Test
{
public:
	Test() {}
	~Test() {}

	Game testGame;
	Player testPlayer;
	Inventory testPlayerInventory;
	Inventory testShopInventory;
	Item frog_mouth_great_helm;
	Item mail_coif;
	Item iron_dagger;

	int setupTests() {
		std::cout << "THIS IS A TEST" << std::endl;

		testPlayerInventory.setBelongsTo("Player (TEST)");
		testShopInventory.setBelongsTo("Shop (TEST)");
		testShopInventory.setMaxTransaction(10000);

		// Frog Mouth Great Helm
		frog_mouth_great_helm.setItemSprite("\\sprites\\frog_mouth_great_helm.txt");
		frog_mouth_great_helm.setItemName("Frog-Mouth Great Helm");
		frog_mouth_great_helm.setItemType("Helmet");
		frog_mouth_great_helm.setItemDam(0);
		frog_mouth_great_helm.setItemDT(5);
		frog_mouth_great_helm.setItemValue(2000);

		// Mail Coif
		mail_coif.setItemSprite("\\sprites\\mail_coif.txt");
		mail_coif.setItemName("Mail Coif");
		mail_coif.setItemType("Helmet");
		mail_coif.setItemDam(0);
		mail_coif.setItemDT(2);
		mail_coif.setItemValue(800);

		// Iron Dagger
		iron_dagger.setItemName("Iron Dagger");
		iron_dagger.setItemType("Blade");
		iron_dagger.setItemDam(5);
		iron_dagger.setItemDT(0);
		iron_dagger.setItemValue(200);

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
			testPlayerInventory.incrementCarriedItem(iron_dagger);
		}

		runTests();
		return 1;
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
		char testChoice;
		while (testingBuy) {
			system("CLS");
			testShopInventory.printInventoryBuy();
			testPlayerInventory.printInventoryNeutral();
			std::cout << std::endl;
			std::cout << std::endl << "Enter 1 to buy frog helm, 2 to buy mail coif, 3 to return to main test branch: ";
			testChoice = _getch();
			switch (testChoice) {
			case '1':
				testPlayerInventory.buyItem(frog_mouth_great_helm);
				testShopInventory.sellItem(frog_mouth_great_helm);
				break;
			case '2':
				testPlayerInventory.buyItem(mail_coif);
				testShopInventory.sellItem(mail_coif);
				break;
			case '3':
				testingBuy = false;
				runTests();
				break;
			default:
				break;
			}
		}
	}

	void testBuyLoop() {

	}

	void testSell() {
		system("CLS");
		bool testingSell = true;
		std::string testChoice;
		while (testingSell) {
			system("CLS");
			testPlayerInventory.printInventorySell();
			std::cout << "Enter a number to sell an item, enter 0 to quit: ";
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
				if (testPlayerInventory.sellItem(indexChoice)) {
					testShopInventory.buyItem(testPlayerInventory.getFoundItem(indexChoice));
				}
			}
		}
	}

	void testNeutral() {
		system("CLS");
		bool testingNeutral = true;
		char testChoice;
		while (testingNeutral) {
			system("CLS");
			testPlayerInventory.printInventoryNeutral();
			std::cout << "Enter 1 to return to main test branch: ";
			testChoice = _getch();
			switch (testChoice) {
			case '1':
				testingNeutral = false;
				runTests();
				break;
			default:
				break;
			}
		}
	}
};