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

	// FIXME: Add more data, e.g., genetic, fitness, mood metrics

public:

	// Accessors
	std::string getName();
	bool getIsAlive();
	bool getIsSpecial();
	int getHP();
	int getMaxHP();
	

	// Mutators
	void setName(std::string);
	void killPlayer();
	void revivePlayer();
	void setIsSpecial();
	void setIsSpecial(bool);
	void setHP(int set);
	void setMaxHP(int set);

	// Display Stats
	void printHP();
};