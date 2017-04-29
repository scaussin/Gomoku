#include "../includes/Gomoku.hpp"

Board::Board()
{
	lastMove.y = -1;
	lastMove.x = -1;
	parent = NULL;
	isVictory = false;
}

Board::Board(Board &rhs, Board *parent, t_vec2 move, t_Color player)
{
	*this = rhs;
	this->parent = parent;
	this->lastMove = move;
	setPoint(move, player);
}

Board::~Board()
{
	for (auto it = next.begin() ; it != next.end() ; ++it)
	{
		delete *it;
	}
	next.clear();
}

Board			&Board::operator=(const Board& other)
{
	for (int y = 0; y != 19; y++)
	{
		memcpy(&this->map[y], other.map[y], 19);
		/*for (int x = 0; x < 19; ++x)
		{
			this->map[y][x] = other.map[y][x];
		}*/
	}
	return (*this);
}

char	Board::getPoint(t_vec2 at)
{
	if (at.y < 0 || at.y > 18 || at.x < 0 | at.x > 18)
	{
		PERROR("t_vec2 out of range");
		return (-1);
	}
	return (map[at.y][at.x]);
}

char	Board::getPoint(int y, int x)
{
	if (y < 0 || y > 18 || x < 0 | x > 18)
	{
		PERROR("t_vec2 out of range");
		return (-1);
	}
	return (map[y][x]);
}

bool	Board::setPoint(t_vec2 at, t_Color color)
{
	if (at.y < 0 || at.y > 18 || at.x < 0 | at.x > 18)
	{
		PERROR("t_vec2 out of range");
		return (false);
	}
	map[at.y][at.x] = color;
	return (true);
}

bool 	Board::setPoint(int y, int x, t_Color color)
{
	if (y < 0 || y > 18 || x < 0 | x > 18)
	{
		PERROR("t_vec2 out of range");
		return (false);
	}
	return (true);
}