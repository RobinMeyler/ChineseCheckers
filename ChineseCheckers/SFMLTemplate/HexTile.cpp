#include "HexTile.h"

//HexTile::HexTile(const HexTile& other) //copy constructor
//{
//    m_position = *new MyVector3(other.m_position);
//    m_gridCoordinates3axis = *new MyVector3(other.m_gridCoordinates3axis);
//    isOccupied = *new bool(other.isOccupied);
//    circle = *new sf::CircleShape(other.circle);
//}

void HexTile::copyNeighbours(std::vector<HexTile*> t_neighboursToCopy, std::vector<HexTile*> t_copyOfAllTiles)
{
    for (auto neighbour : t_neighboursToCopy) // loop each neighbour to copy
    {
        for (auto tile : t_copyOfAllTiles) // loop through all new copy tiles to find matching neighbour
        {
            if (tile->m_gridCoordinates3axis == neighbour->m_gridCoordinates3axis)
            {
                m_neighbours.push_back(tile);
            }
        }
    }
}

void HexTile::setupCircle()
{
    m_font.loadFromFile("digital-7.ttf");

    circle.setPosition(m_position);
    circle.setRadius(m_cellSize / 1.5f);
    circle.setOrigin(circle.getRadius() / 2, circle.getRadius() / 2);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::White);

    text_x.setCharacterSize(30);
    text_x.setFont(m_font);
    text_x.setFillColor(sf::Color::Magenta);
    text_x.setPosition(sf::Vector2f(m_position.x, m_position.y ));
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
    t_rendWindow->draw(text_x);
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

HexTile* HexTile::checkHops(sf::Vector3i t_direction, HexTile* t_followTile)
{
    if (t_followTile->isOccupied == true)		// If it's filled
    {
        t_followTile->isMarked = true;
        sf::Vector3i newCoords = t_followTile->m_gridCoordinates3axis + t_direction;
        for (auto& tile : t_followTile->m_neighbours)
        {
            if (tile->m_gridCoordinates3axis == newCoords)	// If spot at new coords exists
            {
                if (tile->isOccupied == false)				// and is not filled
                {
                    checkHops(t_direction, tile);			// Mark and check it
                }
                else
                {
                    return nullptr;
                }
            }
        }
    }
    else // If not filled
    {
        t_followTile->isMarked = true;
        //t_followTile->circle.setOutlineColor(sf::Color::Green);
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

    return t_followTile;
}

std::vector<HexTile*> HexTile::getPossibleMovesFromThisTile()
{
    possibleMoves.clear();
    for (auto& neighbour : m_neighbours) //each neighbour
    {
        if (neighbour->isOccupied == false)
        {
            neighbour->isMarked = true;
            possibleMoves.push_back(neighbour);
            //neighbour->circle.setOutlineColor(sf::Color::Green);
        }
        else
        {
            // Recursive checks
            sf::Vector3i direction = neighbour->m_gridCoordinates3axis - m_gridCoordinates3axis;
            HexTile* temp = checkHops(direction, neighbour);
            if (temp != nullptr && temp != neighbour)
                possibleMoves.push_back(temp);
        }
    }
    return possibleMoves;
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
