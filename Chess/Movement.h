#pragma once
#include <utility>
#include <string>
#include <iostream>
#include "GameBoard.h"

class Movement 
{
	public:
		Movement(GameBoard& gameBoard) :m_board(gameBoard) {}

		bool enPassant(int start, int end);
		void castle();
		bool promotion(int start, int end);
		
		bool pawnMove(int start, int end); //remember to include double move
		bool knightMove(int start, int end);
		bool bishopMove(int start, int end);
		bool rookMove(int start, int end);
		bool queenMove(int start, int end);
		bool kingMove(int start, int end);
		
		std::pair <int, int> getUserInput(); 
		bool isValidMove(int start, int end);
		int convertUserInput(std::string UserInput);
private:
	GameBoard& m_board;
};
