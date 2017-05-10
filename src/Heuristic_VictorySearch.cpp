#include "../includes/Gomoku.hpp"

int		Heuristic::victorySearchPatterns(Board &board,
									t_vec2 point, t_Color playerColor, t_dir dir,
									char *line, char *backLine)
{
	int					ret = 0;

	// search capture forms variables.
	t_vec2				curPoint;
	int					inner_dir;
	int					mod_x;
	int					mod_y;
	int					i;
	char				inner_line[3];
	char				inner_backline[3];

	if (strncmp(line, "11111", 5) == 0)
	{
		Tools::SetMoveModifiers(mod_x, mod_y, (t_dir)dir);
		for (i = 0; i < 5; ++i)
		{
			curPoint.x = point.x + mod_x * i;
			curPoint.y = point.y + mod_y * i;
			for (inner_dir = 1; inner_dir != 5; ++inner_dir)
			{
				Tools::GetPatternPointsLine(inner_line, board, curPoint, (t_dir)inner_dir, 3, playerColor);
				Tools::GetPatternPointsLine(inner_backline, board, curPoint, Tools::GetOppositeDir((t_dir)inner_dir), 3, playerColor);
				if (isBlackStoneCapturable(board, curPoint, (t_dir)inner_dir, inner_line, inner_backline) == true)
				{
					// std::cout << KGRN "- VICTORY CAPTURABLE BLACK FORM" KRESET << std::endl;
					ret += VICTORY_CAPTURABLE;
					return (ret);
				}
			}
		}
		// std::cout << KGRN "- VICTORY BLACK FORM" KRESET << std::endl;
		ret += SURE_VICTORY;
		board.isVictory = true;
	}
	return (ret);
}

bool	Heuristic::isBlackStoneCapturable(Board &board,
						t_vec2 stone, t_dir dir,
						char *line, char *backLine)
{
	if (strncmp(line, "112", 3) == 0
		&& strncmp(backLine, "10", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line, "110", 3) == 0
		&& strncmp(backLine, "12", 2) == 0)
	{
		return (true);
	}
	return (false);
}

bool	Heuristic::isWhiteStoneCapturable(Board &board,
						t_vec2 stone, t_dir dir,
						char *line, char *backLine)
{
	if (strncmp(line, "221", 3) == 0
		&& strncmp(backLine, "20", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line, "220", 3) == 0
		&& strncmp(backLine, "21", 2) == 0)
	{
		return (true);
	}
	return (false);
}