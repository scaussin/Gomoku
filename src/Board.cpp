#include "../includes/Gomoku.hpp"

Board::Board()
{

}

Board::~Board()
{

}

Board			&Board::operator=(const Board& other)
{
	int x;
	for (int y = 0; y != 19; y++)
	{
		for (x = 0; x < 19; ++x)
		{
			this->Map[y][x] = other.Map[y][x];
		}
	}
	return (*this);
}

char	Board::getPoint(t_vec2 at)
{
	if (at.y < 0 || at.y > 19 || at.x < 0 | at.x > 19)
		return (-1);
	return (Map[at.y][at.x]);
}

char	Board::getPoint(int y, int x)
{
	if (y < 0 || y > 19 || x < 0 | x > 19)
		return (-1);
	return (Map[y][x]);
}

bool	Board::setPoint(t_vec2 at, t_Color color)
{
	if (at.y < 0 || at.y > 19 || at.x < 0 | at.x > 19)
		return (false);
	Map[at.y][at.x] = color;
	return (true);
}

bool 	Board::setPoint(int y, int x, t_Color color)
{
	if (y < 0 || y > 19 || x < 0 | x > 19)
		return (false);
	Map[y][x] = color;
	return (true);
}