#include "Game\Game.h"

int mainMB()
{
	Game game(800, 600);

	game.startUp();
	game.run();

    return 0;
}