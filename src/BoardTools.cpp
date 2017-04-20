#include "../includes/Gomoku.hpp"

t_Color		BoardTools::GetPointValue(char *Board[][19], t_vec2 coord)
{
	return ((t_Color)*(Board[coord.y][coord.x]));
}

t_Color		BoardTools::GetPointValue(char *Board[][19], int x, int y)
{
	return ((t_Color)*(Board[y][x]));
}