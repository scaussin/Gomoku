#include "../includes/Gomoku.hpp"

Board::Board()
{
	lastMove.y = -1;
	lastMove.x = -1;
	parent = NULL;
	isVictory = false;
	heuristic = 0;
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
	BlackCaptures = other.BlackCaptures;
	WhiteCaptures = other.WhiteCaptures;

	
	isVictory = false;
	heuristic = 0;

	for (int y = 0; y != 19; y++)
	{
		memcpy(&this->map[y], other.map[y], 19);
	}
	return (*this);
}

char	Board::getPoint(t_vec2 at)
{
	if (at.y < 0 || at.y > 19 || at.x < 0 || at.x > 19)
		return (-1);
	return (map[at.y][at.x]);
}

char	Board::getPoint(int y, int x)
{
	if (y < 0 || y > 19 || x < 0 || x > 19)
		return (-1);
	return (map[y][x]);
}

bool	Board::setPoint(t_vec2 at, t_Color color)
{
	if (at.y < 0 || at.y > 19 || at.x < 0 || at.x > 19)
	{
		PERROR("t_vec2 out of range", ERR);
		std::cout << ": " << at.x << "x " << at.y << "y" << std::endl;
		return (false);
	}
	map[at.y][at.x] = color;
	return (true);
}

bool 	Board::setPoint(int y, int x, t_Color color)
{
	if (y < 0 || y > 19 || x < 0 || x > 19)
	{
		PERROR("t_vec2 out of range", ERR);
		std::cout << ": " << x << "x " << y << "y" << std::endl;
		return (false);
	}
	map[y][x] = color;
	return (true);
}