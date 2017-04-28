#include "../includes/Gomoku.hpp"

int		Heuristic::victorySearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir,
	std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (playerColor == BLACK)
	{
		ret += victorySearchPatternsBlack(board, point, dir, line, backLine);
	}
	else
	{
		ret += victorySearchPatternsWhite(board, point, dir, line, backLine);
	}
	return (ret);
}

int		Heuristic::victorySearchPatternsBlack(Board &board,
	t_vec2 point, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (strncmp(line.c_str(), "11111", 5) == 0)
	{
		std::cout << KGRN "- VICTORY BLACK FORM" KRESET << std::endl;
		ret += VICTORY_BASIC_FORM;
	}
	return (ret);
}

int		Heuristic::victorySearchPatternsWhite(Board &board,
	t_vec2 point, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	if (strncmp(line.c_str(), "22222", 5) == 0)
	{
		std::cout << KGRN "- VICTORY WHITE FORM" KRESET << std::endl;
		ret += VICTORY_BASIC_FORM;
	}
	return (ret);
}
