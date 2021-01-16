#include "Game.h"


Players Game::m_players{ Players::PlayerOne };

Game::Game() :
	m_window{ sf::VideoMode{ 1420, 1080, 32 }, "Chinese Checkers" },
	m_exitGame{ false },
	m_gamePhase{ Phase::SelectingPieceToMove},
	m_HexGridCenter(30, sf::Vector2f(710, 540), GridOrientation::Pointy, GridType::Hexagon, 4, 0, sf::Vector3i(0,0,0), Config::one)
{
	// Have grid
	m_tilesPtr = m_HexGridCenter.getGrid();

	m_font.loadFromFile("digital-7.ttf");
	m_gameText.setCharacterSize(80);
	m_gameText.setFont(m_font);
	m_gameText.setFillColor(sf::Color::White);
	m_gameText.setPosition(sf::Vector2f(500, 50));
	m_gameText.setString("Player's turn!");

	std::vector<sf::Vector3i> startCoords;
	startCoords.push_back(sf::Vector3i(-1, 5, -4));
	startCoords.push_back(sf::Vector3i(-5, 4, 1));
	startCoords.push_back(sf::Vector3i(-4, -1, 5));
	startCoords.push_back(sf::Vector3i(1, -5, 4));
	startCoords.push_back(sf::Vector3i(5, -4, -1));
	startCoords.push_back(sf::Vector3i(4, 1, -5));
	sf::Color colours[6] = { sf::Color::Red, sf::Color::Green, sf::Color::Yellow, sf::Color::Blue,  sf::Color::Magenta, sf::Color::Cyan };

	// Making Triangles
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
				p_HexGrid->m_gridHexTiles.at(j)->isRedFinishSlot = true;
				m_redFinishSpots.push_back(p_HexGrid->m_gridHexTiles.at(j));
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
				p_HexGrid->m_gridHexTiles.at(j)->isBlueFinishSlot = true;
				m_blueFinishSpots.push_back(p_HexGrid->m_gridHexTiles.at(j));
				/*m_AI.m_marbles.at(j).m_circle.setPosition(p_HexGrid->m_gridHexTiles.at(j)->m_position);
				m_AI.m_marbles.at(j).tile = p_HexGrid->m_gridHexTiles.at(j);
				p_HexGrid->m_gridHexTiles.at(j)->isOccupied = true*/;
			}
		}
		m_HexGridTriangleWedges.push_back(p_HexGrid);
	}

	// Combine Grids
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

	// Set Neighbours
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
	m_AI.m_marbles.at(0).m_circle.setPosition(m_allTiles.at(3)->m_position);
	m_AI.m_marbles.at(0).tile = m_allTiles.at(3);
	m_allTiles.at(3)->isOccupied = true;

	m_AI.m_marbles.at(1).m_circle.setPosition(m_allTiles.at(23)->m_position);
	m_AI.m_marbles.at(1).tile = m_allTiles.at(23);
	m_allTiles.at(23)->isOccupied = true;

	m_AI.m_marbles.at(2).m_circle.setPosition(m_allTiles.at(9)->m_position);
	m_AI.m_marbles.at(2).tile = m_allTiles.at(9);
	m_allTiles.at(9)->isOccupied = true;

	m_AI.m_marbles.at(3).m_circle.setPosition(m_allTiles.at(6)->m_position);
	m_AI.m_marbles.at(3).tile = m_allTiles.at(6);
	m_allTiles.at(6)->isOccupied = true;

	m_AI.m_marbles.at(4).m_circle.setPosition(m_allTiles.at(14)->m_position);
	m_AI.m_marbles.at(4).tile = m_allTiles.at(14);
	m_allTiles.at(14)->isOccupied = true;

	m_AI.m_marbles.at(5).tile = m_allTiles.at(16);
	m_AI.m_marbles.at(5).m_circle.setPosition(m_allTiles.at(39)->m_position);
	m_allTiles.at(39)->isOccupied = true;

	m_AI.m_marbles.at(6).tile = m_allTiles.at(12);
	m_AI.m_marbles.at(6).m_circle.setPosition(m_allTiles.at(12)->m_position);
	m_allTiles.at(12)->isOccupied = true;

	m_AI.m_marbles.at(7).tile = m_allTiles.at(41);
	m_AI.m_marbles.at(7).m_circle.setPosition(m_allTiles.at(41)->m_position);
	m_allTiles.at(41)->isOccupied = true;

	m_AI.m_marbles.at(8).tile = m_allTiles.at(4);
	m_AI.m_marbles.at(8).m_circle.setPosition(m_allTiles.at(4)->m_position);
	m_allTiles.at(4)->isOccupied = true;

	m_AI.m_marbles.at(9).tile = m_allTiles.at(3);
	m_AI.m_marbles.at(9).m_circle.setPosition(m_allTiles.at(3)->m_position);
	m_allTiles.at(3)->isOccupied = true;
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
					m_leftMousePressed = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					m_rightPressed = true;
				}
			}
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	checkForWin();

	if (m_gameFinished != true)
	{
		if (Game::m_players == Players::PlayerOne)
		{
			runPlayerStates();
		}
		else
		{
			runAIStates();
		}
	}


	if (m_exitGame)
	{
		m_window.close();		// Exiting the game
	}
}

void Game::render()
{
	m_window.clear(sf::Color(0.2f*255, 0.3f * 255, 0.3f * 255, 1.0f));

	m_window.draw(m_gameText);
	m_HexGridCenter.render(&m_window);
	for (int i = 0; i < m_HexGridTriangleWedges.size(); i++)
	{
		m_HexGridTriangleWedges.at(i)->render(&m_window);
	}

	m_AI.render(m_window);
	m_player.render(m_window);

	m_window.display();
}

void Game::runPlayerStates()
{
	if (m_gamePhase == Phase::SelectingPieceToMove)
	{
		if (m_leftMousePressed == true)
		{
			checkIfGamePiece();
		}
	}
	if (m_gamePhase == Phase::Evaluating)
	{
		evaluatePossibleMoves();
	}
	else if (m_gamePhase == Phase::SelectingTileToMoveTo)
	{
		if (m_leftMousePressed == true)
		{
			checkIfMoveAllowed();
		}
	}
	else if (m_gamePhase == Phase::Moving)
	{
		moveGamePiece();
	}
}

void Game::runAIStates()
{
	// AI ==============================================================

		// Run evaluation function ============
	// AI ( For now )

		// Run evaluation function
	runEvaluation();
	Game::m_players = Players::PlayerOne;
	// Use Min Max to determine which is best
	/*for (int i = 0; i < m_AI.m_marbles.size(); i++)
	{
		m_AI.minimax(m_AI.m_marbles.at(i).tile, 8, false, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	}*/

	m_AI.minimax(m_AI.m_marbles, m_AI.m_oppositionMarbles, m_AI.m_marbles.at(0).tile, 5, true, m_AI.getCopyOfMapTiles(m_allTiles));

	// Make move
	for (int i = 0; i < m_AI.m_marbles.size(); i++)//(auto piece : m_AI.m_marbles)
	{
		if (m_AI.m_marbles.at(i).tile->m_gridCoordinates3axis == m_AI.bestMove.piece.tile->m_gridCoordinates3axis)
		{
			for (auto tile : m_allTiles)
			{
				if (tile->m_gridCoordinates3axis == m_AI.bestMove.tileToMoveTo->m_gridCoordinates3axis)
				{
					m_AI.m_marbles.at(i).tile->isOccupied = false;
					m_AI.m_marbles.at(i).tile = tile;
					m_AI.m_marbles.at(i).tile->m_position = tile->m_position;
					m_AI.m_marbles.at(i).m_circle.getPosition();
					m_AI.m_marbles.at(i).m_circle.setPosition(m_AI.m_marbles.at(i).tile->m_position);
					m_AI.m_marbles.at(i).m_circle.getPosition();
					m_AI.m_marbles.at(i).tile->isOccupied = true;
				}
			}
		}
	}

	/*m_AI.bestMove.piece.tile->isOccupied = false;
	m_AI.bestMove.piece.tile = m_AI.mostIdealMove.tileToMoveTo;
	m_AI.bestMove.piece.m_circle.setPosition(m_AI.mostIdealMove.piece.tile->m_position);
	m_AI.bestMove.piece.tile->isOccupied = true;*/

	m_gamePhase = Phase::SelectingPieceToMove;
	// Swap turn;
	Game::m_players = Players::PlayerOne;
	// Use Min Max to determine which is best ==========================
	// For each tile:
	// Check AI's highest scoring move, then the players lowest scoring in that case, the players best scoring move etc
	// Compare the best Tile with the highest max after deep check and move to that one


	// Make move =======================================================
	// Set occupied
	// set last not occupied
	// check if win ready
	// Set positions


	Game::m_players = Players::PlayerOne;
	m_gameText.setString("Player's turn!");
}


// Recursive
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

void Game::runEvaluation()
{

	// Distance, 
	GamePiece* furthestBackMarble = nullptr;
	GamePiece* furthestForwardMarble = nullptr;
	int checkY = 10;
	int checkYOther = -10;
	for (auto& gamePiece : m_AI.m_marbles)		// For Each AI Piece
	{
		if (gamePiece.tile->m_gridCoordinates3axis.y < checkY)
		{
			furthestBackMarble = &gamePiece;
			checkY = gamePiece.tile->m_gridCoordinates3axis.y;
		}
		if (gamePiece.tile->m_gridCoordinates3axis.y > checkYOther)
		{
			furthestForwardMarble = &gamePiece;
			checkYOther = gamePiece.tile->m_gridCoordinates3axis.y;
		}
	}

	// Now have the shortest Path
	for (auto& tile : m_allTiles)				// for every Tile
	{
		tile->m_AiScoreValueMinMax = 0;
	}

	for (auto& gamePiece : m_AI.m_marbles)		// For Each AI Piece
	{
		if (gamePiece.tile->winReady == false)
		{
			int furthestPathToEnd = 0;
			HexTile* End = nullptr;
			for (auto& finishTile : m_redFinishSpots)		// for each tile in the endZone, find the closest one
			{
				int result = findAxisdiff(finishTile, gamePiece.tile);

				if (result > furthestPathToEnd)
				{
					furthestPathToEnd = result;
					End = finishTile;
				}
			}

			

			// Now have the shortest Path
			for (auto& tile : m_allTiles)				// for every Tile
			{
				//tile->m_AiScoreValueMinMax = 0;
				
				float distanceToEnd = findAxisdiff(tile, End);		// Find the distance to the furthest end tile
				float inversedDistance = furthestPathToEnd - distanceToEnd;		// New score is the distance from gamePiece to the end - the actual diatance to the end
				int YaxisValue = tile->m_gridCoordinates3axis.y;
				if (tile->m_gridCoordinates3axis.y >= furthestBackMarble->tile->m_gridCoordinates3axis.y)
				{
					YaxisValue = -tile->m_gridCoordinates3axis.y;
				}
				float evaluation = (YaxisValue* 0.25f) + (inversedDistance * 2.f) + (distanceToEnd * 0.8f);

				if (tile->m_AiScoreValueMinMax < evaluation)		// If it isn't already score higher
				{
					tile->m_AiScoreValueMinMax = evaluation;		// If the tile is further away than the player it will be -1, -2 etc, if closer 1, 2 etc
				}
			
				//tile->text_x.setString(std::to_string((int)tile->m_AiScoreValueMinMax));
			}
		}
	}
	float difference = furthestForwardMarble->tile->m_gridCoordinates3axis.y - furthestBackMarble->tile->m_gridCoordinates3axis.y;
	for (auto& tile : furthestBackMarble->tile->m_neighbours)
	{
		if (tile->m_gridCoordinates3axis.y > furthestBackMarble->tile->m_gridCoordinates3axis.y)
		{
			if (tile->isOccupied == true)
			{
				sf::Vector3i direction = tile->m_gridCoordinates3axis - furthestBackMarble->tile->m_gridCoordinates3axis;
				sf::Vector3i newCoords = tile->m_gridCoordinates3axis + direction;
				for (auto& innerTile : tile->m_neighbours)
				{
					if (innerTile->m_gridCoordinates3axis == newCoords)	// If spot at new coords exists
					{
						if (innerTile->isOccupied == false)
						{
							innerTile->m_AiScoreValueMinMax += difference + 2;
						}
					}
				}
			}
			else
			{
				tile->m_AiScoreValueMinMax += difference;
			}
			
		}
	}
	
	// Now have the shortest Path
	for (auto& tile : m_allTiles)				// for every Tile
	{
		tile->text_x.setString(std::to_string((int)tile->m_AiScoreValueMinMax));
	}
}

int Game::findAxisdiff(HexTile* one, HexTile* two)
{
	int largestAxisDiff = 30;
	int distanceX = abs(one->m_gridCoordinates3axis.x - two->m_gridCoordinates3axis.x);
	int distanceY = abs(one->m_gridCoordinates3axis.y - two->m_gridCoordinates3axis.y);
	int distanceZ = abs(one->m_gridCoordinates3axis.z - two->m_gridCoordinates3axis.z);

	if (distanceX > distanceY)
	{
		largestAxisDiff = distanceX;
	}
	else
	{
		largestAxisDiff = distanceY;
	}
	if (largestAxisDiff < distanceZ)
	{
		largestAxisDiff = distanceZ;
	}
	return largestAxisDiff;
}

void Game::checkForWin()
{
	bool winBlue = false;
	for (auto& finish : m_blueFinishSpots)
	{
		if (finish->isOccupied == true && finish->winReady == true)
		{
			winBlue = true;
		}
		else
		{
			winBlue = false;
			break;
		}
	}
	if (winBlue == true)
	{
		// Win player
		m_gameText.setString("Player wins! :)");
		m_gameFinished = true;
	}
	bool winRed = false;
	for (auto& finish : m_redFinishSpots)
	{
		if (finish->isOccupied == true && finish->winReady == true)
		{
			winRed = true;
		}
		else
		{
			winRed = false;
			break;
		}
	}
	if (winRed == true)
	{
		// Win AI
		m_gameText.setString("AI wins! :(");
		m_gameFinished = true;
	}
}

void Game::checkIfGamePiece()
{
	bool found = false;
	for (auto& piece : m_player.m_marbles)
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
	m_leftMousePressed = false;
}

void Game::evaluatePossibleMoves()
{
	for (auto& neighbours : m_pressedToPlayTile->m_neighbours)
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
	m_gamePhase = Phase::SelectingTileToMoveTo;
}

void Game::checkIfMoveAllowed()
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
		m_gamePhase = Phase::SelectingPieceToMove;
	}

	// Reset regardless
	for (HexTile* tile : m_allTiles)
	{
		tile->isMarked = false;
		tile->circle.setOutlineColor(tile->circle.getFillColor());
	}

	m_leftMousePressed = false;
}

void Game::moveGamePiece()
{
	// Move the Player Texture to the new position over a few frames
	m_pieceInPlay->tile->isOccupied = false;
	m_pieceInPlay->tile = m_pressedToMoveToTile;
	m_pieceInPlay->tile->winReady = false;
	m_pieceInPlay->m_circle.setPosition(m_pressedToMoveToTile->m_position);
	m_pressedToMoveToTile->isOccupied = true;
	m_gamePhase = Phase::SelectingPieceToMove;
	if (m_pressedToMoveToTile->isBlueFinishSlot)
	{
		m_pressedToMoveToTile->winReady = true;
	}

	// Swap turn;
	Game::m_players = Players::PlayerTwo;
	m_gameText.setString("AI's turn!");
}



