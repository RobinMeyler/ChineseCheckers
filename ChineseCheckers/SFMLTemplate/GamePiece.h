#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "HexTile.h"


class GamePiece
{

public:
	GamePiece();

	sf::CircleShape m_circle;
	HexTile* tile;
	bool isBluePiece;
};

