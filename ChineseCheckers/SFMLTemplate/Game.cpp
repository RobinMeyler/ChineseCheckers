#include "Game.h"


Players Game::m_players{ Players::PlayerOne };

Game::Game() :
	m_window{ sf::VideoMode{ 1420, 1080, 32 }, "Game Screen" },
	m_exitGame{ false },
	m_HexGridCenter(30, sf::Vector2f(710, 540), GridOrientation::Pointy, GridType::Hexagon, 4)
{
	m_tilesPtr = m_HexGridCenter.getGrid();
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_mousePosition = sf::Mouse::getPosition(m_window);
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_leftPressed = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					m_rightPressed = true;
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				
			}
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{

	if (Game::m_players == Players::PlayerOne)
	{
		// Player
		if (m_gamePhase == Phase::SelectingMarble)
		{
			// Takes input
			if (m_leftPressed == true)
			{
				bool found = false;
				for (HexTile* tile : *m_tilesPtr)
				{
					MyVector3 distance = tile->circle.getPosition() - (sf::Vector2f)m_mousePosition;
					if (distance.length() < tile->circle.getRadius())
					{
						// Collision found
						m_pressedToPlayTile = tile;
						found = true;
						break;
					}
				}

				if (found == true)
				{
					m_gamePhase = Phase::Evaluating;
				}
				m_leftPressed = false;
			}
		}
		if (m_gamePhase == Phase::Evaluating)
		{
			// Game determines which positions are allowed for the player to move
			// Checks each of the players marbles for each of their adjacent places
			// If it is empty, highlight it
			// If it is occupied, check the next slot in that direction, if it is; filled end search, if it is not; highlight it and then check it's neighbours, then repeat
			// Change the circle texture to a different color

			for (auto &neighbours : m_pressedToPlayTile->m_neighbours)
			{
				if (neighbours->isOccupied == false)
				{
					// Highlight, mark
				}
				else 
				{
					// Recursive checks
				}
			}
			m_gamePhase = Phase::SelectingMove;

		}
		else if (m_gamePhase == Phase::SelectingMove)
		{
			// Takes input
			if (m_leftPressed == true)
			{
				// For each Circle do a Circle to point collision check to find which circle is pressed else break
				// determine if the circle is valid
				// begin moving phase
				m_gamePhase = Phase::Moving;
				m_leftPressed = false;
			}
		}
		else if (m_gamePhase == Phase::Moving)
		{
			// Move the Player Texture to the new position over a few frames
		}
	}
	else if (Game::m_players == Players::PlayerTwo)
	{
		// AI ( For now )










	}

	if (m_exitGame)
	{
		m_window.close();		// Exiting the game
	}
	//m_player.update(t_deltaTime);
	//m_npc.update(t_deltaTime);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);





	for (int i = 0; i < 6; i++)
	{
		HexGrid* p_HexGrid = new HexGrid(30, sf::Vector2f(600 + i, 275), GridOrientation::Pointy, GridType::Triangle, 3);
		p_HexGrid->render(&m_window);
	}







	//m_player.render(m_window);
	//m_npc.render(m_window);
	m_HexGridCenter.render(&m_window);
	m_window.display();
}

