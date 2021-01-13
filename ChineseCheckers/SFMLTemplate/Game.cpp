#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 3840, 2160, 32 }, "Game Screen" },
	m_exitGame{ false },
	m_HexGridCenter(20, sf::Vector2f(1000, 1000), GridOrientation::Flat, GridType::Hexagon, 10)
{
	for (int i = 0; i < 6; i++)
	{

		HexGrid* p_HexGrid = new HexGrid(20, sf::Vector2f(1000, 1000), GridOrientation::Flat, GridType::Triangle, 10);
	}
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				
			}
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();		// Exiting the game
	}
	//m_player.update(t_deltaTime);
	//m_npc.update(t_deltaTime);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	//m_player.render(m_window);
	//m_npc.render(m_window);
	m_HexGridCenter.render(&m_window);
	m_window.display();
}

