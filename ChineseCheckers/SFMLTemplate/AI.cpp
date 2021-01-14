#include "AI.h"

AI::AI()
{


	int oop = 60;
	for (int i = 0; i < 10; i++)
	{
		sf::CircleShape marble;
		marble.setFillColor(sf::Color::Red);
		marble.setRadius(30 / 1.25f);
		marble.setOrigin(14, 14);
		marble.setPosition(oop, 60);
		oop += 60;
		m_marbles.push_back(marble);
	}
}

AI::~AI()
{
}

void AI::update(sf::Time t_deltaTime)
{

}

void AI::render(sf::RenderWindow& t_window)
{
	for (auto& marble : m_marbles)
	{
		t_window.draw(marble);
	}
}
