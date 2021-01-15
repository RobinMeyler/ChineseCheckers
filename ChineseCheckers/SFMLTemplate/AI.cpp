#include "AI.h"

AI::AI()
{

	int oop = 60;
	for (int i = 0; i < 10; i++)
	{
		GamePiece marble;
		marble.m_circle.setFillColor(sf::Color::Red);
		marble.m_circle.setRadius(30 / 1.25f);
		marble.m_circle.setOrigin(14, 14);
		marble.m_circle.setPosition(oop, 60);
		oop += 60;
		m_marbles.push_back(marble);
	}
	
}

AI::~AI()
{
}

void AI::update(sf::Time t_deltaTime)
{

}

void AI::render(sf::RenderWindow& t_window)
{
	for (auto& marble : m_marbles)
	{
		t_window.draw(marble.m_circle);
	}
}

HexTile* AI::minimax(std::vector<GamePiece> t_GamePiecesAi, std::vector<GamePiece> t_GamePiecesPlayer, HexTile* node, int depth, bool maximizingPlayer, std::vector<HexTile*> t_copyOfAllTiles)
{
	HexTile* bestValue = new HexTile(sf::Vector3i(0, 0, 0));
	bestValue->m_AiScoreValueMinMax = -1000000;// start with low value, for checks, we want highest val
	if (depth == 0)//if depth = 0 or node is a terminal node then
	{
		return node;
	}

	
	if (maximizingPlayer) {
		// find best move
		GamePieceMove* aiMove = max(t_GamePiecesAi, depth, t_GamePiecesPlayer, t_copyOfAllTiles);
		//make move on new copy of gameboard
		std::vector<HexTile*> t_NewCopyOfAllTiles = getCopyOfMapTiles(t_copyOfAllTiles); // make copy
		std::vector<GamePiece> newCopyOfGamePiecesAI = getCopyOfGamePiecesOnCopiedMap(t_NewCopyOfAllTiles, t_GamePiecesAi);
		std::vector<GamePiece> newCopyOfGamePiecesPlayer = getCopyOfGamePiecesOnCopiedMap(t_NewCopyOfAllTiles, t_GamePiecesPlayer);

		makeMove(aiMove, t_NewCopyOfAllTiles, newCopyOfGamePiecesAI);

		// call minimax using updated pieces
		HexTile* value = minimax(newCopyOfGamePiecesAI, newCopyOfGamePiecesPlayer, node, depth - 1, false, t_NewCopyOfAllTiles);
		
		if (bestValue->m_AiScoreValueMinMax < value->m_AiScoreValueMinMax) //bestValue = std::max(bestValue, value->m_AiScoreValueMinMax);
			bestValue = value;
	}
	else {// (minimizing player)
		GamePieceMove* playerMove = min(t_GamePiecesAi, depth, t_GamePiecesPlayer, t_copyOfAllTiles);
		//make move on new copy of gameboard
		std::vector<HexTile*> t_NewCopyOfAllTiles = getCopyOfMapTiles(t_copyOfAllTiles); // make copy
		std::vector<GamePiece> newCopyOfGamePiecesAI = getCopyOfGamePiecesOnCopiedMap(t_NewCopyOfAllTiles, t_GamePiecesAi);
		std::vector<GamePiece> newCopyOfGamePiecesPlayer = getCopyOfGamePiecesOnCopiedMap(t_NewCopyOfAllTiles, t_GamePiecesPlayer);

		makeMove(playerMove, t_NewCopyOfAllTiles, newCopyOfGamePiecesPlayer);

		// call minimax using updated pieces
		HexTile* value = minimax(newCopyOfGamePiecesAI, newCopyOfGamePiecesPlayer, node, depth - 1, true, t_NewCopyOfAllTiles);

		if (bestValue->m_AiScoreValueMinMax > value->m_AiScoreValueMinMax) //bestValue = std::max(bestValue, value->m_AiScoreValueMinMax);
			bestValue = value;

	}

	return bestValue;
}

//returns move with highest benifit to AI
GamePieceMove* AI::max(std::vector<GamePiece> t_GamePiecesAi, int depth, std::vector<GamePiece> t_GamePiecesPlayer, std::vector<HexTile*> t_copyOfAllTiles)
{
	GamePieceMove* bestMove = new GamePieceMove();
	bestMove->moveScore = -std::numeric_limits<float>::max();
	//bestValue->m_AiScoreValueMinMax = -std::numeric_limits<float>::max();
	for (int i = 0; i < t_GamePiecesAi.size(); i++) // loop through each AI gamePiece
	{
		for (int n = 0; n < t_GamePiecesAi.at(i).tile->getPossibleMovesFromThisTile().size(); n++) // loop through each possible move for that piece
		{
			if (bestMove->moveScore < t_GamePiecesAi.at(i).tile->getPossibleMovesFromThisTile().at(n)->m_AiScoreValueMinMax) //check each move and set best move based on heuristic
			{
				bestMove->piece = &t_GamePiecesAi.at(i); // set the best moves piece
				bestMove->piece->tile = t_GamePiecesAi.at(i).tile;
				bestMove->tileToMoveTo = t_GamePiecesAi.at(i).tile->getPossibleMovesFromThisTile().at(n); // set the tileToMoveTo
				bestMove->moveScore = t_GamePiecesAi.at(i).tile->getPossibleMovesFromThisTile().at(n)->m_AiScoreValueMinMax;
			}
		}
	}
	mostIdealMove = *bestMove;//??????????????
	return bestMove;
}

//returns move with highest benefit to Player
GamePieceMove* AI::min(std::vector<GamePiece> t_GamePiecesAi, int depth, std::vector<GamePiece> t_GamePiecesPlayer, std::vector<HexTile*> t_copyOfAllTiles)
{
	GamePieceMove* bestMove = new GamePieceMove();
	bestMove->moveScore = std::numeric_limits<float>::max();
	//bestValue->m_AiScoreValueMinMax = -std::numeric_limits<float>::max();
	for (int i = 0; i < t_GamePiecesPlayer.size(); i++) // loop through each AI gamePiece
	{
		for (int n = 0; n < t_GamePiecesPlayer.at(i).tile->getPossibleMovesFromThisTile().size(); n++) // loop through each possible move for that piece
		{
			if (bestMove->moveScore > t_GamePiecesPlayer.at(i).tile->getPossibleMovesFromThisTile().at(n)->m_AiScoreValueMinMax) //check each move and set best move based on heuristic
			{
				bestMove->piece = &t_GamePiecesPlayer.at(i); // set the best moves piece
				bestMove->piece->tile = t_GamePiecesAi.at(i).tile;
				bestMove->tileToMoveTo = t_GamePiecesPlayer.at(i).tile->getPossibleMovesFromThisTile().at(n); // set the tileToMoveTo
				bestMove->moveScore = t_GamePiecesPlayer.at(i).tile->getPossibleMovesFromThisTile().at(n)->m_AiScoreValueMinMax;
			}
		}
	}
	return bestMove;
}

void AI::makeMove(GamePieceMove* move, std::vector<HexTile*> t_copyOfAllTiles, std::vector<GamePiece> moveablePieces)
{
	GamePiece* copyPieceToMove = nullptr;
	HexTile* copyTileToMoveTo = nullptr;
	for (auto piece : moveablePieces)
	{
		if (piece.tile->m_gridCoordinates3axis == move->piece->tile->m_gridCoordinates3axis)
		{
			copyPieceToMove = &piece;
			break;
		}
	}
	for (auto tile : t_copyOfAllTiles)
	{
		if (tile->m_gridCoordinates3axis == move->tileToMoveTo->m_gridCoordinates3axis)
		{
			copyTileToMoveTo = tile;
			break;
		}
	}

	if (copyPieceToMove != nullptr && copyTileToMoveTo != nullptr)
	{
		copyPieceToMove->tile->isOccupied = false;
		copyPieceToMove->tile = copyTileToMoveTo;
		copyPieceToMove->m_circle.setPosition(copyPieceToMove->tile->m_position);
		copyPieceToMove->tile->isOccupied = true;
	}
}

std::vector<HexTile*> AI::getCopyOfMapTiles(std::vector<HexTile*> mapToCopy)
{
	std::vector<HexTile*> t_NewCopyOfAllTiles;

	for (auto tile : mapToCopy)
	{
		HexTile* copyTile = new HexTile(*tile);
		t_NewCopyOfAllTiles.push_back(copyTile);
	}
	for (auto tile : t_NewCopyOfAllTiles)
	{
		for (auto oldtile : mapToCopy)
		{
			if (oldtile->m_gridCoordinates3axis == tile->m_gridCoordinates3axis)
			{
				tile->copyNeighbours(oldtile->m_neighbours, t_NewCopyOfAllTiles);
			}
		}
	}

	return t_NewCopyOfAllTiles;
}

std::vector<GamePiece> AI::getCopyOfGamePiecesOnCopiedMap(std::vector<HexTile*> map, std::vector<GamePiece> pieces)
{
	std::vector<GamePiece> newPieces; // the copied pieces, on new map
	for (auto piece : pieces)
	{
		for (auto tile : map)
		{
			if (piece.tile->m_gridCoordinates3axis == tile->m_gridCoordinates3axis) // find piece on new map
			{
				GamePiece pieceCopy;
				pieceCopy.tile = new HexTile(*piece.tile);
				pieceCopy.m_circle = *new sf::CircleShape(pieceCopy.tile->circle);
				newPieces.push_back(pieceCopy);
			}
		}
	}

	return newPieces;
}
