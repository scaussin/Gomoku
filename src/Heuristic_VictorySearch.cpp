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

	// search capture forms variables.
	t_vec2			curPoint;
	int				inner_dir;
	int				mod_x;
	int				mod_y;
	std::string		inner_line;
	std::string		inner_backLine;

	if (strncmp(line.c_str(), "11111", 5) == 0)
	{
		Tools::SetMoveModifiers(mod_x, mod_y, (t_dir)dir);
		for (int i = 0; i < 5; i++)
		{
			curPoint.x = point.x + mod_x * i;
			curPoint.y = point.y + mod_y * i;
			for (inner_dir = 1; inner_dir != 5; inner_dir++)
			{
				inner_line = Tools::GetPointsLine(board, curPoint, (t_dir)inner_dir, 3);
				inner_backLine = Tools::GetPointsLine(board, curPoint, Tools::GetOppositeDir((t_dir)inner_dir), 3);
				if (isBlackStoneCapturable(board, curPoint, (t_dir)inner_dir, inner_line, inner_backLine) == true)
				{
					std::cout << KGRN "- VICTORY CAPTURABLE BLACK FORM" KRESET << std::endl;
					ret += VICTORY_CAPTURABLE;
					return (ret);
				}
			}
		}
		std::cout << KGRN "- VICTORY BLACK FORM" KRESET << std::endl;
		ret += VICTORY;
	}
	return (ret);
}

int		Heuristic::victorySearchPatternsWhite(Board &board,
	t_vec2 point, t_dir dir, std::string &line, std::string &backLine)
{
	int				ret = 0;

	// search capture forms variables.
	t_vec2			curPoint;
	int				inner_dir;
	int				mod_x;
	int				mod_y;
	std::string		inner_line;
	std::string		inner_backLine;

	if (strncmp(line.c_str(), "22222", 5) == 0)
	{
		Tools::SetMoveModifiers(mod_x, mod_y, (t_dir)dir);
		for (int i = 0; i < 5; i++)
		{
			curPoint.x = point.x + mod_x * i;
			curPoint.y = point.y + mod_y * i;
			for (inner_dir = 1; inner_dir != 5; inner_dir++)
			{
				inner_line = Tools::GetPointsLine(board, curPoint, (t_dir)inner_dir, 3);
				inner_backLine = Tools::GetPointsLine(board, curPoint, Tools::GetOppositeDir((t_dir)inner_dir), 3);
				if (isWhiteStoneCapturable(board, curPoint, (t_dir)inner_dir, inner_line, inner_backLine) == true)
				{
					std::cout << KGRN "- VICTORY CAPTURABLE WHITE FORM" KRESET << std::endl;
					ret += VICTORY_CAPTURABLE;
					return (ret);
				}
			}
		}
		std::cout << KGRN "- VICTORY WHITE FORM" KRESET << std::endl;
		ret += VICTORY;
	}
	return (ret);
}

bool	Heuristic::isBlackStoneCapturable(Board &board,
						t_vec2 stone, t_dir dir,
						std::string &line, std::string &backLine)
{
	if (strncmp(line.c_str(), "112", 3) == 0
		&& strncmp(backLine.c_str(), "10", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line.c_str(), "110", 3) == 0
		&& strncmp(backLine.c_str(), "12", 2) == 0)
	{
		return (true);
	}
	return (false);
}

bool	Heuristic::isWhiteStoneCapturable(Board &board,
						t_vec2 stone, t_dir dir,
						std::string &line, std::string &backLine)
{
	if (strncmp(line.c_str(), "221", 3) == 0
		&& strncmp(backLine.c_str(), "20", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line.c_str(), "220", 3) == 0
		&& strncmp(backLine.c_str(), "21", 2) == 0)
	{
		return (true);
	}
	return (false);
}