#include "AI.h"

AI::AI()
{

	int oop = 60;
	for (int i = 0; i < 10; i++)
	{
		GamePiece marble;
		marble.m_circle.setFillColor(sf::Color::Red);
		marble.m_circle.setRadius(30 / 1.25f);
		marble.m_circle.setOrigin(14, 14);
		marble.m_circle.setPosition(oop, 60);
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
		t_window.draw(marble.m_circle);
	}
}

float AI::minimax(HexTile* node, int depth, bool maximizingPlayer, float alpha,float beta)
{
	float bestValue = -1000000;// start with low value, for checks, we want highest val
	if (depth == 0)//if depth = 0 or node is a terminal node then
	{
		return node->heuristicValue;
	}

			
	if (maximizingPlayer) {
		bestValue = -std::numeric_limits<float>::max();
		for (size_t i = 0; i < 6; i++) // loop through each child (neighbour tile) (node.m_neighbours.at(i))
		{
			// check each neighbours heuristic against value (std::max returns largest value)
			float value = minimax(node->m_neighbours.at(i), depth - 1, false, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
			bestValue = std::max(bestValue, value);
			alpha = std::max(alpha, bestValue); //
			if (beta <= alpha)
				break;
		}
		return bestValue;
	}
	else {// (minimizing player)
		bestValue = std::numeric_limits<float>::max();
		for (size_t i = 0; i < 6; i++) // loop through each child (neighbour tile) (node.m_neighbours.at(i))
		{
			// check each neighbours heuristic against value (std::min returns smallest value)
			float value = minimax(node->m_neighbours.at(i), depth - 1, true, - std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
			bestValue = std::min(bestValue, value);
			beta = std::min(beta, bestValue);
			if (beta <= alpha)
				break;
		}
		return bestValue;
	}
}
