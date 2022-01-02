#include "GameBoard.h"

void GameBoard::printBoard()
{	
	for (int i = 0; i < board.size(); i++)
	{
		if (i == 8 || i == 16 || i == 24 || i == 32 || i == 40 || i == 48 || i == 56)
			std::cout << "\n" << board[i] << " ";
		else if (i == 63)
			std::cout << board[i] << " " << std::endl;
		else if (i < 63)
			std::cout << board[i] << " ";
	}
}

void GameBoard::updateBoard(int start, int end)
{
	//board[start] = 'E';
	//board[end] = pieceType?
}
