#pragma once
#include <SFML\Graphics.hpp>

class NPC
{
public:
	NPC(sf::RenderWindow& t_window);
	~NPC();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	int screenWidth;
	int screenHeigth;
};
