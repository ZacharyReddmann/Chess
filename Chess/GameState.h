#pragma once
#include "Movement.h"
#include "GameBoard.h"

class GameState 
{
	public:
		GameState() : boardInstance(), moves(boardInstance) {}
		
		
		bool checkForCheck();
		bool isCheckmate();
		bool checkForGameEnd();
		bool isDraw();
		
		void swapTurn();
		void runGame();
		
		bool m_isCheckmate;
		bool m_currentTurn;
		

		GameBoard boardInstance;
		Movement moves;
		
};