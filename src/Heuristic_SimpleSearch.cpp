#include "../includes/Gomoku.hpp"

int		Heuristic::simpleSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (playerColor == BLACK)
	{
		ret += simpleSearchPatternsBlack(board, point, dir, line, backLine);
	}
	else
	{
		ret += simpleSearchPatternsWhite(board, point, dir, line, backLine);
	}
	return (ret);
}

int		Heuristic::simpleSearchPatternsBlack(Board &board,
	t_vec2 point, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (dir < BOTTOM)
	{
		if (strncmp(line.c_str(), "010", 3) == 0)
		{
			std::cout << KMAG "- FREE ONE" KRESET << std::endl;
			ret += FREE_ONE;
		}
		else if (strncmp(line.c_str(), "210", 3) == 0
			|| strncmp(line.c_str(), "012", 3) == 0)
		{
			std::cout << KMAG "- ONE" KRESET << std::endl;
			ret += ONE;
		}
		if (strncmp(line.c_str(), "0110", 4) == 0)
		{
			std::cout << KMAG "- STRAIGHT TWO" KRESET << std::endl;
			ret += STRAIGHT_TWO;
		}
		else if (strncmp(line.c_str(), "2110", 4) == 0
			|| strncmp(line.c_str(), "0112", 4) == 0)
		{
			std::cout << KMAG "- TWO" KRESET << std::endl;
			ret += TWO;
		}
	}
	return (ret);
}

int		Heuristic::simpleSearchPatternsWhite(Board &board,
	t_vec2 point, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (dir < BOTTOM)
	{
		if (strncmp(line.c_str(), "020", 3) == 0)
		{
			std::cout << KMAG "- FREE ONE" KRESET << std::endl;
			ret += FREE_ONE;
		}
		else if (strncmp(line.c_str(), "120", 3) == 0
			|| strncmp(line.c_str(), "021", 3) == 0)
		{
			std::cout << KMAG "- ONE" KRESET << std::endl;
			ret += ONE;
		}
		if (strncmp(line.c_str(), "0220", 4) == 0)
		{
			std::cout << KMAG "- STRAIGHT TWO" KRESET << std::endl;
			ret += STRAIGHT_TWO;
		}
		else if (strncmp(line.c_str(), "1220", 4) == 0
			|| strncmp(line.c_str(), "0221", 4) == 0)
		{
			std::cout << KMAG "- TWO" KRESET << std::endl;
			ret += TWO;
		}
	}
	return (ret);
}