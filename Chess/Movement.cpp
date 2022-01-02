#include "Movement.h"
#include "GamePiece.h"

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
}

bool Movement::isValidMove() 
{
	//check if that type of piece can actually move to that tile
	//check if king will be in danger
	return true;
}

std::tuple<int, int> Movement::getUserInput()
{
	std::string userInput;
	while (!isValidMove())
	{
		std::cout << "Please input the desired piece to move (ex. A2) : " << std::endl;
		std::cin >> userInput;
	}
	int startIndex = convertUserInput(userInput);
	while (!isValidMove())
	{
		std::cout << "Please input the desired location to move your piece: " << std::endl;
		std::cin >> userInput;
	}
	int endIndex = convertUserInput(userInput);
	return std::make_tuple(startIndex, endIndex);
}

bool Movement::pawnMove()
{
	//m_board
	int startIndex = 0;
	int endIndex = 0;
	//if()
	return false;
}

bool Movement::knightMove()
{
	int startIndex = 0;
	int endIndex = 0;
	//index starting at 18, needs to get to 1 & 3, 33 & 35, &&  8 & 12, 24 & 28
	//index starting at 20, needs to get to 3 & 5, 35 & 37, && 10 & 14, 26 & 30

	//Vertical L Move 
	//desiredLocation == startIndex - 17
	//desiredLocation == startIndex - 15 
	//desiredLocation == startIndex + 15
	//desiredLocation == startIndex + 17
	
	//Horizontal L Move
	//desired Location == startIndex - 10
	//desired Location == startIndex - 6
	//desired Location == startIndex + 10
	//desired Location == startIndex + 6
	return false;
}

bool Movement::bishopMove()
{
	int startIndex = 0;
	int endIndex = 0;
	//index starting at 27 can go to:  (max is 7 tiles from corner to corner)
	//NW (18, 9, 0) decr by 9
	//NE (20, 13, 6) decr by 7
	//SW (34, 41, 48) inc by 7
	//SE (36, 45, 54, 63) inc by 9
	return false;

}

bool Movement::rookMove()
{
	int startIndex = 0;
	int endIndex = 0;
	//index starting at 0 can go to: (max is 7 tiles from corner to corner)
	//S (8, 16, 24, 32, 40, 48, 56) incr by 8
	//N decr by 8
	//E incr by 1
	//W decr by 1
	return false;

}

bool Movement::queenMove()
{
	int startIndex = 0;
	int endIndex = 0;
	//combine rook and bishop move?
	return false;

}

bool Movement::kingMove()
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

void Movement::promotion()
{
	//if (piecetype == 'p' && on index 0, 1, 2, 3, 4, 5, 6, 7, 56, 57, 58, 59, 60, 61, 62, 63)
	//{
	//	
	//}
}

