#include "../includes/Gomoku.hpp"

int		Heuristic::simpleSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, char *line, char *backLine)
{
	int				ret = 0;

	if (dir < BOTTOM)
	{
		if (strncmp(line, "10", 2) == 0
			&& strncmp(backLine, "10", 2) == 0)
		{
			// std::cout << "- FREE ONE" << std::endl;
			ret += FREE_ONE;
		}
		else if ((strncmp(line, "12", 2) == 0 && strncmp(backLine, "10", 2) == 0)
			|| (strncmp(line, "10", 2) == 0 && strncmp(backLine, "12", 2) == 0))
		{
			// std::cout << "- ONE" << std::endl;
			ret += ONE;
		}
		if ((strncmp(line, "110", 3) == 0 && strncmp(backLine, "10", 2) == 0)
			|| (strncmp(line, "10", 2) == 0 && strncmp(backLine, "110", 3) == 0))
		{
			// std::cout << "- STRAIGHT TWO" << std::endl;
			ret += STRAIGHT_TWO;
		}
		else if (strncmp(line, "2110", 4) == 0
			|| strncmp(backLine, "2110", 4) == 0)
		{
			// std::cout << "- TWO" << std::endl;
			ret += TWO;
		}
	}
	return (ret);
}
