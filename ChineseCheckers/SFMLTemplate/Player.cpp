#include "Player.h"


Player::Player(sf::RenderWindow& t_window)
{
	// Load a texture from a file
	m_texture.loadFromFile("Assets/Textures/rocketPixel.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);

	//screen dimensions
	screenHeigth = t_window.getSize().y;
	screenWidth = t_window.getSize().x;
}

Player::~Player()
{

}

void Player::update(sf::Time t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_sprite.move(0, -5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_sprite.move(0, 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_sprite.move(-5, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_sprite.move(5, 0);
	}

	//wrap around checks
	if (m_sprite.getPosition().x > screenWidth)
	{
		m_sprite.setPosition(0, m_sprite.getPosition().y);
	}
	else if (m_sprite.getPosition().x < 0)
	{
		m_sprite.setPosition(screenWidth, m_sprite.getPosition().y);
	}
	if (m_sprite.getPosition().y > screenHeigth)
	{
		m_sprite.setPosition(0, m_sprite.getPosition().y);
	}
	else if (m_sprite.getPosition().y < 0)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, screenHeigth);
	}
}

void Player::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_sprite);
}
