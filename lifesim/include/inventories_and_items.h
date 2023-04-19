#include <inventory.h>

/*
* 
*			DECLARE ALL ITEMS
* 
*/
struct AllItems {
	// HELMETS
	static Item inline plain_bascinet;
	static Item tusk_helm;
	static Item steel_helm;
	static Item frog_mouth_great_helm;
	static Item mail_coif;
};

void initializeItems() {
	Item::tusk_helm.setItemSprite("\\sprites\\armor\\helmets\\tusk_helm.txt");
	AllItems::tusk_helm.setItemName("Tusk Helm");
	AllItems::tusk_helm.setItemType("Helmet");
	AllItems::tusk_helm.setItemDam(0);
	AllItems::tusk_helm.setItemDT(2);
	AllItems::tusk_helm.setItemValue(100);

	AllItems::plain_bascinet.setItemSprite("\\sprites\\armor\\helmets\\plain_bascinet.txt");
	AllItems::plain_bascinet.setItemName("Plain Bascinet");
	AllItems::plain_bascinet.setItemType("Helmet");
	AllItems::plain_bascinet.setItemDam(0);
	AllItems::plain_bascinet.setItemDT(4);
	AllItems::plain_bascinet.setItemValue(400);

	AllItems::steel_helm.setItemSprite("\\sprites\\armor\\helmets\\steel_helm.txt");
	AllItems::steel_helm.setItemName("Steel Helm");
	AllItems::steel_helm.setItemType("Helmet");
	AllItems::steel_helm.setItemDam(0);
	AllItems::steel_helm.setItemDT(5);
	AllItems::steel_helm.setItemValue(1000);

	AllItems::frog_mouth_great_helm.setItemSprite("\\sprites\\armor\\helmets\\frog_mouth_great_helm.txt");
	AllItems::frog_mouth_great_helm.setItemName("Frog-Mouth Great Helm");
	AllItems::frog_mouth_great_helm.setItemType("Helmet");
	AllItems::frog_mouth_great_helm.setItemDam(0);
	AllItems::frog_mouth_great_helm.setItemDT(7);
	AllItems::frog_mouth_great_helm.setItemValue(2000);

	AllItems::mail_coif.setItemSprite("\\sprites\\armor\\helmets\\mail_coif.txt");
	AllItems::mail_coif.setItemName("Mail Coif");
	AllItems::mail_coif.setItemType("Helmet");
	AllItems::mail_coif.setItemDam(0);
	AllItems::mail_coif.setItemDT(3);
	AllItems::mail_coif.setItemValue(800);
}

/*
*
*			DECLARE ALL ITEMS
*
*/

Town thowerd;

void initializeTowns () {

	/*

			Towns

	*/

	// Thowerd Platz
	thowerd.setLocationX(68);
	thowerd.setLocationY(44);
	thowerd.setScreen("\\locations\\towns\\Thowerd_Platz.txt");
	thowerd.setTownAuxScreens("\\locations\\towns\\Thowerd_Smith.txt",
		"\\locations\\towns\\Thowerd_Grocer.txt",
		"\\locations\\towns\\Thowerd_Tavern.txt");
	thowerd.setInventories();
}