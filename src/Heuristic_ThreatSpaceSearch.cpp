#include "../includes/Gomoku.hpp"

int		Heuristic::threatSpaceSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (strncmp(line.c_str(), "211110", 6) == 0)
	{
		std::cout << KMAG "- FOUR" KRESET << std::endl;
		ret += FOUR;
	}
	if (strncmp(line.c_str(), "011112", 6) == 0)
	{
		std::cout << KMAG "- FOUR (REVERSED)" KRESET << std::endl;
		ret += FOUR;
	}
	else if (strncmp(line.c_str(), "011110", 6) == 0)
	{
		std::cout << KMAG "- STRAIGHT FOUR" KRESET << std::endl;
		ret += STRAIGHT_FOUR;
	}
	else if (strncmp(line.c_str(), "0011100", 7) == 0)
	{
		std::cout << KMAG "- THREE (7 points)" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line.c_str(), "001110", 6) == 0
		|| strncmp(line.c_str(), "011100", 6) == 0)
	{
		std::cout << KMAG "- THREE (6 points)" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line.c_str(), "010110", 6) == 0
		&& strncmp(backLine.c_str(), "010110", 6) != 0) // two facing broken threes are defendable.
	{
		std::cout << KMAG "- BROKEN THREE" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line.c_str(), "011010", 6) == 0
		&& strncmp(backLine.c_str(), "011010", 6) != 0) // idem.
	{
		std::cout << KMAG "- BROKEN THREE (REVERSED)" KRESET << std::endl;
		ret += THREE;
	}
	return (ret);
}
