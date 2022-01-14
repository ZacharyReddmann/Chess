#include "GameState.h"

//UPDATE
bool GameState::checkForCheck()
{
	return false;
}

enum EndType
{
	CHECKMATE,
	DRAW, 
	SURRENDER,
	TIME,
	NONE
};

void GameState::swapTurn() 
{
	m_currentTurn = m_currentTurn ? false : true;
	moves.setTurn(m_currentTurn);
}

//UPDATE
bool GameState::isDraw() 
{
	return true;
}

//UPDATE
bool GameState::checkForGameEnd() 
{
	return false;
}

void GameState::runGame() 
{
	boardInstance.printBoard();
	
	/*
	EndType endType = EndType::NONE;
	while (endType == EndType::NONE)
	{
		bool checked = checkForCheck();
		moves.setCheck(checked);
		moves.getUserInput();
		boardInstance.printBoard();
		endType = checkForGameEnd();
		swapTurns();
	}
	*/

	while (true)
	{
		moves.getUserInput();
		boardInstance.printBoard();
		swapTurn();
	}
}

bool GameState::isCheckmate()
{
	/*if isCheck
		check if tiles around king are dangerous
		if false
			return false
			if true
				loop through each team piece to see if they can move to the tile*/

	bool checkWhiteKing = false;
	int tileIndexToCheck = -1;
	if (m_currentTurn)
	{
		checkWhiteKing = true;
		tileIndexToCheck = boardInstance.pieceBoard[28].index; //White King Index
	}

	else
	{
		checkWhiteKing = false;
		tileIndexToCheck = boardInstance.pieceBoard[4].index; //Black King Index
	}

	if (moves.isTileUnderAttack(tileIndexToCheck, checkWhiteKing)) 
	{
		//Every direction
		if(moves.isTileUnderAttack(tileIndexToCheck + 1))
	}

	return false; //CHANGE POSSIBLY
}