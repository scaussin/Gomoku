#include "../includes/Gomoku.hpp"

int		Heuristic::threatSpaceSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, char *line, char *backLine)
{
	int				ret = 0;

	ret += threatSpaceSearchPatternsCmp(board, point, dir, line, backLine);
	return (ret);
}

int		Heuristic::threatSpaceSearchPatternsCmp(Board &board,
	t_vec2 point, t_dir dir, char *line, char *backLine)
{
	int				ret = 0;

	if (strncmp(line, "211110", 6) == 0)
	{
		// std::cout << KMAG "- FOUR" KRESET << std::endl;
		ret += FOUR;
	}
	if (strncmp(line, "011112", 6) == 0)
	{
		// std::cout << KMAG "- FOUR (REVERSED)" KRESET << std::endl;
		ret += FOUR;
	}
	else if (strncmp(line, "011110", 6) == 0)
	{
		// std::cout << KMAG "- STRAIGHT FOUR" KRESET << std::endl;
		ret += STRAIGHT_FOUR;
	}
	else if (strncmp(line, "0011100", 7) == 0)
	{
		// std::cout << KMAG "- THREE (2-2 opened)" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line, "0011102", 7) == 0
		|| strncmp(line, "2011100", 7) == 0)
	{
		// std::cout << KMAG "- THREE (1-2 opened)" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line, "010110", 6) == 0
		&& strncmp(backLine, "010110", 6) != 0) // two facing broken threes are defendable.
	{
		// std::cout << KMAG "- BROKEN THREE" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line, "011010", 6) == 0
		&& strncmp(backLine, "011010", 6) != 0) // idem.
	{
		// std::cout << KMAG "- BROKEN THREE (REVERSED)" KRESET << std::endl;
		ret += THREE;
	}
	return (ret);
}
