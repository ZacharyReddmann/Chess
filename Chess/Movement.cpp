#include "Movement.h"

int convertUserInput(std::string userInput)
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