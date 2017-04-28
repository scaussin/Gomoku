#include "../includes/Gomoku.hpp"

int		Heuristic::threatSpaceSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (playerColor == BLACK)
	{
		ret += threatSpaceSearchPatternsBlack(board, point, dir, line, backLine);
	}
	else
	{
		ret += threatSpaceSearchPatternsWhite(board, point, dir, line, backLine);
	}
	return (ret);
}

int		Heuristic::threatSpaceSearchPatternsBlack(Board &board,
	t_vec2 point, t_dir dir, std::string &line, std::string &backLine)
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
		std::cout << KMAG "- THREE (2-2 opened)" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line.c_str(), "0011102", 7) == 0
		|| strncmp(line.c_str(), "2011100", 7) == 0)
	{
		std::cout << KMAG "- THREE (1-2 opened)" KRESET << std::endl;
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

int		Heuristic::threatSpaceSearchPatternsWhite(Board &board,
	t_vec2 point, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (strncmp(line.c_str(), "122220", 6) == 0)
	{
		std::cout << KMAG "- FOUR" KRESET << std::endl;
		ret += FOUR;
	}
	if (strncmp(line.c_str(), "022221", 6) == 0)
	{
		std::cout << KMAG "- FOUR (REVERSED)" KRESET << std::endl;
		ret += FOUR;
	}
	else if (strncmp(line.c_str(), "022220", 6) == 0)
	{
		std::cout << KMAG "- STRAIGHT FOUR" KRESET << std::endl;
		ret += STRAIGHT_FOUR;
	}
	else if (strncmp(line.c_str(), "0022200", 7) == 0)
	{
		std::cout << KMAG "- THREE (2-2 opened)" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line.c_str(), "0022201", 7) == 0
		|| strncmp(line.c_str(), "1022200", 7) == 0)
	{
		std::cout << KMAG "- THREE (1-2 opened)" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line.c_str(), "020220", 6) == 0
		&& strncmp(backLine.c_str(), "020220", 6) != 0) // two facing broken threes are defendable.
	{
		std::cout << KMAG "- BROKEN THREE" KRESET << std::endl;
		ret += THREE;
	}
	else if (strncmp(line.c_str(), "022020", 6) == 0
		&& strncmp(backLine.c_str(), "022020", 6) != 0) // idem.
	{
		std::cout << KMAG "- BROKEN THREE (REVERSED)" KRESET << std::endl;
		ret += THREE;
	}
	return (ret);
}
