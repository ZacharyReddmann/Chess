#include "GameState.h"

void GameState::swapTurn() 
{
	m_currentTurn = m_currentTurn ? false : true;
	moves.setTurn(m_currentTurn);
}

bool GameState::isStalemate() 
{
	bool checkWhite = false;
	int tileIndexToCheck = -1;
	if (m_currentTurn)
	{
		checkWhite = true;
		tileIndexToCheck = boardInstance.pieceBoard[28].index; //White King Index
	}

	else
	{
		checkWhite = false;
		tileIndexToCheck = boardInstance.pieceBoard[4].index; //Black King Index
	}

	if (!moves.isTileUnderAttack(tileIndexToCheck, checkWhite))
	{
		for (int i = 0; i < boardInstance.board.size(); i++) 
		{
			//check black
			if (!checkWhite) 
			{
				for (int j = 0; j < 16; j++) 
				{
					if (boardInstance.pieceBoard[j].pieceType != EMPTY || boardInstance.pieceBoard[j].index != -1)
					{
						if (boardInstance.pieceBoard[j].pieceType == PAWN)
						{
							if (moves.pawnMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == ROOK)
						{
							if (moves.rookMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == BISHOP)
						{
							if (moves.bishopMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == QUEEN)
						{
							if (moves.queenMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == KNIGHT)
						{
							if (moves.knightMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == KING)
						{
							if (moves.kingMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}
					}
				}
			}

			//check white
			else 
			{
				for (int j = 16; j < 32; j++) 
				{
					if (boardInstance.pieceBoard[j].pieceType != EMPTY)
					{
						if (boardInstance.pieceBoard[j].pieceType == PAWN)
						{
							if (moves.pawnMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == ROOK)
						{
							if (moves.rookMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == BISHOP)
						{
							if (moves.bishopMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == QUEEN)
						{
							if (moves.queenMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == KNIGHT)
						{
							if (moves.knightMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}

						else if (boardInstance.pieceBoard[j].pieceType == KING)
						{
							if (moves.kingMove(boardInstance.pieceBoard[j].index, i))
								return false;
						}
					}
				}
			}
		}
		std::cout << "Game is a draw due to stalemate" << std::endl;
		return true;
	}

	return false;
}

bool GameState::isThreeMoveRepitition()
{
	//3 Moves - Last 3 moves, make an array that stores moves. If 1, 3, 5 , equal each other and 2, 4, 6,
	return false;
}


void GameState::runGame() 
{
	boardInstance.printBoard();

	while (!isCheckmate() && !isStalemate() && !isThreeMoveRepitition())
	{
		moves.setErrorEnable(true);
		moves.getUserInput();
		boardInstance.printBoard();
		swapTurn();
	}
}

bool GameState::isCheckmate()
{

	bool checkWhite = false;
	int tileIndexToCheck = -1;
	if (m_currentTurn)
	{
		checkWhite = true;
		tileIndexToCheck = boardInstance.pieceBoard[28].index; //White King Index
	}

	else
	{
		checkWhite = false;
		tileIndexToCheck = boardInstance.pieceBoard[4].index; //Black King Index
	}

	moves.setErrorEnable(false);
	if (moves.isTileUnderAttack(tileIndexToCheck, checkWhite))
	{
		//Every tile around king
		//E
		if (!moves.isTileUnderAttack(tileIndexToCheck, checkWhite) && tileIndexToCheck + 1 == 'E')
		{
			return false;
		}

		//W
		if (!moves.isTileUnderAttack(tileIndexToCheck, checkWhite) && tileIndexToCheck - 1 == 'E')
		{
			return false;
		}

		//S
		if (tileIndexToCheck + 8 < 64) 
		{
			if (!moves.isTileUnderAttack(tileIndexToCheck, checkWhite) && tileIndexToCheck + 8 == 'E')
			{
				return false;
			}
		}
		
		//N
		if (tileIndexToCheck - 8 > 0) 
		{
			if (!moves.isTileUnderAttack(tileIndexToCheck, checkWhite) && tileIndexToCheck - 8 == 'E')
			{
				return false;
			}
		}
	
		//SE
		if (tileIndexToCheck + 9 < 64) 
		{
			if (!moves.isTileUnderAttack(tileIndexToCheck, checkWhite) && tileIndexToCheck + 9 == 'E')
			{
				return false;
			}
		}

		//NW
		if (tileIndexToCheck - 9 > 0) 
		{
			if (!moves.isTileUnderAttack(tileIndexToCheck, checkWhite) && tileIndexToCheck - 9 == 'E')
			{
				return false;
			}
		}
	
		//NE
		if (tileIndexToCheck - 7 > 0) 
		{
			if (!moves.isTileUnderAttack(tileIndexToCheck, checkWhite) && tileIndexToCheck - 7 == 'E')
			{
				return false;
			}
		}
		

		//SW
		if (tileIndexToCheck + 7 < 64) 
		{
			if (!moves.isTileUnderAttack(tileIndexToCheck, checkWhite) && tileIndexToCheck + 7 == 'E')
			{
				return false;
			}
		}
		
		auto dangerTiles = moves.getDangerTile();
		for (int i = 0; i < dangerTiles.size(); i++)
		{
			if (!checkWhite) 
			{
				for (int j = 0; j < 16; j++) 
				{
					if (boardInstance.pieceBoard[j].pieceType == piece::PAWN) 
					{
						if (moves.pawnMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if (boardInstance.pieceBoard[j].pieceType == piece::BISHOP)
					{
						if (moves.bishopMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if (boardInstance.pieceBoard[j].pieceType == piece::ROOK)
					{
						if (moves.rookMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if (boardInstance.pieceBoard[j].pieceType == piece::QUEEN)
					{
						if (moves.queenMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if (boardInstance.pieceBoard[j].pieceType == piece::KNIGHT)
					{
						if (moves.knightMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if ((boardInstance.pieceBoard[j].pieceType == piece::KING))
					{
						if (moves.kingMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							if (!moves.isTileUnderAttack(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
								return false;
					}
				}
			}

			//checking for white pieces
			else 
			{
				for (int j = 16; j < 32; j++) 
				{
					if (boardInstance.pieceBoard[j].pieceType == piece::PAWN)
					{
						if (moves.pawnMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if (boardInstance.pieceBoard[j].pieceType == piece::BISHOP)
					{
						if (moves.bishopMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if (boardInstance.pieceBoard[j].pieceType == piece::ROOK)
					{
						if (moves.rookMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if (boardInstance.pieceBoard[j].pieceType == piece::QUEEN)
					{
						if (moves.queenMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if (boardInstance.pieceBoard[j].pieceType == piece::KNIGHT)
					{
						if (moves.knightMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}

					if ((boardInstance.pieceBoard[j].pieceType == piece::KING))
					{
						if (moves.kingMove(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							if(!moves.isTileUnderAttack(boardInstance.pieceBoard[j].index, dangerTiles.at(i)))
							return false;
					}
				}
			}
		}
		m_isCheckmate = true;
	}

	if (m_isCheckmate)
	{
		if(checkWhite)
			std::cout << "Black won!" << std::endl;\
		else
			std::cout << "White won!" << std::endl;
	}
	return m_isCheckmate;
}