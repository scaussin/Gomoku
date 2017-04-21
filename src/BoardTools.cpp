#include "../includes/Gomoku.hpp"

t_Color		BoardTools::GetPointValue(Board &Board, t_vec2 coord)
{
	return ((t_Color)(Board.Map[coord.y][coord.x]));
}

t_Color		BoardTools::GetPointValue(Board &Board, int x, int y)
{
	return ((t_Color)(Board.Map[y][x]));
}

void		BoardTools::DisplayBoardChars(Board &Board)
{
	int			x = 0;
	int			y = 18;
	t_Color		value;

	for (; y != -1; y--)
	{
		for(x = 0; x < 19; x++)
		{
			value = (t_Color)Board.Map[y][x];
			if (value == NONE)
				printf(".");
			else if (value == BLACK)
				printf("O");
			else if (value == WHITE)
				printf("X");
		}
		printf("\n");
	}
}
