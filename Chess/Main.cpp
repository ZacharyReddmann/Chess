#include "GameBoard.h"
#include "GamePiece.h"
#include "Movement.h"
#include "GameState.h"


int main()
{
	//GameBoard gameBoard;
	//gameBoard.printBoard();
	GameState gameInstance;
	gameInstance.runGame();

	//user input calls isvalidmove determines which piece
	// isvalidmove calls the typemove to see if it works
	// if yes, update board
	// if no, userinput loop restarts 
	return -1;
}

