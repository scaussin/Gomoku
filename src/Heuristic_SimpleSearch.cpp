#include "../includes/Gomoku.hpp"

int		Heuristic::simpleSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (dir < BOTTOM) // duos only need one-side check;
	{
		if (strncmp(line.c_str(), "0110", 4) == 0)
		{
			std::cout << KMAG "- STRAIGHT TWO" KRESET << std::endl;
			ret += STRAIGHT_TWO;
		}
		else if (strncmp(line.c_str(), "211", 3) == 0
			|| strncmp(line.c_str(), "112", 3) == 0)
		{
			std::cout << KMAG "- TWO" KRESET << std::endl;
			ret += TWO;
		}
	}
	return (ret);
}