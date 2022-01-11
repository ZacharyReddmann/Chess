#include "GameState.h"

/*bool GameState::isCheck()
{
	return false;
}*/

bool GameState::isDraw() 
{
	return true;
}


void GameState::runGame() 
{
	boardInstance.printBoard();
	int i = 0;
	while (i < 100)
	{
		moves.getUserInput();
		boardInstance.printBoard();
		i++;
	}
}