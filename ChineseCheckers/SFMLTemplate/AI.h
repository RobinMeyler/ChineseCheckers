#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "HexTile.h"
#include "GamePiece.h"
#include "GamePieceMove.h"

class AI
{
public:
	AI();
	~AI();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	HexTile* minimax(std::vector<GamePiece> t_GamePiecesAi, std::vector<GamePiece> t_GamePiecesPlayer, HexTile* node, int depth, bool maximizingPlayer, std::vector<HexTile*> t_copyOfAllTiles);
	GamePieceMove max(std::vector<GamePiece> t_GamePiecesAi, int depth, std::vector<GamePiece> t_GamePiecesPlayer, std::vector<HexTile*> t_copyOfAllTiles); //returns move with highest benifit to AI
	GamePieceMove min(std::vector<GamePiece> t_GamePiecesAi, int depth, std::vector<GamePiece> t_GamePiecesPlayer, std::vector<HexTile*> t_copyOfAllTiles); //returns move with highest benefit to Player
	void makeMove(GamePieceMove move, std::vector<HexTile*> t_copyOfAllTiles, std::vector<GamePiece> moveablePieces);
	std::vector<HexTile*> getCopyOfMapTiles(std::vector<HexTile*> mapToCopy);
	std::vector<GamePiece> getCopyOfGamePiecesOnCopiedMap(std::vector<HexTile*> map, std::vector<GamePiece> pieces);


	int screenWidth;
	int screenHeigth;

	std::vector<GamePiece> m_marbles; // collection of AI's marble pieces
	std::vector<GamePiece> m_oppositionMarbles; // collection of oppositions marble pieces
	static HexTile* goalNode; // the position of the furthest away opposition home node
	GamePieceMove mostIdealMove;
	GamePieceMove bestMove;


	std::vector<std::vector<HexTile*>> everyMapCopy;
};
