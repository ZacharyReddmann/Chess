#include "Movement.h"
#include "GamePiece.h"


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
		return -900; //REMOVE LATER POSSIBLY
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
	if (findPBoardElement(start).pieceType == piece::PAWN)
	{
		if(pawnMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			if (promotion(start)) 
			{
				m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			}
			return true;
		}
		return false;
	}
	else if (findPBoardElement(start).pieceType == piece::ROOK)
	{
		if (rookMove(start, end)) 
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			return true;
		}
		return false;
	}
	else if (findPBoardElement(start).pieceType == piece::KNIGHT)
	{
		if (knightMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			return true;
		}
		return false;
	}
	else if (findPBoardElement(start).pieceType == piece::BISHOP)
	{
		if (bishopMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			return true;
		}
		return false;
	}
	else if (findPBoardElement(start).pieceType == piece::QUEEN)
	{
		if (queenMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			return true;
		}
		return false;
	}
	else if (findPBoardElement(start).pieceType == piece::KING)
	{
		if (kingMove(start, end))
		{
			m_board.updateBoard(getPBoardIndexofElement(start), start, getPBoardIndexofElement(end), end);
			return true;
		}
		return false;
	}
	else
		return false;
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

	if (!isCheck())
	{
		if (pieceToMove.isWhite)
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

		}

		//black piece logic
		else
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
		}
	}
	return false;
}


bool Movement::knightMove(int start, int end)
{
	GamePiece pieceToMove = findPBoardElement(start); 
	char endTile = m_board.board[end];
	GamePiece pieceToTake = findPBoardElement(end);

	//Named for white, use opposite for black
	int vMovementOffsetLeft = 17;
	int vMovementOffsetRight = 15;
	int hMovementOffsetRight = 6;
	int hMovementOffsetLeft = 10;

	if(!isCheck())
	{	
		if (endTile == 'E' || pieceToTake.isWhite != pieceToMove.isWhite)
		{
			//Vertical L Move
			if (pieceToMove.index - vMovementOffsetLeft == end)
				return true;
					
			if (pieceToMove.index - vMovementOffsetRight == end)
				return true;

			if (pieceToMove.index + vMovementOffsetLeft == end)
				return true;

			if (pieceToMove.index + vMovementOffsetRight == end)
				return true;

			//Horizontal L Move
			if (pieceToMove.index - hMovementOffsetLeft == end)
				return true;
					
			if (pieceToMove.index - hMovementOffsetRight == end)
				return true;
					
			if (pieceToMove.index + hMovementOffsetLeft == end)
				return true;
					
			if (pieceToMove.index + hMovementOffsetRight == end)
				return true;
		}
	}
	return false;
}

bool Movement::bishopMove(int start, int end)
{
	GamePiece pieceToMove = findPBoardElement(start);
	char endTile = m_board.board[end];
	GamePiece pieceToTake = findPBoardElement(end);

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

	if (!isCheck()) 
	{
		if (endTile == 'E' || pieceToTake.isWhite != pieceToMove.isWhite) 
		{
			if (chooseNine) 
			{
				//SE
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

				//NW
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
			
			if (chooseSeven) 
			{
				//SW
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

				//NE
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
		return false;
	}
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

	if (!isCheck())
	{
		if (endTile == 'E' || pieceToTake.isWhite != pieceToMove.isWhite)
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
	}

	if (emptyHorizontal || emptyVertical)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Movement::queenMove(int start, int end) 
{
	GamePiece pieceToMove = findPBoardElement(start);

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
		if(rookMove(start, end))
		{
			return true;
		}
	}
	return false;
}

bool Movement::kingMove(int start, int end)
{
	//Add castle
	// King side castling - king goes two spaces to E and rook goes two spaces to W
	// Queen side castling - King goes two spaces to W and rook goes three spaces to E
	// make sure to manually update rook old tile to Empty
	// Castle requirements: 
	// king has not moved && chosen rook has not moved, empty tiles between king and rook, king is not in check,
	// the king must not pass through a square that is under attack and the king must not end up in check
	//NW decr by 9
	//N decr by 8
	//NE decr by 7
	//W decr by 1
	//E incr by 1
	//SW incr by 7
	//S incr by 8
	//SE incr by 9
	int startIndex = 0;
	int endIndex = 0;
	return false;
}

bool Movement::isCheck() 
{
	return false;
}

//From king to piece