#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include "GameBoard.h"

class Movement 
{
	public:
		Movement(GameBoard& gameBoard) :m_board(gameBoard) {}

		bool promotion(int start);
		bool isTileUnderAttack(int pBoardIndex, bool isWhiteTurn);
		
		bool isValidMove(int start, int end);
		bool pawnMove(int start, int end); 
		bool knightMove(int start, int end);
		bool bishopMove(int start, int end);
		bool rookMove(int start, int end);
		bool queenMove(int start, int end);
		bool kingMove(int start, int end);
		
		std::pair <int, int> getUserInput(); 
		int convertUserInput(std::string UserInput);
		GamePiece findPBoardElement(int startTile);
		int getPBoardIndexofElement(int index);

		void setTurn(bool wTurn) { m_whiteTurn = wTurn; }
		
		std::vector<int> getDangerTile() 
		{
			auto copy = m_dangerTiles;
			m_dangerTiles.clear();
			return copy;
		}

		void setErrorEnable(bool shouldDisplay) { m_errorEnable = shouldDisplay; }
		
		void printError(std::string& errorMessage) 
		{
			if (m_errorEnable)
				std::cout << errorMessage << std::endl;
		}

		void printError(std::string&& errorMessage)
		{
			if (m_errorEnable)
				std::cout << errorMessage << std::endl;
		}

private:
	GameBoard& m_board;
	bool m_whiteTurn = true;
	std::vector<int> m_dangerTiles;
	bool m_errorEnable;
};
