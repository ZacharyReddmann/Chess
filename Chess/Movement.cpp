#include "Movement.h"
#include "GamePiece.h"
#include "GameBoard.h"

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
	if (m_board.pieceBoard[start].pieceType == piece::PAWN)
	{
		if(pawnMove(start, end))
		{
			m_board.updateBoard(start, end);
			if (promotion(start, end)) 
			{
				m_board.updateBoard(start, end);
			}
			return true;
		}
		return false;
	}
	else if (m_board.pieceBoard[start].pieceType == piece::ROOK)
	{
		if (rookMove(start, end)) 
		{
			m_board.updateBoard(start, end);
			return true;
		}
		return false;
	}
	else if (m_board.pieceBoard[start].pieceType == piece::KNIGHT)
	{
		if (knightMove(start, end))
		{
			m_board.updateBoard(start, end);
			return true;
		}
		return false;
	}
	else if (m_board.pieceBoard[start].pieceType == piece::BISHOP)
	{
		if (bishopMove(start, end))
		{
			m_board.updateBoard(start, end);
			return true;
		}
		return false;
	}
	else if (m_board.pieceBoard[start].pieceType == piece::QUEEN)
	{
		if (queenMove(start, end))
		{
			m_board.updateBoard(start, end);
			return true;
		}
		return false;
	}
	else if (m_board.pieceBoard[start].pieceType == piece::KING)
	{
		if (kingMove(start, end))
		{
			m_board.updateBoard(start, end);
			return true;
		}
		return false;
	}
	else
		return false;
}

/*bool Movement::enPassant(int start, int end)
{

}*/


bool Movement::promotion(int start, int end)
{
	if ((m_board.pieceBoard[start].pieceType == piece::PAWN && m_board.pieceBoard[start].index < 8) ||
		(m_board.pieceBoard[start].pieceType == piece::PAWN && m_board.pieceBoard[start].index < 64))
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
			m_board.pieceBoard[start].pieceType = piece::QUEEN;
			return true;
		}
		else if (userInput == "ROOK")
		{
			m_board.pieceBoard[start].pieceType = piece::ROOK;
			return true;
		}
		else if (userInput == "KNIGHT")
		{
			m_board.pieceBoard[start].pieceType = piece::KNIGHT;
			return true;
		}
		else if (userInput == "BISHOP")
		{
			m_board.pieceBoard[start].pieceType = piece::BISHOP;
			return true;
		}
	}
	return false;
}

bool Movement::pawnMove(int start, int end)
{
	//Moving one space forward - Checking for correct tile & empty tile, wont place your king in check
	if (((((m_board.pieceBoard[start].index + 8) == m_board.pieceBoard[end].index) && (m_board.pieceBoard[end].pieceType == piece::EMPTY)) ||
		(((m_board.pieceBoard[start].index - 8) == m_board.pieceBoard[end].index) && (m_board.pieceBoard[end].pieceType == piece::EMPTY))) &&
		(isCheck() == false))
	{
		return true;
	}

	//Taking enemy piece - Checking for correct tile & tile is an enemy piece, wont place your king in check
	else if (((((m_board.pieceBoard[start].index + 7) == m_board.pieceBoard[end].index) && (m_board.pieceBoard[end].isWhite != m_board.pieceBoard[start].isWhite)) ||
		(((m_board.pieceBoard[start].index - 7) == m_board.pieceBoard[end].index) && (m_board.pieceBoard[end].isWhite != m_board.pieceBoard[start].isWhite)) ||
		(((m_board.pieceBoard[start].index + 9) == m_board.pieceBoard[end].index) && (m_board.pieceBoard[end].isWhite != m_board.pieceBoard[start].isWhite)) ||
		(((m_board.pieceBoard[start].index - 9) == m_board.pieceBoard[end].index) && (m_board.pieceBoard[end].isWhite != m_board.pieceBoard[start].isWhite)) &&
		(isCheck() == false)))
	{
		return true;
	}

	//Double move - Checking for correct tile, both tiles in front are empty, pawn hasnt moved yet, wont place your king in check
	else if (((m_board.pieceBoard[start].index + 16) == m_board.pieceBoard[end].index) &&
		(m_board.pieceBoard[start + 8].pieceType == piece::EMPTY) &&
		(m_board.pieceBoard[end].pieceType == piece::EMPTY) &&
		(m_board.pieceBoard[start].hasMoved == false) && (isCheck() == false))
	{
		return true;
	}

	/*En Passant, first black taking whiteand then white taking black - checks for starting pawn color, pawn is in correct tile row,
	  other pawn is enemy and has double moved, correct end tile, and wont place your king in check*/
	else if (((m_board.pieceBoard[start].isWhite == false) &&
		(m_board.pieceBoard[start].index >= 32 || m_board.pieceBoard[start].index <= 39) &&
		(m_board.pieceBoard[end].isWhite == true && m_board.pieceBoard[end].hasDoubleMoved == true) &&
		((m_board.pieceBoard[end].index == m_board.pieceBoard[start].index + 7) || (m_board.pieceBoard[end].index == m_board.pieceBoard[start].index + 9)) &&
		(isCheck() == false)) || //end of En Passant Black
		((m_board.pieceBoard[start].isWhite == true) &&
		(m_board.pieceBoard[start].index >= 24 || m_board.pieceBoard[start].index <= 31) &&
		(m_board.pieceBoard[end].isWhite == false && m_board.pieceBoard[end].hasDoubleMoved == true) &&
		((m_board.pieceBoard[end].index == m_board.pieceBoard[start].index - 7) || (m_board.pieceBoard[end].index == m_board.pieceBoard[start].index - 9)) &&
		(isCheck() == false))) //end of En Passant White
	{
		return true;
	}
	else
		return false;
}


bool Movement::knightMove(int start, int end)
{
	//Vertical L Move - Checking correct tile, end tile is empty or enemy, and wont place your king in check
	if ((((m_board.pieceBoard[start].index + 17) == m_board.pieceBoard[end].index) ||
		((m_board.pieceBoard[start].index + 15) == m_board.pieceBoard[end].index) ||
		((m_board.pieceBoard[start].index - 17) == m_board.pieceBoard[end].index) ||
		((m_board.pieceBoard[start].index - 15) == m_board.pieceBoard[end].index)) &&
		((m_board.pieceBoard[end].pieceType == piece::EMPTY) || (m_board.pieceBoard[start].isWhite != m_board.pieceBoard[end].isWhite)) &&
		(isCheck() == false))
	{
		return true;
	}
	//Horizontal L Move - Checking correct tile, end tile is empty or enemy, and wont place your king in check
	else if ((((m_board.pieceBoard[start].index + 10) == m_board.pieceBoard[end].index) ||
			((m_board.pieceBoard[start].index + 6) == m_board.pieceBoard[end].index) ||
			((m_board.pieceBoard[start].index - 10) == m_board.pieceBoard[end].index) ||
			((m_board.pieceBoard[start].index - 6) == m_board.pieceBoard[end].index)) &&
			((m_board.pieceBoard[end].pieceType == piece::EMPTY) || (m_board.pieceBoard[start].isWhite != m_board.pieceBoard[end].isWhite)) &&
			(isCheck() == false))
	{
		return true;
	}

	else
		return false;
}

bool Movement::bishopMove(int start, int end)
{
	int tilesToTravelByNine = ((m_board.pieceBoard[end].index - m_board.pieceBoard[start].index) / 9); //should equal 3 27 to 54
	int tilesToTravelBySeven = ((m_board.pieceBoard[end].index - m_board.pieceBoard[start].index) / 7); //should equal 2 27 to 41

	bool chooseNine = false;
	bool chooseSeven = false;

	if (((m_board.pieceBoard[end].index - m_board.pieceBoard[start].index) % 9) == 0)
	{
		chooseNine = true;
	}
	else if (((m_board.pieceBoard[end].index - m_board.pieceBoard[start].index) % 7) == 0)
	{
		chooseSeven = true;
	}


	//index starting at 27 can go to:  (max is 7 tiles from corner to corner) 27 to 54  (27, 36, 45, 54)
	//NW (18, 9, 0) decr by 9
	//NE (20, 13, 6) decr by 7
	//SW (34, 41, 48) inc by 7
	//SE (36, 45, 54, 63) inc by 9

	if (chooseNine)
	{
		for (int i = 0; i < tilesToTravelByNine; i++)
		{

		}
	}
	
	else if (chooseSeven) 
	{
		for (int i = 0; i < tilesToTravelBySeven; i++)
		{


		}
	}
	
	return false;

}

bool Movement::rookMove(int start, int end)
{
	
	//index starting at 0 can go to: (max is 7 tiles from corner to corner)
	//S (8, 16, 24, 32, 40, 48, 56) incr by 8
	//N decr by 8
	//E incr by 1
	//W decr by 1
	return false;

}

bool Movement::queenMove(int start, int end)
{

	//combine rook and bishop move?
	return false;

}

bool Movement::kingMove(int start, int end)
{
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

