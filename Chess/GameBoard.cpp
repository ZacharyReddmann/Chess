#include "GameBoard.h"
#include "Movement.h"

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

void GameBoard::updateBoard(int pStart, int start, int pEnd, int end)
{
	if (board[end] != 'E')
	{
		pieceBoard[pEnd].index = -1;
		pieceBoard[pEnd].pieceType = piece::EMPTY;
	}

	pieceBoard[pStart].index = end;
	pieceBoard[pStart].hasMoved = true;
	board[start] = 'E';

	if (pieceBoard[pStart].pieceType == piece::PAWN) 
	{
		board[end] = 'P';
	}
	if (pieceBoard[pStart].pieceType == piece::ROOK)
	{
		board[end] = 'R';
	}
	if (pieceBoard[pStart].pieceType == piece::KNIGHT)
	{
		board[end] = 'N';
	}
	if (pieceBoard[pStart].pieceType == piece::BISHOP)
	{
		board[end] = 'B';
	}
	if (pieceBoard[pStart].pieceType == piece::QUEEN)
	{
		board[end] = 'Q';
	}
	if (pieceBoard[pStart].pieceType == piece::KING)
	{
		board[end] = 'K';
	}	
}