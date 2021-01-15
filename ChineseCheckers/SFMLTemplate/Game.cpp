#include "Game.h"


Players Game::m_players{ Players::PlayerOne };

Game::Game() :
	m_window{ sf::VideoMode{ 1420, 1080, 32 }, "Game Screen" },
	m_exitGame{ false },
	m_gamePhase{ Phase::SelectingMarble},
	m_HexGridCenter(30, sf::Vector2f(710, 540), GridOrientation::Pointy, GridType::Hexagon, 4, 0, sf::Vector3i(0,0,0), Config::one)
{
	// Have grid
	m_tilesPtr = m_HexGridCenter.getGrid();

	std::vector<sf::Vector3i> startCoords;
	startCoords.push_back(sf::Vector3i(-1, 5, -4));
	startCoords.push_back(sf::Vector3i(-5, 4, 1));
	startCoords.push_back(sf::Vector3i(-4, -1, 5));
	startCoords.push_back(sf::Vector3i(1, -5, 4));
	startCoords.push_back(sf::Vector3i(5, -4, -1));
	startCoords.push_back(sf::Vector3i(4, 1, -5));
	sf::Color colours[6] = { sf::Color::Red, sf::Color::Green, sf::Color::Yellow, sf::Color::Blue,  sf::Color::Magenta, sf::Color::Cyan };

	for (int i = 0; i < 6; i++)
	{
		//find correct location to place wedges
		MyVector3 startingPos;
	
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
	
		// Player Pieces
		if (i == 0)
		{
			for (int j = 0; j < p_HexGrid->m_gridHexTiles.size(); j++)
			{
				m_player.m_marbles.at(j).m_circle.setPosition(p_HexGrid->m_gridHexTiles.at(j)->m_position);
				m_player.m_marbles.at(j).tile = p_HexGrid->m_gridHexTiles.at(j);
				p_HexGrid->m_gridHexTiles.at(j)->isOccupied = true;
			}
		}

		// AI pieces
		if (i == 3)
		{
			for (int j = 0; j < p_HexGrid->m_gridHexTiles.size(); j++)
			{
				m_AI.m_marbles.at(j).m_circle.setPosition(p_HexGrid->m_gridHexTiles.at(j)->m_position);
				m_AI.m_marbles.at(j).tile = p_HexGrid->m_gridHexTiles.at(j);
				p_HexGrid->m_gridHexTiles.at(j)->isOccupied = true;
			}
		}
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
		if (m_gamePhase == Phase::SelectingMarble)
		{
			if (m_leftPressed == true)
			{
				bool found = false;
				for (auto & piece : m_player.m_marbles)
				{
					MyVector3 distance = piece.m_circle.getPosition() - (sf::Vector2f)m_mousePosition;
					if (distance.length() < 30)
					{
						// Collision found
						m_pressedToPlayTile = piece.tile;
						m_pieceInPlay = &piece;
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
			for (auto &neighbours : m_pressedToPlayTile->m_neighbours)
			{
				if (neighbours->isOccupied == false)
				{
					neighbours->isMarked = true;
					neighbours->circle.setOutlineColor(sf::Color::Green);
				}
				else 
				{
					// Recursive checks
					sf::Vector3i direction = neighbours->m_gridCoordinates3axis - m_pressedToPlayTile->m_gridCoordinates3axis;
					checkHops(direction, neighbours);
				}
			}
			m_gamePhase = Phase::SelectingMove;
		}
		else if (m_gamePhase == Phase::SelectingMove)
		{
			// Takes input
			if (m_leftPressed == true)
			{
				bool found = false;
				for (HexTile* tile : m_allTiles)
				{
					MyVector3 distance = tile->circle.getPosition() - (sf::Vector2f)m_mousePosition;
					if (distance.length() < tile->m_cellSize)
					{
						if (tile->isMarked == true && tile->isOccupied == false)
						{
							found = true;
							m_pressedToMoveToTile = tile;
							break;
						}
					}
				}
				if (found == true)
				{
					m_gamePhase = Phase::Moving;
				}
				else
				{
					m_gamePhase = Phase::SelectingMarble;
				}

				// Reset regardless
				for (HexTile* tile : m_allTiles)
				{
					tile->isMarked = false;
					tile->circle.setOutlineColor(tile->circle.getFillColor());
				}
				
				m_leftPressed = false;
			}
		}
		else if (m_gamePhase == Phase::Moving)
		{
			// Move the Player Texture to the new position over a few frames
			m_pieceInPlay->tile->isOccupied = false;
			m_pieceInPlay->tile = m_pressedToMoveToTile;
			m_pieceInPlay->m_circle.setPosition(m_pressedToMoveToTile->m_position);
			m_pressedToMoveToTile->isOccupied = true;
			m_gamePhase = Phase::SelectingMarble;
			// Swap turn;

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
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_HexGridCenter.render(&m_window);
	for (int i = 0; i < m_HexGridTriangleWedges.size(); i++)
	{
		m_HexGridTriangleWedges.at(i)->render(&m_window);
	}

	m_AI.render(m_window);
	m_player.render(m_window);

	m_window.display();
}

void Game::checkHops(sf::Vector3i t_direction, HexTile* t_followTile)
{
	if (t_followTile->isOccupied == true)		// If it's filled
	{
		t_followTile->isMarked = true;
		sf::Vector3i newCoords = t_followTile->m_gridCoordinates3axis + t_direction;
		for (auto& tile : t_followTile->m_neighbours)
		{
			if (tile->m_gridCoordinates3axis == newCoords)	// If spot at new coords exists
			{
				if (tile->isOccupied == false )				// and is not filled
				{
					checkHops(t_direction, tile);			// Mark and check it
				}
				else
				{
					return;
				}
			}
		}
	}
	else			// If not filled
	{
		t_followTile->isMarked = true;
		t_followTile->circle.setOutlineColor(sf::Color::Green);
		for (auto& neighbours : t_followTile->m_neighbours)
		{
			if (neighbours->isOccupied == true && neighbours->isMarked == false)
			{
				// Recursive checks
				sf::Vector3i direction = neighbours->m_gridCoordinates3axis - t_followTile->m_gridCoordinates3axis;
				checkHops(direction, neighbours);
			}
		}
	}

	return;
}



