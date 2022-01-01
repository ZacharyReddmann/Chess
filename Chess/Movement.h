#pragma once
#include <utility>
#include <string>

class Movement 
{
	public:
		void enPassant();
		void castle();
		void promotion();
		
		std::tuple <int, int> pawnMove(); //remember to include double move
		std::tuple <int, int> knightMove();
		std::tuple <int, int> bishopMove();
		std::tuple <int, int> rookMove();
		std::tuple <int, int> queenMove();
		std::tuple <int, int> kingMove();
		std::tuple <int, int> getUserInput();
		bool isValidMove();
		int convertUserInput(std::string UserInput);

};
