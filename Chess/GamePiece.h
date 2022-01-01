#pragma once
#include <string>


enum piece {
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
	PAWN,
	EMPTY
};

class GamePiece
{
	public:
		GamePiece(piece pType, bool hasMoved, bool hasDoubleMoved) 
		{
			pieceType = pType;
			this->hasMoved = hasMoved;
			this->hasDoubleMoved = hasDoubleMoved;
		}
		piece pieceType;
		bool hasMoved;
		bool hasDoubleMoved;
};
