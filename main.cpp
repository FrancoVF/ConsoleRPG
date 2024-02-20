#include <ctime>
#include <cstdlib>
#include "Game.h"
#include "Inventory.h"
#include "Item.h"
#include "Weapon.h"

int main()
{
	// srand(time(NULL));
	
	Game game;
	
	game.initGame();
	
	while (game.getPlaying())
	{
		game.mainMenu();
	}

	std::cout << "Hello, World!" << std::endl;

	return EXIT_SUCCESS;
}
