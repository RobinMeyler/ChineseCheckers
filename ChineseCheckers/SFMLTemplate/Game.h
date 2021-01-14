#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>
#include "Player.h"
#include "NPC.h"
#include "HexGrid.h"
#include "MyVector3.h"
class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

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
	HexGrid m_HexGridCenter;
	std::vector<HexGrid*> m_HexGridTriangleWedges;
};

#endif // !GAME

