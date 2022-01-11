#pragma once
#include "Movement.h"
#include "GameBoard.h"

class GameState 
{
	public:
		GameState() : boardInstance(), moves(boardInstance) {}
		//bool isCheck();
		bool isDraw();
		void runGame();
		GameBoard boardInstance;
		Movement moves;
		bool isCheckmate;
		
};