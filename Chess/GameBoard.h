#pragma once
#include <iostream>
#include <array>
#include "GamePiece.h"
#include <vector>

class GameBoard {
	public:
		GameBoard():pieceBoard(makePieceBoard()) {}
		std::array<char, 64> board = 
		{
			'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', //(0-7)
			'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', //(8-15)
			'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', //(16-23)
			'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', //(24-31)
			'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', //(32-39)
			'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', //(40-47)
			'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', //(48-55)
			'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'  //(56-63)
		};

		//keep track where the pieces are
		std::array<GamePiece, 32> pieceBoard;		

		void updateBoard(int pStart, int start, int pEnd, int end);
		void printBoard();
	private:
		std::array<GamePiece, 32> makePieceBoard() 
		{
			std::array<GamePiece, 32> pBoard;
			int pieceIndex = 0;
			for (int i = 0; i < board.size(); i++)
			{
				char tempPiece = board[i];
				if (tempPiece != 'E') 
				{
					pBoard[pieceIndex].pieceType = g_pieceMapConverter[tempPiece];
					pBoard[pieceIndex].hasMoved = false;
					pBoard[pieceIndex].hasDoubleMoved = false;
					if (i < 16)
					{
						pBoard[pieceIndex].isWhite = false;
					}
					else
					{
						pBoard[pieceIndex].isWhite = true;
					}
					pBoard[pieceIndex].index = i;
					pieceIndex++;
				}
			}
			return pBoard;
		}
};



