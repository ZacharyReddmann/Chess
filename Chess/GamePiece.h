#pragma once
#include <string>
#include <unordered_map>

enum piece {
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
	PAWN,
	EMPTY
};

inline std::unordered_map<char, piece> g_pieceMapConverter
{
	{'R', piece::ROOK},
	{'N', piece::KNIGHT},
	{'B', piece::BISHOP},
	{'Q', piece::QUEEN},
	{'K', piece::KING},
	{'P', piece::PAWN},
	{'E', piece::EMPTY}
};

class GamePiece
{
	public:
		GamePiece() = default;
		GamePiece(piece pType, bool hasMoved, bool hasDoubleMoved, bool isWhite, int index):
			pieceType(pType), 
			hasMoved(hasMoved), 
			hasDoubleMoved(hasDoubleMoved), 
			isWhite(isWhite),
			index(index) {}
		piece pieceType;
		bool hasMoved;
		bool hasDoubleMoved;
		bool isWhite;
		int index;
};
