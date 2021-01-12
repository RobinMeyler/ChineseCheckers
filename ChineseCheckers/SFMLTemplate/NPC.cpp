#include "NPC.h"

NPC::NPC(sf::RenderWindow& t_window)
{
	// Load a texture from a file
	m_texture.loadFromFile("Assets/Textures/chinaManPixel.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 1000);

	//screen dimensions
	screenHeigth = t_window.getSize().y;
	screenWidth = t_window.getSize().x;
}

NPC::~NPC()
{
}

void NPC::update(sf::Time t_deltaTime)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_sprite.move(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_sprite.move(0, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_sprite.move(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_sprite.move(1, 0);
	}*/
	m_sprite.move(1, 0);
	if (m_sprite.getPosition().x > screenWidth)
	{
		
		m_sprite.setPosition(0, m_sprite.getPosition().y);
	}
}

void NPC::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
}
