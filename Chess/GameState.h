#pragma once
#include "Movement.h"
#include "GameBoard.h"

class GameState 
{
	public:
		GameState() : boardInstance(), moves(boardInstance) {}
		

		bool isCheckmate();
		void swapTurn();
		void runGame();
		
		bool m_isCheckmate;
		bool m_currentTurn = true;

		GameBoard boardInstance;
		Movement moves;
		
};