#include <iostream>
#include <test.h>
#include <game.h>

int main() {
	// Start testing
	Test test;
	test.setupTests();
	// Initialize game
	Game game{};
	// Run game object
	game.start();
	// end game
	return 0;
}