
// Author: Robin Meyler, Josh Browne

#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>
#include "Player.h"
#include "AI.h"
#include "HexGrid.h"
#include "MyVector3.h"
#include "Enum.h"

enum class Players {
	PlayerOne,
	PlayerTwo
};

enum class Phase {
	SelectingPieceToMove,
	Evaluating,
	SelectingTileToMoveTo,
	Moving
};

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	static Players m_players;
	Phase m_gamePhase;

private:

	void processEvents();				// Loop functions
	void update(sf::Time t_deltaTime);
	void render();
	sf::Event event;
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // control exiting game
	
	//Player m_player;
	//NPC m_npc;

	// Robin
	sf::Vector2i m_mousePosition;
	bool m_leftMousePressed;
	bool m_rightPressed;

	HexTile* m_pressedToPlayTile;
	HexTile* m_pressedToMoveToTile;
	GamePiece* m_pieceInPlay;
	


	std::vector<HexTile*>* m_tilesPtr;
	HexGrid m_HexGridCenter;
	std::vector<HexGrid*> m_HexGridTriangleWedges;
	std::vector<HexTile*> m_blueFinishSpots;
	std::vector<HexTile*> m_redFinishSpots;
	std::vector<HexTile*> m_allTiles;

	void checkHops(sf::Vector3i t_direction, HexTile* t_followTile);
	void runEvaluation();
	int findAxisdiff(HexTile* one, HexTile* two);
	void checkForWin();
	void runPlayerStates();
	void runAIStates();
	void checkIfGamePiece();
	void evaluatePossibleMoves();
	void checkIfMoveAllowed();
	void moveGamePiece();
	bool m_gameFinished;
	sf::Text m_gameText;
	sf::Font m_font;
	Player m_player;
	AI m_AI;
};

#endif // !GAME

