#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>
#include "Player.h"
#include "NPC.h"
#include "HexGrid.h"

enum class Players {
	PlayerOne,
	PlayerTwo
};

enum class Phase {
	Evaluating,
	Selecting,
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
	HexGrid m_HexGrid;


	// Robin
	sf::Vector2i m_mousePosition;
	bool m_leftPressed;
	bool m_rightPressed;
};

#endif // !GAME

