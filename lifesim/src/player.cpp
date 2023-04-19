#include <player.h>

// Constructor & Destructor
Player::Player() 
{
	// Biographical Data
	name = "";

	// Vital Data
	isAlive = true;
	setIsSpecial();
	int hp = 0;
	int maxHP = 0;

	playerX = 50;
	playerY = 40;
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

int Player::getPlayerX() {
	return playerX;
}

int Player::getPlayerY() {
	return playerY;
}

bool Player::getInTown() {
	return inTown;
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


// Player Geographic Data
void Player::setPlayerX(int set) {
	playerX = set;
}

void Player::setPlayerY(int set) {
	playerY = set;
}

int Player::incRetPlayerX() {
	playerX += 1;
	return playerX;
}

int Player::incRetPlayerY() {
	playerY += 1;
	return playerY;
}

int Player::decRetPlayerX() {
	playerX -= 1;
	return playerX;
}

int Player::decRetPlayerY() {
	playerY -= 1;
	return playerY;
}

void Player::incPlayerX() {
	playerX += 1;
}

void Player::incPlayerY() {
	playerY += 1;
}

void Player::decPlayerX() {
	playerX -= 1;
}

void Player::decPlayerY() {
	playerY -= 1;
}

void Player::setInTownTrue() {
	inTown = true;
}

void Player::setInTownFalse() {
	inTown = false;
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