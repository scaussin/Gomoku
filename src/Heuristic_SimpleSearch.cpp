#include "../includes/Gomoku.hpp"

int		Heuristic::simpleSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, char *line, char *backLine)
{
	int				ret = 0;

	ret += simpleSearchPatternsCmp(board, point, dir, line, backLine);
	return (ret);
}

int		Heuristic::simpleSearchPatternsCmp(Board &board,
	t_vec2 point, t_dir dir, char *line, char *backLine)
{
	int				ret = 0;

	if (dir < BOTTOM)
	{
		if (strncmp(line, "010", 3) == 0)
		{
			// std::cout << "- FREE ONE" << std::endl;
			ret += FREE_ONE;
		}
		else if (strncmp(line, "210", 3) == 0
			|| strncmp(line, "012", 3) == 0)
		{
			// std::cout << "- ONE" << std::endl;
			ret += ONE;
		}
		if (strncmp(line, "0110", 4) == 0)
		{
			// std::cout << "- STRAIGHT TWO" << std::endl;
			ret += STRAIGHT_TWO;
		}
		else if (strncmp(line, "2110", 4) == 0
			|| strncmp(line, "0112", 4) == 0)
		{
			// std::cout << "- TWO" << std::endl;
			ret += TWO;
		}
	}
	return (ret);
}
