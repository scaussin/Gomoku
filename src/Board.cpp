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