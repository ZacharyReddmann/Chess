#pragma once
#include "Movement.h"
#include "GameBoard.h"

class GameState 
{
	public:
		GameState() : board(), moves(board.board) {}
		bool isCheck();
		bool isDraw();
		GameBoard board;
		Movement moves;
		bool isCheckmate;
		
};