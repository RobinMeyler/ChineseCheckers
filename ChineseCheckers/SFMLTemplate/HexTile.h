#pragma once
// Author: Josh Tyrrell Browne & Robin Meyler
// Date: Jan 2021
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "MyVector3.h"

//Class to hold tile data
class HexTile
{
public:
	// constructor
	HexTile(sf::Vector2f t_position, sf::Vector3i t_gridCoordinates3axis, int t_cellSize) { m_position = t_position; m_gridCoordinates3axis = t_gridCoordinates3axis; m_cellSize = t_cellSize; setupCircle(); }
	HexTile(sf::Vector3i t_gridCoordinates3axis) { m_gridCoordinates3axis = t_gridCoordinates3axis; setupCircle(); } // Overloaded, only grid coords passed, figure out gameworld pos
	//copy constructor
	//HexTile(const HexTile& other);
	void copyNeighbours(std::vector<HexTile*> t_neighboursToCopy, std::vector<HexTile*> t_copyOfAllTiles);

	void setupCircle();
	void setNeighbour(HexTile* t_neighbour);
	void render(sf::RenderWindow* t_rendWindow);
	void setPosition(MyVector3 t_newPos);

	HexTile* checkHops(sf::Vector3i t_direction, HexTile* t_followTile);

	std::vector<HexTile*> getPossibleMovesFromThisTile(); //returns the positions which a piece at this location could move to
	std::vector<HexTile*> possibleMoves;

	MyVector3 m_position; // The game world position of the Hex tile 
	MyVector3 m_gridCoordinates3axis; // the grid coordinates, (on three axis), hex coordinates
	sf::CircleShape circle;
	int m_cellSize;

	const std::vector<sf::Vector3i> hex_directions = { sf::Vector3i(1, 0, -1), sf::Vector3i(1, -1, 0), sf::Vector3i(0, -1, 1), sf::Vector3i(-1, 0, 1), sf::Vector3i(-1, 1, 0), sf::Vector3i(0, 1, -1) };


	sf::Vector3i hex_add(HexTile t_hexTile); // returns position from 2 added hextile positions
	sf::Vector3i hex_subtract(HexTile t_hexTile);

	sf::Vector3i hex_direction(int t_direction); //returns the direction in 3 axis hex coordinates (for grid)

	// Robin
	std::vector<HexTile*> m_neighbours;
	bool isOccupied{ false };
	bool isMarked{ false };
	sf::Text text_x;
	sf::Text text_y;
	sf::Text text_z;
	sf::Font m_font;

	bool isRedFinishSlot{ false };
	bool isBlueFinishSlot{ false };
	bool winReady{ false };

	float m_AiScoreValueMinMax{ 0 };

	float heuristicValue;
};