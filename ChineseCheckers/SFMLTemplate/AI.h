#pragma once
#include <SFML\Graphics.hpp>
#include "HexTile.h"
#include "GamePiece.h"
#include <iostream>
#include <algorithm>

class AI
{
public:
	AI();
	~AI();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	float minimax(HexTile* node, int depth, bool maximizingPlayer, float alpha, float beta);

	int screenWidth;
	int screenHeigth;

	std::vector<GamePiece> m_marbles; // collection of AI's marble pieces
	std::vector<GamePiece> m_oppositionMarbles; // collection of oppositions marble pieces
	static HexTile* goalNode; // the position of the furthest away opposition home node
	GamePiece* pieceToMove;
	GamePiece* positionToMoveTo;
};
