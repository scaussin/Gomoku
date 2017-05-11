#include "../includes/Gomoku.hpp"

int		Heuristic::threatSpaceSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, char *line, char *backLine)
{
	int				ret = 0;

	if (strncmp(line, "11110", 5) == 0 && strncmp(backLine, "12", 2) == 0)
	{
		// std::cout << KMAG "- FOUR" KRESET << std::endl;
		ret += FOUR;
	}
	else if (strncmp(line, "11110", 5) == 0 && strncmp(backLine, "10", 2) == 0)
	{
		// std::cout << KMAG "- STRAIGHT FOUR" KRESET << std::endl;
		ret += STRAIGHT_FOUR;
	}
	else if (strncmp(line, "1100", 4) == 0 && strncmp(backLine, "1100", 4) == 0)
	{
		// std::cout << KMAG "- THREE (2-2 opened)" KRESET << std::endl;
		ret += STRAIGHT_THREE;
	}
	else if ((strncmp(line, "1102", 4) == 0 && strncmp(backLine, "1100", 4) == 0)
		|| (strncmp(line, "1100", 4) == 0 && strncmp(backLine, "1102", 4) == 0)
		|| (strncmp(line, "1110", 4) == 0 && strncmp(backLine, "12", 2) == 0))
	{
		// std::cout << KMAG "- THREE (1-2 opened)" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line, "10110", 5) == 0 && strncmp(backLine, "100", 3) == 0) // two facing broken threes are defendable.
	{
		// std::cout << KMAG "- BROKEN THREE" KRESET << std::endl;
		ret += BROKEN_THREE;
	}
	else if (strncmp(line, "11010", 5) == 0 && strncmp(backLine, "100", 3) == 0) // idem.
	{
		// std::cout << KMAG "- BROKEN THREE (REVERSED)" KRESET << std::endl;
		ret += BROKEN_THREE;
	}
	else if (strncmp(line, "111010", 6) == 0 && strncmp(backLine, "10", 2) == 0)
	{
		ret += BROKEN_FOUR;
	}
	return (ret);
}
