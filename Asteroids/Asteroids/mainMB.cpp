#include "Game\Game.h"

int mainMB()
{
	Game game;

	game.startUp();
	game.run();

	system("PAUSE");
    return 0;
}