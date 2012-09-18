#include "Game\Game.h"

int mainMB()
{
	Game game(800, 600);

	game.startUp();
	game.run();

	system("PAUSE");
    return 0;
}