#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "HexTile.h"
#include "GamePiece.h"


class GamePieceMove
{

public:
	GamePieceMove() {};

	GamePiece piece;         // The piece we want to move
	HexTile* tileToMoveTo;	  // Where we want to move it
	int moveScore;            // The score of this move
};