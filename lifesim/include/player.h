#pragma once
#include <iostream>

class Player {
public:
	Player();
	~Player();
private:
	// Biographical Data
	std::string name;

	// Vital Data
	bool isAlive = true;
	bool isSpecial;

	int hp;
	int maxHP;

	// Geographic Data
	int playerX;
	int playerY;

	bool inTown;

	// FIXME: Add more data, e.g., genetic, fitness, mood metrics

public:

	// Accessors
	std::string getName();

	bool getIsAlive();
	bool getIsSpecial();

	int getHP();
	int getMaxHP();

	int getPlayerX();
	int getPlayerY();

	bool getInTown();
	

	// Mutators
	void setName(std::string);

	void killPlayer();
	void revivePlayer();
	void setIsSpecial();
	void setIsSpecial(bool);

	void setHP(int set);
	void setMaxHP(int set);

	// Geographical Mutators
	void setPlayerX(int set);
	void setPlayerY(int set);

	int incRetPlayerX();
	int incRetPlayerY();

	int decRetPlayerX();
	int decRetPlayerY();


	void incPlayerX();
	void incPlayerY();

	void decPlayerX();
	void decPlayerY();


	void setInTownTrue();
	void setInTownFalse();

	// Display Stats
	void printHP();
};