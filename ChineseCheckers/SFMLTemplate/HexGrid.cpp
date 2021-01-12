#include "HexGrid.h"

HexGrid::HexGrid(int t_hexSize, sf::Vector2f t_originPos, GridOrientation t_gridOrientation, GridType t_gridType, int t_gridSize)
{
	m_hexSize = t_hexSize;
	m_originPos = t_originPos;
	m_gridOrientation = t_gridOrientation;
	m_gridType = t_gridType;
	m_gridSize = t_gridSize;
	//set orientation
	switch (m_gridOrientation)
	{
	case GridOrientation::Flat:
		m_orientation == layout_flat;
		break;
	case GridOrientation::Pointy:
		m_orientation == layout_pointy;
		break;
	default:
		break;
	}
	//set layout
	m_layout.orientation == m_orientation;
	m_layout.origin = m_originPos;
	m_layout.size = m_hexSize;

	TileGeneration();
}

void HexGrid::TileGeneration()
{
	switch (m_gridType)
	{
	case GridType::Hexagon:
	{
		for (int x = -m_gridSize; x <= m_gridSize; x++)
		{
			for (int y = 0; y <= m_gridSize; y++)
			{
				int z = -x - y;

				//std::abs(-10) = 10. Returns absalute value
				if (std::abs(x) <= m_gridSize && std::abs(y) <= m_gridSize && std::abs(z) <= m_gridSize) //if coordinates fit in our grid
				{
					sf::Vector3i gridCoordinates3axis = { x, y, z };
					sf::Vector2f positionCoordinates; // position in game world
					positionCoordinates = hex_to_pixel(m_layout, gridCoordinates3axis);

					HexTile* p_tile = new HexTile(positionCoordinates, gridCoordinates3axis);
					m_gridHexTiles.push_back(p_tile);
				}
			}
		}
		break;
	}
	case GridType::Triangle:
	{
		for (int x = 0; x <= m_gridSize; x++)
		{
			for (int y = 0; y <= x; y++)
			{
				sf::Vector3i gridCoordinates3axis = { x, -y, y - x };

				HexTile* p_tile = new HexTile(gridCoordinates3axis);
				p_tile->m_position = hex_to_pixel(m_layout, gridCoordinates3axis);
				m_gridHexTiles.push_back(p_tile);
			}
		}
		break;
	}
	default:
		break;
	}
}

sf::Vector2f HexGrid::hex_to_pixel(Layout layout, sf::Vector3i t_hexGridCoordinates)
{
	Orientation M = layout.orientation;
	int size = layout.size;
	sf::Vector2f origin = layout.origin;
	double x = (M.f0 * t_hexGridCoordinates.x + M.f1 * t_hexGridCoordinates.y) * size;
	double y = (M.f2 * t_hexGridCoordinates.x + M.f3 * t_hexGridCoordinates.y) * size;
	return sf::Vector2f(x + origin.x, y + origin.y);
}

void HexGrid::render(sf::RenderWindow* t_rendWindow)
{
	for (int i = 0; i < m_gridHexTiles.size(); i++)
	{
		m_gridHexTiles.at(i)->render(t_rendWindow);
	}
}
