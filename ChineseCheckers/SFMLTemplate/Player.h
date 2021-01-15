#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "HexTile.h"
#include "GamePiece.h"
class Player
{
public:
	Player();
	~Player();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);

	sf::Event event;
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	std::vector<GamePiece> m_marbles;
};