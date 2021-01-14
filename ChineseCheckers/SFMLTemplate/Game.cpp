#include "Game.h"


Players Game::m_players{ Players::PlayerOne };

Game::Game() :
	m_window{ sf::VideoMode{ 1420, 1080, 32 }, "Game Screen" },
	m_exitGame{ false },
	m_HexGridCenter(30, sf::Vector2f(710, 540), GridOrientation::Pointy, GridType::Hexagon, 4, 0, sf::Vector3i(0,0,0), Config::one)
{
	// Have grid
	m_tilesPtr = m_HexGridCenter.getGrid();
	float rot;

	std::vector<sf::Vector3i> startCoords;

	startCoords.push_back(sf::Vector3i(-1, 5, -4));

	startCoords.push_back(sf::Vector3i(-5, 4, 1));

	startCoords.push_back(sf::Vector3i(-4, -1, 5));

	startCoords.push_back(sf::Vector3i(1, -5, 4));

	startCoords.push_back(sf::Vector3i(5, -4, -1));

	startCoords.push_back(sf::Vector3i(4, 1, -5));

	



	for (int i = 0; i < 6; i++)
	{
		//find correct location to place wedges

		MyVector3 startingPos;
		if (i == 3)
		{
			rot = 65.f;
		}
	
		float rotateAngleRadians = (60 * (i + 1)) * 3.14159265 / 180;
		startingPos.x = cos(rotateAngleRadians);
		startingPos.y = sin(rotateAngleRadians);
		startingPos.normalise();
		startingPos.x *= 260; // ????
		startingPos.y *= 260;

		
		// Decide start of triangle coords
		Config con = Config::one;
		if (i == 1 || i == 4)
		{
			con = Config::two;
		}
		else if (i == 2 || i == 5)
		{
			con = Config::three;
		}

		HexGrid* p_HexGrid = new HexGrid(30, startingPos + sf::Vector2f(710, 540), GridOrientation::Pointy, GridType::Triangle, 3, (60 * i) -180, startCoords[i], con);
		p_HexGrid->correct();
		m_HexGridTriangleWedges.push_back(p_HexGrid);
	}

	for(auto & tile : m_HexGridCenter.m_gridHexTiles)
	{
		m_allTiles.push_back(tile);
	}
	for (auto& grid : m_HexGridTriangleWedges)
	{
		for (auto& tile : grid->m_gridHexTiles)
		{
			m_allTiles.push_back(tile);
		}
	}

	for (auto& tile : m_allTiles)
	{
		for (sf::Vector3i direction : tile->hex_directions)
		{
			sf::Vector3i newCoords = tile->m_gridCoordinates3axis + direction;
			for (HexTile* hex : m_allTiles)
			{
				if (hex->m_gridCoordinates3axis == newCoords)
				{
					tile->setNeighbour(hex);
					break;
				}
			}
		}
	}


	for (auto tile : m_allTiles)
	{
		std::cout << "New Set Tile: X: " << tile->m_gridCoordinates3axis.x << " Y: " << tile->m_gridCoordinates3axis.y << " Z: " << tile->m_gridCoordinates3axis.z << std::endl;
		for (HexTile* neigh : tile->m_neighbours)
		{
			std::cout << "Neighbour X: " << neigh->m_gridCoordinates3axis.x << " Y: " << neigh->m_gridCoordinates3axis.y << " Z: " << neigh->m_gridCoordinates3axis.z << std::endl;
		}
	}
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










	//m_player.render(m_window);
	//m_npc.render(m_window);
	m_HexGridCenter.render(&m_window);
	for (int i = 0; i < m_HexGridTriangleWedges.size(); i++)
	{
		m_HexGridTriangleWedges.at(i)->render(&m_window);
	}
	m_window.display();
}

