#pragma once
// Author: Josh Tyrrell Browne
// Date: Jan 2021

#include "HexTile.h"
#include <iostream>
#include <vector>

enum GridType { Hexagon, Triangle };
enum GridOrientation { Flat, Pointy }; // the grid layout orientation (center cell either flat or pointy at top)

struct Orientation
{
	double f0, f1, f2, f3; // matrix
	double b0, b1, b2, b3; // inverse matrix
	double start_angle;

	Orientation() {};

	Orientation(double f0_, double f1_, double f2_, double f3_, double b0_, double b1_, double b2_, double b3_, double start_angle_) : 
		f0(f0_), 
		f1(f1_), 
		f2(f2_), 
		f3(f3_), 
		b0(b0_), 
		b1(b1_), 
		b2(b2_), 
		b3(b3_), 
		start_angle(start_angle_) 
	{}
	void operator==(Orientation t_orientation) 
	{ 
		f0 = t_orientation.f0;
		f1 = t_orientation.f1;
		f2 = t_orientation.f2;
		f3 = t_orientation.f3;
		b0 = t_orientation.b0;
		b1 = t_orientation.b1;
		b2 = t_orientation.b2;
		b3 = t_orientation.b3;
		start_angle = t_orientation.start_angle; 
	}
};
const Orientation layout_pointy = Orientation(
	sqrt(3.0), 
	sqrt(3.0) / 2.0, 
	0.0, 3.0 / 2.0, 
	sqrt(3.0) / 3.0, 
	-1.0 / 3.0,
	0.0, 2.0 / 3.0, 
	0.5);

const Orientation layout_flat = Orientation(
	3.0 / 2.0, 
	0.0, 
	sqrt(3.0) / 2.0, 
	sqrt(3.0), 
	2.0 / 3.0, 
	0.0, -1.0 / 3.0, 
	sqrt(3.0) / 3.0, 
	0.0);

struct Layout
{
	Orientation orientation;
	int size;
	sf::Vector2f origin;
	Layout() {};
	Layout(Orientation orientation_, int size_, sf::Vector2f origin_) : orientation(orientation_), size(size_), origin(origin_) {}
};

class HexGrid
{
public:
	HexGrid(int t_hexSize, sf::Vector2f t_originPos, GridOrientation t_gridOrientation, GridType t_gridType, int t_gridSize);

	std::vector<HexTile*>* getGrid();

	int m_hexSize;
	sf::Vector2f m_originPos; // origin game world position of grid
	Orientation m_orientation;
	Layout m_layout;
	//Map m_map ??
	GridOrientation m_gridOrientation;
	GridType m_gridType;
	int m_gridSize; // number of cells in grid
	std::vector<HexTile*> m_gridHexTiles; // vector conatianing grid tiles

	void TileGeneration(); //Generates grid tiles
	sf::Vector2f hex_to_pixel(Layout layout, sf::Vector3i t_hexGridCoordinates);
	void render(sf::RenderWindow* t_rendWindow);
};