#pragma once
// Author: Josh Tyrrell Browne
// Date: Jan 2021
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

//Class to hold tile data
class HexTile
{
public:
	// constructor
	HexTile(sf::Vector2f t_position, sf::Vector3i t_gridCoordinates3axis, int t_cellSize) { m_position = t_position; m_gridCoordinates3axis = t_gridCoordinates3axis; m_cellSize = t_cellSize; setupCircle(); }
	HexTile(sf::Vector3i t_gridCoordinates3axis) { m_gridCoordinates3axis = t_gridCoordinates3axis; setupCircle(); } // Overloaded, only grid coords passed, figure out gameworld pos
	void setupCircle();
	void setNeighbour(HexTile* t_neighbour);
	void render(sf::RenderWindow* t_rendWindow);

	sf::Vector2f m_position; // The game world position of the Hex tile 
	sf::Vector3i m_gridCoordinates3axis; // the grid coordinates, (on three axis), hex coordinates
	sf::CircleShape circle;
	int m_cellSize;
	//HexMap* map;

	const std::vector<sf::Vector3i> hex_directions = { sf::Vector3i(1, 0, -1), sf::Vector3i(1, -1, 0), sf::Vector3i(0, -1, 1), sf::Vector3i(-1, 0, 1), sf::Vector3i(-1, 1, 0), sf::Vector3i(0, 1, -1) };


	sf::Vector3i hex_add(HexTile t_hexTile); // returns position from 2 added hextile positions
	sf::Vector3i hex_subtract(HexTile t_hexTile);
	//sf::Vector3f hex_scale(HexTile t_hexTile);
	
	//HexTile hex_rotate_left(HexTile t_hexTile);
	//HexTile hex_rotate_right(HexTile t_hexTile);

	sf::Vector3i hex_direction(int t_direction); //returns the direction in 3 axis hex coordinates (for grid)

	// Robin
	std::vector<HexTile*> m_neighbours;
	bool isOccupied;
};