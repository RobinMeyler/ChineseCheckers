#include "Player.h"


Player::Player()
{


	int oop = 60;
	for (int i = 0; i < 10; i++)
	{
		GamePiece marble;
		marble.m_circle.setFillColor(sf::Color::Blue);
		marble.m_circle.setRadius(30/1.25f);
		marble.m_circle.setOrigin(14, 14);
		marble.m_circle.setPosition(oop, 120);
		oop += 60;
		m_marbles.push_back(marble);
	}

}

Player::~Player()
{

}

void Player::update(sf::Time t_deltaTime)
{

}

void Player::render(sf::RenderWindow &t_window)
{
	for (auto& marble : m_marbles)
	{
		t_window.draw(marble.m_circle);
	}
}
