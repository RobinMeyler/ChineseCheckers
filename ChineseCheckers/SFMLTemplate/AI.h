#pragma once
#include <SFML\Graphics.hpp>
#include "HexTile.h"
class AI
{
public:
	AI();
	~AI();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);


	sf::Sprite m_sprite;
	sf::Texture m_texture;

	int screenWidth;
	int screenHeigth;


	std::vector<sf::CircleShape> m_marbles;
	HexTile* m_tile;
};
