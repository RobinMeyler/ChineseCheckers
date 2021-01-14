#include "HexGrid.h"
#include "MyVector3.h"

HexGrid::HexGrid(int t_hexSize, sf::Vector2f t_originPos, GridOrientation t_gridOrientation, GridType t_gridType, int t_gridSize, int t_startAngle, sf::Vector3i t_startCoords, Config t_config)
{
	m_hexSize = t_hexSize;
	m_originPos = t_originPos;
	m_gridOrientation = t_gridOrientation;
	m_gridType = t_gridType;
	m_gridSize = t_gridSize;
	startCoords = t_startCoords;
	m_config = t_config;
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
	
	m_rotateAngle = t_startAngle;//for extra grid rotation 

	TileGeneration();
}

void HexGrid::correct()
{
	MyVector3 directionalVec = m_gridHexTiles.at(m_gridSize)->circle.getPosition() - m_gridHexTiles.at(0)->circle.getPosition();
	
	for (auto til : m_gridHexTiles)
	{
		MyVector3 newPos = til->m_position + directionalVec * 0.5f;
		til->setPosition(newPos);
	}
}

std::vector<HexTile*>* HexGrid::getGrid()
{
	return &m_gridHexTiles;
}

void HexGrid::TileGeneration()
{
	switch (m_gridType)
	{
	case GridType::Hexagon:
	{
		for (int x = -m_gridSize; x <= m_gridSize; x++)
		{
			for (int y = -m_gridSize; y <= m_gridSize; y++)
			{
				int z = -x - y;

				//std::abs(-10) = 10. Returns absalute value
				if (std::abs(x) <= m_gridSize && std::abs(y) <= m_gridSize && std::abs(z) <= m_gridSize) //if coordinates fit in our grid
				{
					sf::Vector3i gridCoordinates3axis = { x, y, z };
					sf::Vector2f positionCoordinates; // position in game world
					positionCoordinates = hex_to_pixel(m_layout, gridCoordinates3axis);

					HexTile* p_tile = new HexTile(positionCoordinates, gridCoordinates3axis, m_hexSize);
					p_tile->circle.setFillColor(sf::Color::White);
					p_tile->text_x.setString(std::to_string(p_tile->m_gridCoordinates3axis.x));
					p_tile->text_y.setString(std::to_string(p_tile->m_gridCoordinates3axis.y));
					p_tile->text_z.setString(std::to_string(p_tile->m_gridCoordinates3axis.z));
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
				sf::Vector3i gridCoordinates3axis;
				gridCoordinates3axis = { x, -y, y - x };
				sf::Vector2f positionCoordinates; // position in game world
				positionCoordinates = hex_to_pixel(m_layout, gridCoordinates3axis);

				if (m_config == Config::one)
				{
					if (startCoords.x < 0)
					{
						gridCoordinates3axis.x = startCoords.x - x;
					}
					else
					{
						gridCoordinates3axis.x = startCoords.x + x;
					}
					if (startCoords.y < 0)
					{
						gridCoordinates3axis.y = startCoords.y - y;
					}
					else
					{
						gridCoordinates3axis.y = startCoords.y + y;
					}
					if (startCoords.z < 0)
					{
						gridCoordinates3axis.z = startCoords.z - (y - x);
					}
					else
					{
						gridCoordinates3axis.z = startCoords.z + (y - x);
					}
				}
				else if (m_config == Config::two)
				{
					if (startCoords.x < 0)
					{
						gridCoordinates3axis.x = startCoords.x - y;
					}
					else
					{
						gridCoordinates3axis.x = startCoords.x + y;
					}
					if (startCoords.y < 0)
					{
						gridCoordinates3axis.y = startCoords.y - (y - x);
					}
					else
					{
						gridCoordinates3axis.y = startCoords.y + (y - x);
					}
					if (startCoords.z < 0)
					{
						gridCoordinates3axis.z = startCoords.z - x;
					}
					else
					{
						gridCoordinates3axis.z = startCoords.z + x;
					}
				}
				else if (m_config == Config::three)
				{
					if (startCoords.x < 0)
					{
						gridCoordinates3axis.x = startCoords.x - (y - x);
					}
					else
					{
						gridCoordinates3axis.x = startCoords.x + (y - x);
					}
					if (startCoords.y < 0)
					{
						gridCoordinates3axis.y = startCoords.y - x;
					}
					else
					{
						gridCoordinates3axis.y = startCoords.y + x;
					}
					if (startCoords.z < 0)
					{
						gridCoordinates3axis.z = startCoords.z - y;
					}
					else
					{
						gridCoordinates3axis.z = startCoords.z + y;
					}
				}

				if (m_rotateAngle != 0)
				{
					positionCoordinates = rotatePointAboutOrigin(positionCoordinates);
				}

				HexTile* p_tile = new HexTile(positionCoordinates, gridCoordinates3axis, m_hexSize);
				//p_tile->text_x.setString(std::to_string(p_tile->m_gridCoordinates3axis.x));
				//p_tile->text_y.setString(std::to_string(p_tile->m_gridCoordinates3axis.y));
				//p_tile->text_z.setString(std::to_string(p_tile->m_gridCoordinates3axis.z));
				m_gridHexTiles.push_back(p_tile);
			}
		}
		break;
	}
	default:
		break;
	}

	//m_gridHexTiles.at(0)->circle.setFillColor(sf::Color::Green);
}

sf::Vector2f HexGrid::hex_to_pixel(Layout layout, sf::Vector3i t_hexGridCoordinates)
{
	Orientation M = layout.orientation;
	//M.start_angle;
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

sf::Vector2f HexGrid::rotatePointAboutOrigin(sf::Vector2f t_PosToRotate)
{
	sf::Vector2f temp = t_PosToRotate;
	//first undo extra position settings (will be added back after rotation)
	temp = t_PosToRotate - m_originPos;
	temp.x = temp.x / m_hexSize;
	temp.y = temp.y / m_hexSize;

	sf::Vector2f rotatedPosition;
	rotatedPosition.x = (temp.x * cos(m_rotateAngle * 3.14159265 / 180)) - (temp.y * sin(m_rotateAngle * 3.14159265 / 180));
	rotatedPosition.y = (temp.x * sin(m_rotateAngle * 3.14159265 / 180)) + (temp.y * cos(m_rotateAngle * 3.14159265 / 180));
	
	//add position settings back
	rotatedPosition.x = rotatedPosition.x * m_hexSize;
	rotatedPosition.y = rotatedPosition.y * m_hexSize;
	rotatedPosition = rotatedPosition + m_originPos;

	return rotatedPosition;
}

//if (startCoords.x < 0)
//{
//	gridCoordinates3axis.x = startCoords.x - x;
//}
//else
//{
//	gridCoordinates3axis.x = startCoords.x + x;
//}
//if (startCoords.y < 0)
//{
//	gridCoordinates3axis.y = startCoords.y - y;
//}
//else
//{
//	gridCoordinates3axis.y = startCoords.y + y;
//}
//if (startCoords.z < 0)
//{
//	gridCoordinates3axis.z = startCoords.z - (y - x);
//}
//else
//{
//	gridCoordinates3axis.z = startCoords.z + (y - x);
//}