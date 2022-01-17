#include "Movement.h"
#include "GamePiece.h"


//ADD king condition to tile under attack

//Find the correct index for pieceBoard
GamePiece Movement::findPBoardElement(int startTile) 
{
	for (int i = 0; i < m_board.pieceBoard.size(); i++)
	{
		if (startTile == m_board.pieceBoard[i].index)
		{
			return m_board.pieceBoard[i];
		}
	}
	return { piece::EMPTY, true, true, true, -1 };
}


//Find the correct index for start in updateBoard
int Movement::getPBoardIndexofElement(int index)
{
	for (int i = 0; i < m_board.pieceBoard.size(); i++)
	{
		if (index == m_board.pieceBoard[i].index)
		{
			return i;
		}
	}
	return -1;
}


//Convert user input to index value
int Movement::convertUserInput(std::string userInput)
{
	char col = userInput[0];
	int row = userInput[1] - '0'; //ASCII
	int formula = 64 - (row * 8);

	if (col == 'A')
	{
		return formula;
	}

	else if (col == 'B')
	{
		return 1 + formula;
	}

	else if (col == 'C')
	{
		return 2 + formula;
	}

	else if (col == 'D')
	{
		return 3 + formula;
	}

	else if (col == 'E')
	{
		return 4 + formula;
	}

	else if (col == 'F')
	{
		return 5 + formula;
	}

	else if (col == 'G')
	{
		return 6 + formula;
	}

	else if (col == 'H')
	{
		return 7 + formula;
	}
	else
		return -900; 
}

std::pair<int, int> Movement::getUserInput()
{

	int pos1 = -1;
	int pos2 = -1;

	do
	{
		std::string firstPos;
		std::cout << "Please input the desired piece to move (ex. A2) : " << std::endl;
		std::cin >> firstPos;

		std::string secondPos;
		std::cout << "Please input the desired location to move your piece: " << std::endl;
		std::cin >> secondPos;

		pos1 = convertUserInput(firstPos);
		pos2 = convertUserInput(secondPos);
	} while (!isValidMove(pos1, pos2));

	return std::make_pair(pos1, pos2);
}

bool Movement::isValidMove(int start, int end) 
{
	bool isValid = false;

	bool checkWhiteKing = false;
	int tileIndexToCheck = -1;

	if (m_whiteTurn)
	{
		checkWhiteKing = true;
		tileIndexToCheck = m_board.pieceBoard[28].index; //White King Index
	}

	else
	{
		checkWhiteKing = false;
		tileIndexToCheck = m_board.pieceBoard[4].index; //Black King Index
	}


	if (findPBoardElement(start).isWhite != m_whiteTurn) 
	{
		std::cout << "That is not your piece" << std::endl;
		return false;
	}
	
	if (findPBoardElement(start).pieceType == piece::PAWN)
	{
		if(pawnMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			if (promotion(start)) 
			{
				m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			}
			isValid = true;
		}
	}
	else if (findPBoardElement(start).pieceType == piece::ROOK)
	{
		if (rookMove(start, end)) 
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			isValid = true;
		}
	}
	else if (findPBoardElement(start).pieceType == piece::KNIGHT)
	{
		if (knightMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			isValid = true;
		}
	}
	else if (findPBoardElement(start).pieceType == piece::BISHOP)
	{
		if (bishopMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			isValid = true;
		}
	}
	else if (findPBoardElement(start).pieceType == piece::QUEEN)
	{
		if (queenMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			isValid = true;
		}
	}
	else if (findPBoardElement(start).pieceType == piece::KING)
	{
		if (kingMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			isValid = true;
			if (m_whiteTurn)
			{
				tileIndexToCheck = m_board.pieceBoard[28].index; //White King Index
			}

			else
			{
				tileIndexToCheck = m_board.pieceBoard[4].index; //Black King Index
			}
		}
	}
	
	if (isTileUnderAttack(tileIndexToCheck, checkWhiteKing) && isValid)
	{
		isValid = false;
		m_board.updateBoard(getPBoardIndexofElement(end), end, getPBoardIndexofElement(start), start);
	}

	return isValid;
}

//FIX ME, NEED TO FIND A WAY TO UPDATE PIECE BOARD PIECE, MAYBE USE OTHER FUNCTION AT TOP
//Might be fixed - NOT FIXED
bool Movement::promotion(int start)
{
	if ((findPBoardElement(start).pieceType == piece::PAWN && findPBoardElement(start).index < 8) ||
		(findPBoardElement(start).pieceType == piece::PAWN && findPBoardElement(start).index < 64))
	{
		std::string userInput;
		std::cout << "Please enter Queen, Rook, Bishop, Knight to promote your pawn respectively" << std::endl;
		std::cin >> userInput;

		for (char& ch : userInput)
		{
			toupper(ch);
		}

		if (userInput == "QUEEN")
		{
			m_board.pieceBoard[getPBoardIndexofElement(start)].pieceType = piece::QUEEN;
			return true;
		}
		else if (userInput == "ROOK")
		{
			m_board.pieceBoard[getPBoardIndexofElement(start)].pieceType = piece::ROOK;
			return true;
		}
		else if (userInput == "KNIGHT")
		{
			m_board.pieceBoard[getPBoardIndexofElement(start)].pieceType = piece::KNIGHT;
			return true;
		}
		else if (userInput == "BISHOP")
		{
			m_board.pieceBoard[getPBoardIndexofElement(start)].pieceType = piece::BISHOP;
			return true;
		}
	}
	return false;
}

bool Movement::pawnMove(int start, int end)
{
	GamePiece pieceToMove = findPBoardElement(start); 
	char endTile = m_board.board[end];

	int movementOffset = 8;
	int takingOffsetLeft = 7;
	int takingOffsetRight = 9;

	bool checkWhiteKing = false;
	int tileIndexToCheck = -1;

	if (m_whiteTurn) 
	{
		checkWhiteKing = true;
		tileIndexToCheck = m_board.pieceBoard[28].index; //White King Index
	}

	else 
	{
		checkWhiteKing = false;
		tileIndexToCheck = m_board.pieceBoard[4].index; //Black King Index
	}

	if (pieceToMove.isWhite && m_whiteTurn)
	{
		if (endTile == 'E')
		{
			//standard move one tile
			if (pieceToMove.index - movementOffset == end)
			{
				return true;
			}

			//double move check
			if (pieceToMove.index - (movementOffset * 2) == end && !pieceToMove.hasMoved && m_board.board[pieceToMove.index - movementOffset] == 'E')
			{
				pieceToMove.hasDoubleMoved = true;
				return true;
			}
		}

		//Check if pawn is trying to take a piece
		GamePiece pieceToTake = findPBoardElement(end);
		if (pieceToTake.index != -1 && !pieceToTake.isWhite && endTile != 'E')
		{
			//take right check
			if (pieceToMove.index - takingOffsetLeft == end)
				return true;

			//take left check
			if (pieceToMove.index - takingOffsetRight == end)
				return true;
		}

		//En Passant
		if (pieceToMove.index >= 24 || pieceToMove.index <= 31)
		{
			if (!pieceToTake.isWhite && pieceToTake.hasDoubleMoved)
			{
				if (pieceToMove.index - 7 == end)
				{
					return true;
				}

				if (pieceToMove.index - 9 == end)
				{
					return true;
				}
			}
		}
		printError("Error, white pawn can not move there");
	}

	//black piece logic
	if (!pieceToMove.isWhite && !m_whiteTurn)
	{
		if (endTile == 'E')
		{
			//standard move one tile
			if (pieceToMove.index + movementOffset == end)
			{
				return true;
			}

			//double move check
			if (pieceToMove.index + (movementOffset * 2) == end && !pieceToMove.hasMoved && m_board.board[pieceToMove.index + movementOffset] == 'E')
			{
				pieceToMove.hasDoubleMoved = true;
				return true;
			}
		}

		//Check if pawn is trying to take a piece
		GamePiece pieceToTake = findPBoardElement(end);
		if (pieceToTake.index != -1 && pieceToTake.isWhite && endTile != 'E')
		{
			//take left check
			if (pieceToMove.index + takingOffsetLeft == end)
				return true;

			//take right check
			if (pieceToMove.index + takingOffsetRight == end)
				return true;
		}

		//En Passant
		if (pieceToMove.index >= 32 || pieceToMove.index <= 39)
		{
			if (pieceToTake.isWhite && pieceToTake.hasDoubleMoved)
			{
				if (pieceToMove.index + 7 == end)
				{
					return true;
				}

				if (pieceToMove.index + 9 == end)
				{
					return true;
				}
			}
		}
		printError("Error, black pawn can not move there");
	}
	return false;
}


bool Movement::knightMove(int start, int end)
{
	GamePiece pieceToMove = findPBoardElement(start); 
	char endTile = m_board.board[end];
	GamePiece pieceToTake = findPBoardElement(end);
	int ptmIndex = pieceToMove.index;

	//Named for white, use opposite for black
	int vMovementOffsetLeft = 17;
	int vMovementOffsetRight = 15;
	int hMovementOffsetRight = 6;
	int hMovementOffsetLeft = 10;

	bool checkWhiteKing = false;
	int tileIndexToCheck = -1;

	if (m_whiteTurn)
	{
		checkWhiteKing = true;
		tileIndexToCheck = m_board.pieceBoard[28].index; //White King Index
	}

	else
	{
		checkWhiteKing = false;
		tileIndexToCheck = m_board.pieceBoard[4].index; //Black King Index
	}


	//White Knight Logic
	if (pieceToMove.isWhite && m_whiteTurn) 
	{
		if (endTile == 'E' || !pieceToTake.isWhite)
		{
			//Vertical L Move
			//2up left
			if ((ptmIndex >= 17 && ptmIndex <= 23) || (ptmIndex >= 25 && ptmIndex <= 31) || (ptmIndex >= 33 && ptmIndex <= 39) || (ptmIndex >= 41 && ptmIndex <= 47) || (ptmIndex >= 49 && ptmIndex <= 55) || (ptmIndex >= 57 && ptmIndex <= 63)) 
			{
				if (pieceToMove.index - vMovementOffsetLeft == end)
					return true;
			}
		
			//2up right
			if ((ptmIndex >= 16 && ptmIndex <= 22) || (ptmIndex >= 24 && ptmIndex <= 30) || (ptmIndex >= 32 && ptmIndex <= 38) || (ptmIndex >= 40 && ptmIndex <= 46) || (ptmIndex >= 48 && ptmIndex <= 54) || (ptmIndex >= 56 && ptmIndex <= 62))
			{
				if (pieceToMove.index - vMovementOffsetRight == end)
					return true;
			}
			
			//2down right
			if ((ptmIndex >= 0 && ptmIndex <= 6) || (ptmIndex >= 8 && ptmIndex <= 14) || (ptmIndex >= 16 && ptmIndex <= 22) || (ptmIndex >= 24 && ptmIndex <= 30) || (ptmIndex >= 32 && ptmIndex <= 38) || (ptmIndex >= 40 && ptmIndex <= 46)) 
			{
				if (pieceToMove.index + vMovementOffsetLeft == end)
					return true;
			}
	
			//2down left
			if ((ptmIndex >= 1 && ptmIndex <= 7) || (ptmIndex >= 9 && ptmIndex <= 15) || (ptmIndex >= 17 && ptmIndex <= 23) || (ptmIndex >= 25 && ptmIndex <= 31) || (ptmIndex >= 33 && ptmIndex <= 39) || (ptmIndex >= 41 && ptmIndex <= 47))
			{
				if (pieceToMove.index + vMovementOffsetRight == end)
					return true;
			}
			
			//Horizontal L Move
			//up 2left
			if ((ptmIndex >= 10 && ptmIndex <= 15) || (ptmIndex >= 18 && ptmIndex <= 23) || (ptmIndex >= 26 && ptmIndex <= 31) || (ptmIndex >= 34 && ptmIndex <= 39) || (ptmIndex >= 42 && ptmIndex <= 47) || (ptmIndex >= 50 && ptmIndex <= 55) || (ptmIndex >= 58 && ptmIndex <= 63))
			{
				if (pieceToMove.index - hMovementOffsetLeft == end)
					return true;
			}

			//up 2right
			if ((ptmIndex >= 8 && ptmIndex <= 13) || (ptmIndex >= 16 && ptmIndex <= 21) || (ptmIndex >= 24 && ptmIndex <= 29) || (ptmIndex >= 32 && ptmIndex <= 37) || (ptmIndex >= 40 && ptmIndex <= 45) || (ptmIndex >= 48 && ptmIndex <= 53) || (ptmIndex >= 56 && ptmIndex <= 61))
			{
				if (pieceToMove.index - hMovementOffsetRight == end)
					return true;
			}

			//down 2 right
			if ((ptmIndex >= 0 && ptmIndex <= 5) || (ptmIndex >= 8 && ptmIndex <= 13) || (ptmIndex >= 16 && ptmIndex <= 21) || (ptmIndex >= 24 && ptmIndex <= 29) || (ptmIndex >= 32 && ptmIndex <= 37) || (ptmIndex >= 40 && ptmIndex <= 45) || (ptmIndex >= 48 && ptmIndex <= 53)) 
			{
				if (pieceToMove.index + hMovementOffsetLeft == end)
					return true;
			}
			
			//down 2left
			if ((ptmIndex >= 2 && ptmIndex <= 7) || (ptmIndex >= 10 && ptmIndex <= 15) || (ptmIndex >= 18 && ptmIndex <= 23) || (ptmIndex >= 26 && ptmIndex <= 31) || (ptmIndex >= 34 && ptmIndex <= 39) || (ptmIndex >= 42 && ptmIndex <= 47) || (ptmIndex >= 50 && ptmIndex <= 55))
			{
				if (pieceToMove.index + hMovementOffsetRight == end)
					return true;
			}
		}
		printError("Error, white knight cannot move there");
	}
		
	//Black Knight Logic
	if (!pieceToMove.isWhite && !m_whiteTurn)
	{
		if (endTile == 'E' || pieceToTake.isWhite)
		{
			//Vertical L Move
			//2up left
			if ((ptmIndex >= 17 && ptmIndex <= 23) || (ptmIndex >= 25 && ptmIndex <= 31) || (ptmIndex >= 33 && ptmIndex <= 39) || (ptmIndex >= 41 && ptmIndex <= 47) || (ptmIndex >= 49 && ptmIndex <= 55) || (ptmIndex >= 57 && ptmIndex <= 63))
			{
				if (pieceToMove.index - vMovementOffsetLeft == end)
					return true;
			}

			//2up right
			if ((ptmIndex >= 16 && ptmIndex <= 22) || (ptmIndex >= 24 && ptmIndex <= 30) || (ptmIndex >= 32 && ptmIndex <= 38) || (ptmIndex >= 40 && ptmIndex <= 46) || (ptmIndex >= 48 && ptmIndex <= 54) || (ptmIndex >= 56 && ptmIndex <= 62))
			{
				if (pieceToMove.index - vMovementOffsetRight == end)
					return true;
			}

			//2down right
			if ((ptmIndex >= 0 && ptmIndex <= 6) || (ptmIndex >= 8 && ptmIndex <= 14) || (ptmIndex >= 16 && ptmIndex <= 22) || (ptmIndex >= 24 && ptmIndex <= 30) || (ptmIndex >= 32 && ptmIndex <= 38) || (ptmIndex >= 40 && ptmIndex <= 46))
			{
				if (pieceToMove.index + vMovementOffsetLeft == end)
					return true;
			}

			//2down left
			if ((ptmIndex >= 1 && ptmIndex <= 7) || (ptmIndex >= 9 && ptmIndex <= 15) || (ptmIndex >= 17 && ptmIndex <= 23) || (ptmIndex >= 25 && ptmIndex <= 31) || (ptmIndex >= 33 && ptmIndex <= 39) || (ptmIndex >= 41 && ptmIndex <= 47))
			{
				if (pieceToMove.index + vMovementOffsetRight == end)
					return true;
			}

			//Horizontal L Move
			//up 2left
			if ((ptmIndex >= 10 && ptmIndex <= 15) || (ptmIndex >= 18 && ptmIndex <= 23) || (ptmIndex >= 26 && ptmIndex <= 31) || (ptmIndex >= 34 && ptmIndex <= 39) || (ptmIndex >= 42 && ptmIndex <= 47) || (ptmIndex >= 50 && ptmIndex <= 55) || (ptmIndex >= 58 && ptmIndex <= 63))
			{
				if (pieceToMove.index - hMovementOffsetLeft == end)
					return true;
			}

			//up 2right
			if ( (ptmIndex >= 9 && ptmIndex <= 13) || (ptmIndex >= 17 && ptmIndex <= 21) || (ptmIndex >= 25 && ptmIndex <= 29) || (ptmIndex >= 33 && ptmIndex <= 37) || (ptmIndex >= 41 && ptmIndex <= 45) || (ptmIndex >= 49 && ptmIndex <= 53) || (ptmIndex >= 57 && ptmIndex <= 61))
			{
				if (pieceToMove.index - hMovementOffsetRight == end)
					return true;
			}
			
			//down 2right
			if ((ptmIndex >= 0 && ptmIndex <= 5) || (ptmIndex >= 8 && ptmIndex <= 13) || (ptmIndex >= 16 && ptmIndex <= 21) || (ptmIndex >= 24 && ptmIndex <= 29) || (ptmIndex >= 32 && ptmIndex <= 37) || (ptmIndex >= 40 && ptmIndex <= 45) || (ptmIndex >= 48 && ptmIndex <= 53))
			{
				if (pieceToMove.index + hMovementOffsetLeft == end)
					return true;
			}

			//down 2left
			if ((ptmIndex >= 2 && ptmIndex <= 7) || (ptmIndex >= 10 && ptmIndex <= 15) || (ptmIndex >= 18 && ptmIndex <= 23) || (ptmIndex >= 26 && ptmIndex <= 31) || (ptmIndex >= 34 && ptmIndex <= 39) || (ptmIndex >= 42 && ptmIndex <= 47) || (ptmIndex >= 50 && ptmIndex <= 55))
			{
				if (pieceToMove.index + hMovementOffsetRight == end)
					return true;
			}
		}
		printError("Error, black knight cannot move there");
	}
	return false;
}

bool Movement::bishopMove(int start, int end)
{
	GamePiece pieceToMove = findPBoardElement(start);
	char endTile = m_board.board[end];
	GamePiece pieceToTake = findPBoardElement(end);
	int ptmIndex = pieceToMove.index;

	int tilesToTravelByNine = ((end - pieceToMove.index) / 9);
	if (tilesToTravelByNine < 0) 
	{
		tilesToTravelByNine = tilesToTravelByNine * -1;
	}
	
	int tilesToTravelBySeven = ((end - pieceToMove.index) / 7);
	if (tilesToTravelBySeven < 0)
	{
		tilesToTravelBySeven = tilesToTravelBySeven * -1;
	}

	bool chooseNine = false;
	bool chooseSeven = false;
	bool emptyDiag = false;

	if (((end - pieceToMove.index) % 9) == 0)
	{
		chooseNine = true;
	}
	else if (((end - pieceToMove.index) % 7) == 0)
	{
		chooseSeven = true;
	}

	bool checkWhiteKing = false;
	int tileIndexToCheck = -1;

	if (m_whiteTurn)
	{
		checkWhiteKing = true;
		tileIndexToCheck = m_board.pieceBoard[28].index; //White King Index
	}

	else
	{
		checkWhiteKing = false;
		tileIndexToCheck = m_board.pieceBoard[4].index; //Black King Index
	}

	//White bishop
	if (pieceToMove.isWhite && m_whiteTurn)
	{
		if (endTile == 'E' || !pieceToTake.isWhite)
		{
			if (chooseNine)
			{
				//SE
				if (ptmIndex < 55 && ptmIndex != 47 && ptmIndex != 39 && ptmIndex != 31 && ptmIndex != 23 && ptmIndex != 15 && ptmIndex != 7) 
				{
					if (ptmIndex + (9 * tilesToTravelByNine) == end)
					{
						if (tilesToTravelByNine == 1)
						{
							emptyDiag = true;
						}

						else
						{
							for (int i = 1; i < tilesToTravelByNine; i++)
							{
								if (findPBoardElement(start + (9 * i)).pieceType == piece::EMPTY)
								{
									emptyDiag = true;
								}
								else
								{
									emptyDiag = false;
									break;
								}
							}
						}
					}
				}
				
				//NW
				if (ptmIndex > 8 && ptmIndex != 16 && ptmIndex != 24 && ptmIndex != 32 && ptmIndex != 40 && ptmIndex != 48 && ptmIndex != 56) 
				{
					if (ptmIndex - (9 * tilesToTravelByNine) == end)
					{
						if (tilesToTravelByNine == 1)
						{
							emptyDiag = true;
						}

						else
						{
							for (int i = 1; i < tilesToTravelByNine; i++)
							{
								if (findPBoardElement(start - (9 * i)).pieceType == piece::EMPTY)
								{
									emptyDiag = true;
								}
								else
								{
									emptyDiag = false;
									break;
								}
							}
						}
					}
				}
			}

			if (chooseSeven)
			{
				//SW
				if (ptmIndex < 56 && ptmIndex != 0 && ptmIndex != 8 && ptmIndex != 16 && ptmIndex != 24 && ptmIndex != 32 && ptmIndex != 40 && ptmIndex != 48) 
				{
					if (ptmIndex + (7 * tilesToTravelBySeven) == end)
					{
						if (tilesToTravelBySeven == 1)
						{
							emptyDiag = true;
						}

						else
						{
							for (int i = 1; i < tilesToTravelBySeven; i++)
							{
								if (findPBoardElement(start + (7 * i)).pieceType == piece::EMPTY)
								{
									emptyDiag = true;
								}
								else
								{
									emptyDiag = false;
									break;
								}
							}
						}
					}
				}

				//NE
				if (ptmIndex > 7 && ptmIndex != 63 && ptmIndex != 55 && ptmIndex != 47 && ptmIndex != 39 && ptmIndex != 31 && ptmIndex != 23 && ptmIndex != 15) 
				{
					if (ptmIndex - (7 * tilesToTravelBySeven) == end)
					{
						if (tilesToTravelBySeven == 1)
						{
							emptyDiag = true;
						}

						else
						{
							for (int i = 1; i < tilesToTravelBySeven; i++)
							{
								if (findPBoardElement(start - (7 * i)).pieceType == piece::EMPTY)
								{
									emptyDiag = true;
								}
								else
								{
									emptyDiag = false;
									break;
								}
							}
						}
					}
				}
			}
		}
			
		if (emptyDiag)
		{
			return true;
		}
		else
		{
			if (findPBoardElement(start).pieceType == piece::BISHOP)
			{
				printError("Error, white bishop cannot move there");
			}
			return false;
		}
	}


	//Black bishop
	if (!pieceToMove.isWhite && !m_whiteTurn)
	{
		if (endTile == 'E' || pieceToTake.isWhite)
		{
			if (chooseNine)
			{
				//Black SE
				if (ptmIndex < 55 && ptmIndex != 47 && ptmIndex != 39 && ptmIndex != 31 && ptmIndex != 23 && ptmIndex != 15 && ptmIndex != 7) 
				{
					if (pieceToMove.index + (9 * tilesToTravelByNine) == end)
					{
						if (tilesToTravelByNine == 1)
						{
							emptyDiag = true;
						}

						else
						{
							for (int i = 1; i < tilesToTravelByNine; i++)
							{
								if (findPBoardElement(start + (9 * i)).pieceType == piece::EMPTY)
								{
									emptyDiag = true;
								}
								else
								{
									emptyDiag = false;
									break;
								}
							}
						}
					}
				}

				//Black NW
				if (ptmIndex > 8 && ptmIndex != 16 && ptmIndex != 24 && ptmIndex != 32 && ptmIndex != 40 && ptmIndex != 48 && ptmIndex != 56) 
				{
					if (pieceToMove.index - (9 * tilesToTravelByNine) == end)
					{
						if (tilesToTravelByNine == 1)
						{
							emptyDiag = true;
						}

						else
						{
							for (int i = 1; i < tilesToTravelByNine; i++)
							{
								if (findPBoardElement(start - (9 * i)).pieceType == piece::EMPTY)
								{
									emptyDiag = true;
								}
								else
								{
									emptyDiag = false;
									break;
								}
							}
						}
					}
				}
			}

			if (chooseSeven)
			{
				//Black SW
				if (ptmIndex < 56 && ptmIndex != 0 && ptmIndex != 8 && ptmIndex != 16 && ptmIndex != 24 && ptmIndex != 32 && ptmIndex != 40 && ptmIndex != 48) 
				{
					if (pieceToMove.index + (7 * tilesToTravelBySeven) == end)
					{
						if (tilesToTravelBySeven == 1)
						{
							emptyDiag = true;
						}

						else
						{
							for (int i = 1; i < tilesToTravelBySeven; i++)
							{
								if (findPBoardElement(start + (7 * i)).pieceType == piece::EMPTY)
								{
									emptyDiag = true;
								}
								else
								{
									emptyDiag = false;
									break;
								}
							}
						}
					}
				}

				//Black NE
				if (ptmIndex > 7 && ptmIndex != 63 && ptmIndex != 55 && ptmIndex != 47 && ptmIndex != 39 && ptmIndex != 31 && ptmIndex != 23 && ptmIndex != 15) 
				{
					if (pieceToMove.index - (7 * tilesToTravelBySeven) == end)
					{
						if (tilesToTravelBySeven == 1)
						{
							emptyDiag = true;
						}

						else
						{
							for (int i = 1; i < tilesToTravelBySeven; i++)
							{
								if (findPBoardElement(start - (7 * i)).pieceType == piece::EMPTY)
								{
									emptyDiag = true;
								}
								else
								{
									emptyDiag = false;
									break;
								}
							}
						}
					}
				}
			}
		}

		if (emptyDiag)
		{
			return true;
		}

		else
		{
			if (findPBoardElement(start).pieceType == piece::BISHOP)
			{
				printError("Error, black bishop cannot move there");
			}
			return false;
		}
	}
	return false;
}
	

bool Movement::rookMove(int start, int end)
{
	GamePiece pieceToMove = findPBoardElement(start);
	char endTile = m_board.board[end];
	GamePiece pieceToTake = findPBoardElement(end);

	int tilesToTravelByEight = ((end - pieceToMove.index) / 8);
	if (tilesToTravelByEight < 0)
	{
		tilesToTravelByEight = tilesToTravelByEight * -1;
	}

	int tilesToTravelByOne = end - pieceToMove.index;
	if (tilesToTravelByOne < 0)
	{
		tilesToTravelByOne = tilesToTravelByOne * -1;
	}

	bool chooseEight = false;
	bool emptyHorizontal = false;
	bool emptyVertical = false;

	if (((end - pieceToMove.index) % 8) == 0)
	{
		chooseEight = true;
	}
	
	bool checkWhiteKing = false;
	int tileIndexToCheck = -1;
	if (m_whiteTurn)
	{
		checkWhiteKing = true;
		tileIndexToCheck = m_board.pieceBoard[28].index; //White King Index
	}

	else
	{
		checkWhiteKing = false;
		tileIndexToCheck = m_board.pieceBoard[4].index; //Black King Index
	}

	if (pieceToMove.isWhite && m_whiteTurn)
	{
		if (endTile == 'E' || !pieceToTake.isWhite)
		{
			if (chooseEight)
			{
				//S
				if (pieceToMove.index + (8 * tilesToTravelByEight) == end)
				{
					if (tilesToTravelByEight == 1)
					{
						emptyVertical = true;
					}

					else
					{
						for (int i = 1; i < tilesToTravelByEight; i++)
						{
							if (findPBoardElement(start + (8 * i)).pieceType == piece::EMPTY)
							{
								emptyVertical = true;
							}
							else
							{
								emptyVertical = false;
								break;
							}
						}
					}
				}

				//N
				if (pieceToMove.index - (8 * tilesToTravelByEight) == end)
				{
					if (tilesToTravelByEight == 1)
					{
						emptyVertical = true;
					}

					else
					{
						for (int i = 1; i < tilesToTravelByEight; i++)
						{
							if (findPBoardElement(start - (8 * i)).pieceType == piece::EMPTY)
							{
								emptyVertical = true;
							}
							else
							{
								emptyVertical = false;
								break;
							}
						}
					}
				}
			}

			else
			{
				//E
				if (pieceToMove.index + tilesToTravelByOne == end)
				{
					if (tilesToTravelByOne == 1)
					{
						emptyHorizontal = true;
					}

					else
					{
						for (int i = 1; i < tilesToTravelByOne; i++)
						{
							if (findPBoardElement(start + i).pieceType == piece::EMPTY) //Replace with just + i possibly
							{
								emptyHorizontal = true;
							}
							else
							{
								emptyHorizontal = false;
								break;
							}
						}
					}
				}

				//W
				if (pieceToMove.index - tilesToTravelByOne == end)
				{
					if (tilesToTravelByOne == 1)
					{
						emptyHorizontal = true;
					}

					else
					{
						for (int i = 1; i < tilesToTravelByOne; i++)
						{
							if (findPBoardElement(start - i).pieceType == piece::EMPTY)
							{
								emptyHorizontal = true;
							}
							else
							{
								emptyHorizontal = false;
								break;
							}
						}
					}
				}
			}
		}
			
		if (emptyHorizontal || emptyVertical)
		{
			return true;
		}
		else
		{
			if (findPBoardElement(start).pieceType == piece::ROOK)
			{
				printError("Error, white rook can't move there");
			}
			return false;
		}
	}

	//Black Rook
	if (!pieceToMove.isWhite && !m_whiteTurn)
	{
		if (endTile == 'E' || pieceToTake.isWhite)
		{
			if (chooseEight)
			{
				//S
				if (pieceToMove.index + (8 * tilesToTravelByEight) == end)
				{
					if (tilesToTravelByEight == 1)
					{
						emptyVertical = true;
					}

					else
					{
						for (int i = 1; i < tilesToTravelByEight; i++)
						{
							if (findPBoardElement(start + (8 * i)).pieceType == piece::EMPTY)
							{
								emptyVertical = true;
							}
							else
							{
								emptyVertical = false;
								break;
							}
						}
					}
				}

				//N
				if (pieceToMove.index - (8 * tilesToTravelByEight) == end)
				{
					if (tilesToTravelByEight == 1)
					{
						emptyVertical = true;
					}

					else
					{
						for (int i = 1; i < tilesToTravelByEight; i++)
						{
							if (findPBoardElement(start - (8 * i)).pieceType == piece::EMPTY)
							{
								emptyVertical = true;
							}
							else
							{
								emptyVertical = false;
								break;
							}
						}
					}
				}
			}

			else
			{
				//E
				if (pieceToMove.index + tilesToTravelByOne == end)
				{
					if (tilesToTravelByOne == 1)
					{
						emptyHorizontal = true;
					}

					else
					{
						for (int i = 1; i < tilesToTravelByOne; i++)
						{
							if (findPBoardElement(start + i).pieceType == piece::EMPTY) //Replace with just + i possibly
							{
								emptyHorizontal = true;
							}
							else
							{
								emptyHorizontal = false;
								break;
							}
						}
					}
				}

				//W
				if (pieceToMove.index - tilesToTravelByOne == end)
				{
					if (tilesToTravelByOne == 1)
					{
						emptyHorizontal = true;
					}

					else
					{
						for (int i = 1; i < tilesToTravelByOne; i++)
						{
							if (findPBoardElement(start - i).pieceType == piece::EMPTY)
							{
								emptyHorizontal = true;
							}
							else
							{
								emptyHorizontal = false;
								break;
							}
						}
					}
				}
			}
		}

		if (emptyHorizontal || emptyVertical)
		{
			return true;
		}
		else
		{
			if (findPBoardElement(start).pieceType == piece::ROOK) 
			{
				printError("Error, black rook can't move there");
			}
			return false;
		}
	}
	return false;
}

bool Movement::queenMove(int start, int end) 
{
	GamePiece pieceToMove = findPBoardElement(start);

	bool checkWhiteKing = false;
	int tileIndexToCheck = -1;
	if (m_whiteTurn)
	{
		checkWhiteKing = true;
		tileIndexToCheck = m_board.pieceBoard[28].index; //White King Index
	}

	else
	{
		checkWhiteKing = false;
		tileIndexToCheck = m_board.pieceBoard[4].index; //Black King Index
	}

	//White Queen
	if (pieceToMove.isWhite && m_whiteTurn) 
	{
		if (((end - pieceToMove.index) % 9) == 0 || ((end - pieceToMove.index) % 7) == 0)
		{
			if (bishopMove(start, end))
			{
				return true;
			}

			//needed for unique cases such as 40 to 47 where bishop would get flagged but it really is moving as a rook
			else if (rookMove(start, end))
			{
				return true;
			}
		}

		else
		{
			if (rookMove(start, end))
			{
				return true;
			}
		}
		printError("Error, white queen cannot move there");
		return false;
	}

	//Black Queen
	if (!pieceToMove.isWhite && !m_whiteTurn)
	{
		if (((end - pieceToMove.index) % 9) == 0 || ((end - pieceToMove.index) % 7) == 0)
		{
			if (bishopMove(start, end))
			{
				return true;
			}

			//needed for unique cases such as 40 to 47 where bishop would get flagged but it really is moving as a rook
			else if (rookMove(start, end))
			{
				return true;
			}
		}

		else
		{
			if (rookMove(start, end))
			{
				return true;
			}
		}
		printError("Error, black queen cannot move there");
		return false;
	}
	return false;
}

bool Movement::kingMove(int start, int end)
{
	GamePiece pieceToMove = findPBoardElement(start);
	GamePiece pieceToTake = findPBoardElement(end);
	char endTile = m_board.board[end]; 
	int startTileIndex = start;
	int endTileIndex = end;

	int verticalOffset = 8;
	int horizontalOffset = 1;
	int diagNwSeOffset = 9;
	int diagSwNeOffset = 7;

	//White King
	if (pieceToMove.isWhite && m_whiteTurn)
	{
		if (endTile == 'E' || !pieceToTake.isWhite) 
		{
			//S
			if (pieceToMove.index + verticalOffset == end)
				return true;
			
			//E
			if (pieceToMove.index + horizontalOffset == end)
				return true;
			
			//SE
			if (pieceToMove.index + diagNwSeOffset == end)
				return true;
			
			//SW
			if (pieceToMove.index + diagSwNeOffset == end)
				return true;

			//N
			if (pieceToMove.index - verticalOffset == end)
				return true;

			//W
			if (pieceToMove.index - horizontalOffset == end)
				return true;

			//NW
			if (pieceToMove.index - diagNwSeOffset == end)
				return true;

			//NE
			if (pieceToMove.index - diagSwNeOffset == end)
				return true;
		}
	}

	//Black King
	if (!pieceToMove.isWhite && !m_whiteTurn)
	{
		if (endTile == 'E' || pieceToTake.isWhite)
		{
			//S
			if (pieceToMove.index + verticalOffset == end)
				return true;

			//E
			if (pieceToMove.index + horizontalOffset == end)
				return true;

			//SE
			if (pieceToMove.index + diagNwSeOffset == end)
				return true;

			//SW
			if (pieceToMove.index + diagSwNeOffset == end)
				return true;

			//N
			if (pieceToMove.index - verticalOffset == end)
				return true;

			//W
			if (pieceToMove.index - horizontalOffset == end)
				return true;

			//NW
			if (pieceToMove.index - diagNwSeOffset == end)
				return true;

			//NE
			if (pieceToMove.index - diagSwNeOffset == end)
				return true;
		}
	}


	bool checkWhiteKing = false;
	int tileIndexToCheck = -1;
	if (m_whiteTurn)
	{
		checkWhiteKing = true;
		tileIndexToCheck = m_board.pieceBoard[28].index; //White King Index
	}

	else
	{
		checkWhiteKing = false;
		tileIndexToCheck = m_board.pieceBoard[4].index; //Black King Index
	}

	//Castling for White King
	if (pieceToMove.isWhite && m_whiteTurn)
	{
		//King starting tile and end tile
		if (startTileIndex == 60 && endTileIndex == 62) 
		{
			//KING SIDE CASTLING - Make sure king and east rook has not moved
			if (!pieceToMove.hasMoved && !m_board.pieceBoard[31].hasMoved)
			{
				//Empty tiles between
				if (m_board.board[end - 1] == 'E' && endTile == 'E')
				{
					//King is not in check
					if (!isTileUnderAttack(tileIndexToCheck, checkWhiteKing))
					{
						//tiles are not under attack
						if (!isTileUnderAttack(tileIndexToCheck + 1, checkWhiteKing) && !isTileUnderAttack(tileIndexToCheck + 2, checkWhiteKing))
						{
							//king goes two spaces to E and rook goes 2 spaces to W
							m_board.board[tileIndexToCheck + 1] = 'R';
							m_board.pieceBoard[31].hasMoved = true;
							m_board.pieceBoard[31].index = tileIndexToCheck + 1;

							m_board.board[end + 1] = 'E';
							return true;
						}
					}
				}
			}
		}

		//QUEEN SIDE CASTLING - Make sure king and west rook has not moved
		if (startTileIndex == 60 && endTileIndex == 58) 
		{
			if (!pieceToMove.hasMoved && !m_board.pieceBoard[24].hasMoved)
			{
				//Empty tiles between
				if (m_board.board[end + 1] == 'E' && m_board.board[end - 1] == 'E' && endTile == 'E')
				{
					//King is not in check
					if (!isTileUnderAttack(tileIndexToCheck, checkWhiteKing))
					{
						//tiles are not under attack
						if (!isTileUnderAttack(tileIndexToCheck - 1, checkWhiteKing) && !isTileUnderAttack(tileIndexToCheck - 2, checkWhiteKing) && !isTileUnderAttack(tileIndexToCheck - 3, checkWhiteKing))
						{
							//king goes two spaces W and rook goes 3 spaces E
							m_board.board[tileIndexToCheck - 1] = 'R';
							m_board.pieceBoard[24].hasMoved = true;
							m_board.pieceBoard[24].index = tileIndexToCheck - 1;

							m_board.board[end - 2] = 'E';
							return true;
						}
					}
				}
			}
		}
		
		
	}

	//Castling for Black King
	if (!pieceToMove.isWhite && !m_whiteTurn)
	{
		if (startTileIndex == 4 && endTileIndex == 6) 
		{
			//KING SIDE CASTLING - Make sure king and east rook has not moved
			if (!pieceToMove.hasMoved && !m_board.pieceBoard[7].hasMoved)
			{
				//Empty tiles between
				if (m_board.board[end - 1] == 'E' && endTile == 'E')
				{
					//King is not in check
					if (!isTileUnderAttack(tileIndexToCheck, checkWhiteKing))
					{
						//tiles are not under attack
						if (!isTileUnderAttack(tileIndexToCheck + 1, checkWhiteKing) && !isTileUnderAttack(tileIndexToCheck + 2, checkWhiteKing))
						{
							//king goes two spaces to E and rook goes 2 spaces to W
							m_board.board[tileIndexToCheck + 1] = 'R';
							m_board.pieceBoard[7].hasMoved = true;
							m_board.pieceBoard[7].index = tileIndexToCheck + 1;

							m_board.board[end + 1] = 'E';
							return true;
						}
					}
				}
			}
		}
		
		if (startTileIndex == 4 && endTileIndex == 2) 
		{
			//QUEEN SIDE CASTLING - Make sure king and west rook has not moved
			if (!pieceToMove.hasMoved && !m_board.pieceBoard[0].hasMoved)
			{
				//Empty tiles between
				if (m_board.board[end + 1] == 'E' && m_board.board[end - 1] == 'E' && endTile == 'E')
				{
					//King is not in check
					if (!isTileUnderAttack(tileIndexToCheck, checkWhiteKing))
					{
						//tiles are not under attack
						if (!isTileUnderAttack(tileIndexToCheck - 1, checkWhiteKing) && !isTileUnderAttack(tileIndexToCheck - 2, checkWhiteKing) && !isTileUnderAttack(tileIndexToCheck - 3, checkWhiteKing))
						{
							//king goes two spaces W and rook goes 3 spaces E
							m_board.board[tileIndexToCheck - 1] = 'R';
							m_board.pieceBoard[0].hasMoved = true;
							m_board.pieceBoard[0].index = tileIndexToCheck - 1;

							m_board.board[end - 2] = 'E';
							return true;
						}
					}
				}
			}
		}
	}
	printError("King cant move there right now");
	return false;
}


bool Movement::isTileUnderAttack(int pBoardIndex, bool isWhiteTurn) 
{
	if (isWhiteTurn) 
	{	
		//North
		int tempNorthIndex = pBoardIndex;
		int tilesToAdd = 1;
		while (tempNorthIndex - 8 > 0) //bounds checking
		{
			//check for teammate
			if (findPBoardElement(tempNorthIndex - 8).isWhite && findPBoardElement(tempNorthIndex - 8).index != -1)
			{
				break;
			}
			
			//check for not teammate or empty
			if (!findPBoardElement(tempNorthIndex - 8).isWhite || m_board.board[tempNorthIndex - 8] == 'E')
			{

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::ROOK)
				{
					for (int i = 0; i < tilesToAdd; i++) 
					{
						m_dangerTiles.push_back(tempNorthIndex - 8);
						tempNorthIndex = tempNorthIndex + 8;
					}
					return true;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::QUEEN)
				{
					for (int i = 0; i < tilesToAdd; i++) 
					{
						m_dangerTiles.push_back(tempNorthIndex - 8); //match
						tempNorthIndex = tempNorthIndex + 8; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::PAWN)
				{
					break;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::KNIGHT)
				{
					break;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::BISHOP)
				{
					break;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::KING)
				{
					break;
				}
			}
			tempNorthIndex = tempNorthIndex - 8;
			tilesToAdd++;
		}

		//South
		int tempSouthIndex = pBoardIndex;
		tilesToAdd = 1;
		while (tempSouthIndex + 8 < 64) //bounds checking
		{
			//check for teammate
			if (findPBoardElement(tempSouthIndex + 8).isWhite && findPBoardElement(tempSouthIndex + 8).index != -1)
			{
				break;
			}

			//check for not teammate or empty
			if (!findPBoardElement(tempSouthIndex + 8).isWhite || m_board.board[tempSouthIndex + 8] == 'E')
			{

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::ROOK)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempSouthIndex + 8); //match
						tempSouthIndex = tempSouthIndex - 8; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::QUEEN)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempSouthIndex + 8); //match
						tempSouthIndex = tempSouthIndex - 8; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::PAWN)
				{
					break;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::KNIGHT)
				{
					break;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::BISHOP)
				{
					break;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::KING)
				{
					break;
				}
			}
			tempSouthIndex = tempSouthIndex + 8;
			tilesToAdd++;
		}

		//East
		int tempEastIndex = pBoardIndex;
		tilesToAdd = 1;
		while (tempEastIndex + 1 != 8 && tempEastIndex + 1 != 16 && tempEastIndex + 1 != 24 && tempEastIndex + 1 != 32 && tempEastIndex + 1 != 40 && tempEastIndex + 1 != 48 && tempEastIndex + 1 != 56 && tempEastIndex + 1 != 64)
		{
			//check for teammate
			if (findPBoardElement(tempEastIndex + 1).isWhite && findPBoardElement(tempEastIndex + 1).index != -1)
			{
				break;
			}

			//check for not teammate or empty
			if (!findPBoardElement(tempEastIndex + 1).isWhite || m_board.board[tempEastIndex + 1] == 'E')
			{

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::ROOK)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempEastIndex + 1); //match
						tempEastIndex = tempEastIndex - 1; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::QUEEN)
				{
					for (int i = 0; i < tilesToAdd; i++) 
					{
						m_dangerTiles.push_back(tempEastIndex + 1); //match
						tempEastIndex = tempEastIndex - 1; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::PAWN)
				{
					break;
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::KNIGHT)
				{
					break;
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::BISHOP)
				{
					break;
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::KING)
				{
					break;
				}
			}
			tempEastIndex = tempEastIndex + 1;
			tilesToAdd++;
		}

		//West
		int tempWestIndex = pBoardIndex;
		tilesToAdd = 1;
		while (tempWestIndex - 1 != -1 && tempWestIndex - 1 != 7 && tempWestIndex - 1 != 15 && tempWestIndex - 1 != 23 && tempWestIndex - 1 != 31 && tempWestIndex - 1 != 39 && tempWestIndex - 1 != 47 && tempWestIndex - 1 != 55)
		{
			//check for teammate
			if (findPBoardElement(tempWestIndex - 1).isWhite && findPBoardElement(tempWestIndex - 1).index != -1)
			{
				break;
			}

			//check for not teammate or empty
			if (!findPBoardElement(tempWestIndex - 1).isWhite || m_board.board[tempWestIndex - 1] == 'E')
			{

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::ROOK)
				{
					for (int i = 0; i < tilesToAdd; i++) 
					{
						m_dangerTiles.push_back(tempWestIndex - 1); //match
						tempWestIndex = tempWestIndex + 1; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::QUEEN)
				{
					for (int i = 0; i < tilesToAdd; i++) 
					{
						m_dangerTiles.push_back(tempWestIndex - 1); //match
						tempWestIndex = tempWestIndex + 1; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::PAWN)
				{
					break;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::KNIGHT)
				{
					break;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::BISHOP)
				{
					break;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::KING)
				{
					break;
				}
			}
			tempWestIndex = tempWestIndex - 1;
			tilesToAdd++;
		}

		//NW
		int tempNorthWestIndex = pBoardIndex;
		tilesToAdd = 1;
		int pawnCheck = tempNorthWestIndex - 9;
		if (tempNorthWestIndex - 9 > 0)
		{
			//covers the bounds checking for left col and top row
			while (tempNorthWestIndex - 9 > 0 && tempNorthWestIndex - 9 != 47 && tempNorthWestIndex - 9 != 39 && tempNorthWestIndex - 9 != 31 && tempNorthWestIndex - 9 != 23 && tempNorthWestIndex - 9 != 15 && tempNorthWestIndex - 9 != 7)
			{

				//check for teammate
				if (findPBoardElement(tempNorthWestIndex - 9).isWhite && findPBoardElement(tempNorthWestIndex - 9).index != -1)
				{
					break;
				}

				if (!findPBoardElement(pawnCheck).isWhite && findPBoardElement(pawnCheck).index != -1 && findPBoardElement(pawnCheck).pieceType == piece::PAWN)
				{
					m_dangerTiles.push_back(pawnCheck);
					return true;
				}

				//check for not teammate or empty
				if (!findPBoardElement(tempNorthWestIndex - 9).isWhite || m_board.board[tempNorthWestIndex - 9] == 'E')
				{

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::BISHOP)
					{
						for (int i = 0; i < tilesToAdd; i++) 
						{
							m_dangerTiles.push_back(tempNorthWestIndex - 9); //match
							tempNorthWestIndex = tempNorthWestIndex + 9; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::QUEEN)
					{
						for (int i = 0; i < tilesToAdd; i++) 
						{
							m_dangerTiles.push_back(tempNorthWestIndex - 9); //match
							tempNorthWestIndex = tempNorthWestIndex + 9; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::PAWN)
					{
						break;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::KNIGHT)
					{
						break;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::ROOK)
					{
						break;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::KING)
					{
						break;
					}
				}
				tempNorthWestIndex = tempNorthWestIndex - 9;
				tilesToAdd++;
			}
		}

		//NE
		int tempNorthEastIndex = pBoardIndex;
		tilesToAdd = 1;
		pawnCheck = tempNorthEastIndex - 7;
		if (tempNorthEastIndex - 7 > 0)
		{
			//covers the bounds checking for right col and top row
			while (tempNorthEastIndex - 7 > 0 && tempNorthEastIndex - 7 != 56 && tempNorthEastIndex - 7 != 48 && tempNorthEastIndex - 7 != 40 && tempNorthEastIndex - 7 != 32 && tempNorthEastIndex - 7 != 24 && tempNorthEastIndex - 7 != 16 && tempNorthEastIndex - 7 != 8)
			{

				//check for teammate
				if (findPBoardElement(tempNorthEastIndex - 7).isWhite && findPBoardElement(tempNorthEastIndex - 7).index != -1)
				{
					break;
				}

				if (!findPBoardElement(pawnCheck).isWhite && findPBoardElement(pawnCheck).index != -1 && findPBoardElement(pawnCheck).pieceType == piece::PAWN)
				{
					m_dangerTiles.push_back(pawnCheck);
					return true;
				}

				//check for not teammate or empty
				if (!findPBoardElement(tempNorthEastIndex - 7).isWhite || m_board.board[tempNorthEastIndex - 7] == 'E')
				{

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::BISHOP)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempNorthEastIndex - 7); //match
							tempNorthEastIndex = tempNorthEastIndex + 7; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::QUEEN)
					{
						for (int i = 0; i < tilesToAdd; i++) 
						{
							m_dangerTiles.push_back(tempNorthEastIndex - 7); //match
							tempNorthEastIndex = tempNorthEastIndex + 7; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::PAWN)
					{
						break;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::KNIGHT)
					{
						break;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::ROOK)
					{
						break;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::KING)
					{
						break;
					}
				}
				tempNorthEastIndex = tempNorthEastIndex - 7;
				tilesToAdd++;
			}
		}

		//SW
		int tempSouthWestIndex = pBoardIndex;
		tilesToAdd = 1;
		if (tempSouthWestIndex + 7 < 64)
		{
			//covers the bounds checking for left col and bottom row
			while (tempSouthWestIndex + 7 < 64 && tempSouthWestIndex + 7 != 63 && tempSouthWestIndex + 7 != 55 && tempSouthWestIndex + 7 != 47 && tempSouthWestIndex + 7 != 39 && tempSouthWestIndex + 7 != 31 && tempSouthWestIndex + 7 != 23 && tempSouthWestIndex + 7 != 15 && tempSouthWestIndex + 7 != 7)
			{
				//check for teammate
				if (findPBoardElement(tempSouthWestIndex + 7).isWhite && findPBoardElement(tempSouthWestIndex + 7).index != -1)
				{
					break;
				}

				//check for not teammate or empty
				if (!findPBoardElement(tempSouthWestIndex + 7).isWhite || m_board.board[tempSouthWestIndex + 7] == 'E')
				{

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::BISHOP)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempSouthWestIndex + 7); //match
							tempSouthWestIndex = tempSouthWestIndex - 7; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::QUEEN)
					{
						for (int i = 0; i < tilesToAdd; i++) 
						{
							m_dangerTiles.push_back(tempSouthWestIndex + 7); //match
							tempSouthWestIndex = tempSouthWestIndex - 7; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::PAWN)
					{
						break;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::KNIGHT)
					{
						break;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::ROOK)
					{
						break;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::KING)
					{
						break;
					}
				}
				tempSouthWestIndex = tempSouthWestIndex + 7;
				tilesToAdd++;
			}
		}
		
		//SE
		int tempSouthEastIndex = pBoardIndex;
		tilesToAdd = 1;
		if (tempSouthEastIndex + 9 < 64)
		{
			//covers the bounds checking for right col and bottom row
			while (tempSouthEastIndex + 9 < 64 && tempSouthEastIndex + 9 != 56 && tempSouthEastIndex + 9 != 48 && tempSouthEastIndex + 9 != 40 && tempSouthEastIndex + 9 != 32 && tempSouthEastIndex + 9 != 24 && tempSouthEastIndex + 9 != 16)
			{

				//check for teammate
				if (findPBoardElement(tempSouthEastIndex + 9).isWhite && findPBoardElement(tempSouthEastIndex + 9).index != -1)
				{
					break;
				}

				//check for not teammate or empty
				if (!findPBoardElement(tempSouthEastIndex + 9).isWhite || m_board.board[tempSouthEastIndex + 9] == 'E')
				{

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::BISHOP)
					{
						for (int i = 0; i < tilesToAdd; i++) 
						{
							m_dangerTiles.push_back(tempSouthEastIndex + 9); //match
							tempSouthEastIndex = tempSouthEastIndex - 9; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::QUEEN)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempSouthEastIndex + 9); //match
							tempSouthEastIndex = tempSouthEastIndex - 9; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::PAWN)
					{
						break;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::KNIGHT)
					{
						break;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::ROOK)
					{
						break;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::KING)
					{
						break;
					}
				}
				tempSouthEastIndex = tempSouthEastIndex + 9;
				tilesToAdd++;
			}
		}

		//White Knight 
		int tempKnightIndex = pBoardIndex;
		if (tempKnightIndex + 17 < 64) 
		{
			if (!findPBoardElement(tempKnightIndex + 17).isWhite && findPBoardElement(tempKnightIndex + 17).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex + 17);
				return true;
			}
		}
		
		if (tempKnightIndex + 10 < 64)
		{
			if (!findPBoardElement(tempKnightIndex + 10).isWhite && findPBoardElement(tempKnightIndex + 10).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex + 10);
				return true;
			}
		}
		
		if (tempKnightIndex + 15 < 64)
		{
			if (!findPBoardElement(tempKnightIndex + 15).isWhite && findPBoardElement(tempKnightIndex + 15).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex + 15);
				return true;
			}
		}
		
		if (tempKnightIndex + 6 < 64)
		{
			if (!findPBoardElement(tempKnightIndex + 6).isWhite && findPBoardElement(tempKnightIndex + 6).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex + 6);
				return true;
			}
		}

		if (tempKnightIndex - 17 >= 0) 
		{
			if (!findPBoardElement(tempKnightIndex - 17).isWhite && findPBoardElement(tempKnightIndex - 17).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex - 17);
				return true;
			}
		}
		
		if (tempKnightIndex - 10 >= 0)
		{
			if (!findPBoardElement(tempKnightIndex - 10).isWhite && findPBoardElement(tempKnightIndex - 10).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex - 10);
				return true;
			}
		}

		if (tempKnightIndex - 15 >= 0)
		{
			if (!findPBoardElement(tempKnightIndex - 15).isWhite && findPBoardElement(tempKnightIndex - 15).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex - 15);
				return true;
			}
		}
		
		if (tempKnightIndex - 6 >= 0)
		{
			if (!findPBoardElement(tempKnightIndex - 6).isWhite && findPBoardElement(tempKnightIndex - 6).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex - 6);
				return true;
			}
		}
		return false;
	}

	//black turn
	else
	{
		//Black North
		int tempNorthIndex = pBoardIndex;
		int tilesToAdd = 1;
		while (tempNorthIndex - 8 > 0) //bounds checking
		{
			//check for teammate
			if (!findPBoardElement(tempNorthIndex - 8).isWhite && findPBoardElement(tempNorthIndex - 8).index != -1)
			{
				break;
			}

			//check for not teammate or empty
			if (findPBoardElement(tempNorthIndex - 8).isWhite || m_board.board[tempNorthIndex - 8] == 'E')
			{

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::ROOK)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempNorthIndex - 8); //match
						tempNorthIndex = tempNorthIndex + 8; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::QUEEN)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempNorthIndex - 8); //match
						tempNorthIndex = tempNorthIndex + 8; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::PAWN)
				{
					break;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::KNIGHT)
				{
					break;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::BISHOP)
				{
					break;
				}

				if (findPBoardElement(tempNorthIndex - 8).pieceType == piece::KING)
				{
					break;
				}
			}
			tempNorthIndex = tempNorthIndex - 8;
			tilesToAdd++;
		}

		//Black South
		int tempSouthIndex = pBoardIndex;
		tilesToAdd = 1;
		while (tempSouthIndex + 8 < 64) //bounds checking
		{
			//check for teammate
			if (!findPBoardElement(tempSouthIndex + 8).isWhite && findPBoardElement(tempSouthIndex + 8).index != -1)
			{
				break;
			}

			//check for not teammate or empty
			if (findPBoardElement(tempSouthIndex + 8).isWhite || m_board.board[tempSouthIndex + 8] == 'E')
			{

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::ROOK)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempSouthIndex + 8); //match
						tempSouthIndex = tempSouthIndex - 8; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::QUEEN)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempSouthIndex + 8); //match
						tempSouthIndex = tempSouthIndex - 8; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::PAWN)
				{
					break;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::KNIGHT)
				{
					break;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::BISHOP)
				{
					break;
				}

				if (findPBoardElement(tempSouthIndex + 8).pieceType == piece::KING)
				{
					break;
				}
			}
			tempSouthIndex = tempSouthIndex + 8;
			tilesToAdd++;
		}

		//Black East
		int tempEastIndex = pBoardIndex;
		tilesToAdd = 1;
		while (tempEastIndex + 1 < 64 && tempEastIndex + 1 != 8 && tempEastIndex + 1 != 16 && tempEastIndex + 1 != 24 && tempEastIndex + 1 != 32 && tempEastIndex + 1 != 40 && tempEastIndex + 1 != 48 && tempEastIndex + 1 != 56 && tempEastIndex + 1 != 64)
		{
			//check for teammate
			if (!findPBoardElement(tempEastIndex + 1).isWhite && findPBoardElement(tempEastIndex + 1).index != -1)
			{
				break;
			}

			//check for not teammate or empty
			if (findPBoardElement(tempEastIndex + 1).isWhite || m_board.board[tempEastIndex + 1] == 'E')
			{

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::ROOK)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempEastIndex + 1); //match
						tempEastIndex = tempEastIndex - 1; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::QUEEN)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempEastIndex + 1); //match
						tempEastIndex = tempEastIndex - 1; //opposite
					}
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::PAWN)
				{
					break;
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::KNIGHT)
				{
					break;
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::BISHOP)
				{
					break;
				}

				if (findPBoardElement(tempEastIndex + 1).pieceType == piece::KING)
				{
					break;
				}
			}
			tempEastIndex = tempEastIndex + 1;
			tilesToAdd++;
		}

		//Black West
		int tempWestIndex = pBoardIndex;
		tilesToAdd = 1;
		while (tempWestIndex - 1 != -1 && tempWestIndex - 1 != 7 && tempWestIndex - 1 != 15 && tempWestIndex - 1 != 23 && tempWestIndex - 1 != 31 && tempWestIndex - 1 != 39 && tempWestIndex - 1 != 47 && tempWestIndex - 1 != 55)
		{
			//check for teammate
			if (!findPBoardElement(tempWestIndex - 1).isWhite && findPBoardElement(tempWestIndex - 1).index != -1)
			{
				break;
			}

			//check for not teammate or empty
			if (findPBoardElement(tempWestIndex - 1).isWhite || m_board.board[tempEastIndex - 1] == 'E')
			{

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::ROOK)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempWestIndex - 1); //match
						tempWestIndex = tempWestIndex + 1; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::QUEEN)
				{
					for (int i = 0; i < tilesToAdd; i++)
					{
						m_dangerTiles.push_back(tempWestIndex - 1); //match
						tempWestIndex = tempWestIndex + 1; //opposite
					}
					return true;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::PAWN)
				{
					break;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::KNIGHT)
				{
					break;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::BISHOP)
				{
					break;
				}

				if (findPBoardElement(tempWestIndex - 1).pieceType == piece::KING)
				{
					break;
				}
			}
			tempWestIndex = tempWestIndex - 1;
			tilesToAdd++;
		}

		//Black NW
		int tempNorthWestIndex = pBoardIndex;
		tilesToAdd = 1;
		if (tempNorthWestIndex - 9 > 0)
		{
			//covers the bounds checking for left col and top row
			while (tempNorthWestIndex - 9 > 0 && tempNorthWestIndex - 9 != 47 && tempNorthWestIndex - 9 != 39 && tempNorthWestIndex - 9 != 31 && tempNorthWestIndex - 9 != 23 && tempNorthWestIndex - 9 != 15 && tempNorthWestIndex - 9 != 7)
			{
				//check for teammate
				if (!findPBoardElement(tempNorthWestIndex - 9).isWhite && findPBoardElement(tempNorthWestIndex - 9).index != -1)
				{
					break;
				}

				//check for not teammate or empty
				if (findPBoardElement(tempNorthWestIndex - 9).isWhite || m_board.board[tempNorthWestIndex - 9] == 'E')
				{

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::BISHOP)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempNorthWestIndex - 9); //match
							tempNorthWestIndex = tempNorthWestIndex + 9; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::QUEEN)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempNorthWestIndex - 9); //match
							tempNorthWestIndex = tempNorthWestIndex + 9; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::PAWN)
					{
						break;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::KNIGHT)
					{
						break;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::ROOK)
					{
						break;
					}

					if (findPBoardElement(tempNorthWestIndex - 9).pieceType == piece::KING)
					{
						break;
					}
				}
				tempNorthWestIndex = tempNorthWestIndex - 9;
				tilesToAdd++;
			}
		}

		//Black NE
		int tempNorthEastIndex = pBoardIndex;
		tilesToAdd = 1;
		if (tempNorthEastIndex - 7 > 0)
		{
			//covers the bounds checking for right col and top row
			while (tempNorthEastIndex - 7 > 0 && tempNorthEastIndex - 7 != 56 && tempNorthEastIndex - 7 != 48 && tempNorthEastIndex - 7 != 40 && tempNorthEastIndex - 7 != 32 && tempNorthEastIndex - 7 != 24 && tempNorthEastIndex - 7 != 16 && tempNorthEastIndex - 7 != 8)
			{
				//check for teammate
				if (!findPBoardElement(tempNorthEastIndex - 7).isWhite && findPBoardElement(tempNorthEastIndex - 7).index != -1)
				{
					break;
				}

				//check for not teammate or empty
				if (findPBoardElement(tempNorthEastIndex - 7).isWhite || m_board.board[tempNorthEastIndex - 7] == 'E')
				{

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::BISHOP)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempNorthEastIndex - 7); //match
							tempNorthEastIndex = tempNorthEastIndex + 7; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::QUEEN)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempNorthEastIndex - 7); //match
							tempNorthEastIndex = tempNorthEastIndex + 7; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::PAWN)
					{
						break;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::KNIGHT)
					{
						break;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::ROOK)
					{
						break;
					}

					if (findPBoardElement(tempNorthEastIndex - 7).pieceType == piece::KING)
					{
						break;
					}
				}
				tempNorthEastIndex = tempNorthEastIndex - 7;
				tilesToAdd++;
			}
		}

		//Black SW 
		int tempSouthWestIndex = pBoardIndex;
		tilesToAdd = 1;
		int pawnCheck = tempSouthWestIndex + 7;
		if (tempSouthWestIndex + 7 < 64)
		{
			//covers the bounds checking for left col and bottom row
			while (tempSouthWestIndex + 7 < 64 && tempSouthWestIndex + 7 != 63 && tempSouthWestIndex + 7 != 55 && tempSouthWestIndex + 7 != 47 && tempSouthWestIndex + 7 != 39 && tempSouthWestIndex + 7 != 31 && tempSouthWestIndex + 7 != 23 && tempSouthWestIndex + 7 != 15 && tempSouthWestIndex + 7 != 7)
			{
				if (findPBoardElement(pawnCheck).isWhite && findPBoardElement(pawnCheck).index != -1 && findPBoardElement(pawnCheck).pieceType == piece::PAWN)
				{
					m_dangerTiles.push_back(pawnCheck);
					return true;
				}

				//check for teammate
				if (!findPBoardElement(tempSouthWestIndex + 7).isWhite && findPBoardElement(tempSouthWestIndex + 7).index != -1)
				{
					break;
				}

				//check for not teammate or empty
				if (findPBoardElement(tempSouthWestIndex + 7).isWhite || m_board.board[tempSouthWestIndex + 7] == 'E')
				{

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::BISHOP)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempSouthWestIndex + 7); //match
							tempSouthWestIndex = tempSouthWestIndex - 7; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::QUEEN)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempSouthWestIndex + 7); //match
							tempSouthWestIndex = tempSouthWestIndex - 7; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::PAWN)
					{
						break;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::KNIGHT)
					{
						break;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::ROOK)
					{
						break;
					}

					if (findPBoardElement(tempSouthWestIndex + 7).pieceType == piece::KING)
					{
						break;
					}
				}
				tempSouthWestIndex = tempSouthWestIndex + 7;
				tilesToAdd++;
			}
		}

		//Black SE
		int tempSouthEastIndex = pBoardIndex;
		tilesToAdd = 1;
		pawnCheck = tempSouthEastIndex + 9;
		if (tempSouthEastIndex + 9 < 64)
		{
			//covers the bounds checking for right col and bottom row
			while (tempSouthEastIndex + 9 < 64 && tempSouthEastIndex + 9 != 56 && tempSouthEastIndex + 9 != 48 && tempSouthEastIndex + 9 != 40 && tempSouthEastIndex + 9 != 32 && tempSouthEastIndex + 9 != 24 && tempSouthEastIndex + 9 != 16)
			{
				if (findPBoardElement(pawnCheck).isWhite && findPBoardElement(pawnCheck).index != -1 && findPBoardElement(pawnCheck).pieceType == piece::PAWN)
				{
					m_dangerTiles.push_back(pawnCheck);
					return true;
				}

				//check for teammate
				if (!findPBoardElement(tempSouthEastIndex + 9).isWhite && findPBoardElement(tempSouthEastIndex + 9).index != -1)
				{
					break;
				}

				//check for not teammate or empty
				if (findPBoardElement(tempSouthEastIndex + 9).isWhite || m_board.board[tempSouthEastIndex + 9] == 'E')
				{

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::BISHOP)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempSouthEastIndex + 9); //match
							tempSouthEastIndex = tempSouthEastIndex - 9; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::QUEEN)
					{
						for (int i = 0; i < tilesToAdd; i++)
						{
							m_dangerTiles.push_back(tempSouthEastIndex + 9); //match
							tempSouthEastIndex = tempSouthEastIndex - 9; //opposite
						}
						return true;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::PAWN)
					{
						break;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::KNIGHT)
					{
						break;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::ROOK)
					{
						break;
					}

					if (findPBoardElement(tempSouthEastIndex + 9).pieceType == piece::KING)
					{
						break;
					}
				}
				tempSouthEastIndex = tempSouthEastIndex + 9;
				tilesToAdd++;
			}
		}

		//Black Knight has special section
		int tempKnightIndex = pBoardIndex;
		if (tempKnightIndex + 17 < 64)
		{
			if (findPBoardElement(tempKnightIndex + 17).isWhite && findPBoardElement(tempKnightIndex + 17).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex + 17);
				return true;
			}
		}

		if (tempKnightIndex + 10 < 64)
		{
			if (findPBoardElement(tempKnightIndex + 10).isWhite && findPBoardElement(tempKnightIndex + 10).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex + 10);
				return true;
			}
		}

		if (tempKnightIndex + 15 < 64)
		{
			if (findPBoardElement(tempKnightIndex + 15).isWhite && findPBoardElement(tempKnightIndex + 15).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex + 15);
				return true;
			}
		}

		if (tempKnightIndex + 6 < 64)
		{
			if (findPBoardElement(tempKnightIndex + 6).isWhite && findPBoardElement(tempKnightIndex + 6).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex + 6);
				return true;
			}
		}

		if (tempKnightIndex - 17 >= 0)
		{
			if (findPBoardElement(tempKnightIndex - 17).isWhite && findPBoardElement(tempKnightIndex - 17).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex - 17);
				return true;
			}
		}

		if (tempKnightIndex - 10 >= 0)
		{
			if (findPBoardElement(tempKnightIndex - 10).isWhite && findPBoardElement(tempKnightIndex - 10).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex - 10);
				return true;
			}
		}

		if (tempKnightIndex - 15 >= 0)
		{
			if (findPBoardElement(tempKnightIndex - 15).isWhite && findPBoardElement(tempKnightIndex - 15).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex - 15);
				return true;
			}
		}

		if (tempKnightIndex - 6 >= 0)
		{
			if (findPBoardElement(tempKnightIndex - 6).isWhite && findPBoardElement(tempKnightIndex - 6).pieceType == piece::KNIGHT)
			{
				m_dangerTiles.push_back(tempKnightIndex - 6);
				return true;
			}
		}
		return false;
	}
}
