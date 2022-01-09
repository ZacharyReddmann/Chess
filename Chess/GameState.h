#pragma once
#include "Movement.h"
#include "GameBoard.h"

class GameState 
{
	public:
		GameState() : boardInstance(), moves(boardInstance) {}
		//bool isCheck();
		bool isDraw();
		GameBoard boardInstance;
		Movement moves;
		bool isCheckmate;
		
};