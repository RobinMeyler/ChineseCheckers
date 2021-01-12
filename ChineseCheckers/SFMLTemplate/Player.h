#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
class Player
{
public:
	Player(sf::RenderWindow& t_window);
	~Player();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	float m_acceleration;
	int screenWidth;
	int screenHeigth;


	sf::Event event;
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message


};