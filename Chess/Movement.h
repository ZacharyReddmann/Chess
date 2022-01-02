#pragma once
#include <tuple>
#include <string>
#include <iostream>

class Movement 
{
	public:
		Movement(std::array<char, 64>& gameBoard) :m_board(gameBoard) {}

		void enPassant();
		void castle();
		void promotion();
		
		bool pawnMove(); //remember to include double move
		bool knightMove();
		bool bishopMove();
		bool rookMove();
		bool queenMove();
		bool kingMove();
		
		std::tuple <int, int> getUserInput(); 
		bool isValidMove();
		int convertUserInput(std::string UserInput);
private:
	std::array<char, 64>& m_board;
};
