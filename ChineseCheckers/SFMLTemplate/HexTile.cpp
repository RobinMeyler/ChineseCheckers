#include "HexTile.h"

void HexTile::setupCircle()
{
    m_font.loadFromFile("digital-7.ttf");

    circle.setPosition(m_position);
    circle.setRadius(m_cellSize / 1.5f);
    circle.setOrigin(circle.getRadius() / 2, circle.getRadius() / 2);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::White);

    text_x.setCharacterSize(20);
    text_x.setFont(m_font);
    text_x.setFillColor(sf::Color::Magenta);
    text_x.setPosition(sf::Vector2f(m_position.x -10, m_position.y - 10));
    text_x.setString("0");
    text_y.setCharacterSize(20);
    text_y.setFont(m_font);
    text_y.setFillColor(sf::Color::Magenta);
    text_y.setPosition(sf::Vector2f(m_position.x, m_position.y + 10));

    text_z.setCharacterSize(20);
    text_z.setFont(m_font);
    text_z.setFillColor(sf::Color::Magenta);
    text_z.setPosition(sf::Vector2f(m_position.x + 10, m_position.y - 10));
}

void HexTile::setNeighbour(HexTile* t_neighbour)
{
    m_neighbours.push_back(t_neighbour);
}

void HexTile::render(sf::RenderWindow* t_rendWindow)
{
    t_rendWindow->draw(circle);
    //t_rendWindow->draw(text_x);
    //t_rendWindow->draw(text_y);
   // t_rendWindow->draw(text_z);
}

void HexTile::setPosition(MyVector3 t_newPos)
{
    m_position = t_newPos;
    circle.setPosition(t_newPos);

    text_x.setPosition(sf::Vector2f(m_position.x - 10, m_position.y - 10));
    text_y.setPosition(sf::Vector2f(m_position.x, m_position.y + 10));
    text_z.setPosition(sf::Vector2f(m_position.x + 10, m_position.y - 10));
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
