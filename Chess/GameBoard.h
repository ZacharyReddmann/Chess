#pragma once
#include <iostream>
#include <array>

class GameBoard {
	public:
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
		void updateBoard();
		void printBoard();
};

