#include "HexTile.h"

void HexTile::setupCircle()
{
    circle.setPosition(m_position);
    circle.setRadius(m_cellSize / 2);
    circle.setOrigin(circle.getRadius() / 2, circle.getRadius() / 2);
    circle.setFillColor(sf::Color::Red);
}

void HexTile::setNeighbour(HexTile* t_neighbour)
{
    m_neighbours.push_back(t_neighbour);
}

void HexTile::render(sf::RenderWindow* t_rendWindow)
{
    t_rendWindow->draw(circle);
}

sf::Vector3i HexTile::hex_add(HexTile t_hexTile)
{
    return sf::Vector3i(this->m_gridCoordinates3axis.x + t_hexTile.m_gridCoordinates3axis.x, this->m_gridCoordinates3axis.y + t_hexTile.m_gridCoordinates3axis.y, this->m_gridCoordinates3axis.z + t_hexTile.m_gridCoordinates3axis.z);
}

sf::Vector3i HexTile::hex_subtract(HexTile t_hexTile)
{
    return sf::Vector3i(this->m_gridCoordinates3axis.x - t_hexTile.m_gridCoordinates3axis.x, this->m_gridCoordinates3axis.y - t_hexTile.m_gridCoordinates3axis.y, this->m_gridCoordinates3axis.z - t_hexTile.m_gridCoordinates3axis.z);
}

sf::Vector3i HexTile::hex_direction(int t_direction)
{
    return hex_directions[t_direction];
}
