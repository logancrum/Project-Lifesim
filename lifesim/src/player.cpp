#include <player.h>

// Constructor & Destructor
Player::Player() 
{
	// Biographical Data
	name = "";

	// Vital Data
	isAlive = true;
	isSpecial;
	int hp = 0;
	int maxHP = 0;
}

Player::~Player()
{
}

// Accessors
std::string Player::getName() {
	return name;
}

bool Player::getIsAlive() {
	return isAlive;
}

bool Player::getIsSpecial() {
	return isSpecial;
}

int Player::getHP() {
	return hp;
}

int Player::getMaxHP() {
	return maxHP;
}

// Mutators
void Player::setName(std::string set) {
	name = set;
}
void Player::killPlayer() {
	isAlive = false;
	hp = 0;
	maxHP = 0;
}

void Player::revivePlayer() {
	isAlive = true;
	hp = 1;
	maxHP = 100;
}

void Player::setIsSpecial() {
	int special = rand() % 2 + 1;
	if (special == 1) {
		isSpecial = true;
	}
	else {
		isSpecial = false;
	}
}

void Player::setIsSpecial(bool specialness) {
	if (specialness) {
		isSpecial = true;
	}
	else {
		isSpecial = false;
	}
}

void Player::setHP(int set) {
	hp = set;
}

void Player::setMaxHP(int set) {
	maxHP = set;
}

// Display stats
void Player::printHP() {
	// HP: ( |><|><|><|><|><|> |  |  |  |  | ) = 55 / 100
	//  or maybe like:
	// HP: ( |<3|<3|<3|<3|<3|< |  |  |  |  | ) = 55 / 100
	int readHP = hp;
	int counter = 0;
	readHP -= (readHP % 5);
	std::cout << "HP: ( |";
	while (counter < 10) {
		if (readHP >= 10) {
			std::cout << "<3|";
			readHP -= 10;
		}
		else if ((readHP == 5)) {
			std::cout << "< |";
			readHP -= 5;
		}
		else {
			std::cout << "  |";
		}
		counter++;
	}
	std::cout << " )";
}