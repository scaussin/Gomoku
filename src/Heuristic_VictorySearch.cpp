#include "../includes/Gomoku.hpp"

int		Heuristic::victorySearchPatterns(Board &board,
									t_vec2 point, t_Color playerColor, t_dir dir,
									char *line, char *backLine)
{
	int						ret = 0;

	// search capture forms variables.
	static t_vec2			curPoint;
	static int				inner_dir;
	static int				mod_x;
	static int				mod_y;
	static int				i;
	static char				inner_line[3];
	static char				inner_backline[3];

	if (strncmp(line, "11111", 5) == 0)
	{
		Tools::SetMoveModifiers(mod_x, mod_y, (t_dir)dir);
		for (i = 0; i < 5; ++i)
		{
			curPoint.x = point.x + mod_x * i;
			curPoint.y = point.y + mod_y * i;
			for (inner_dir = 1; inner_dir != 9; ++inner_dir)
			{
				Tools::GetDualPatternPointsLine(&(inner_line[0]), &(inner_backline[0]),
						board, curPoint, (t_dir)dir, 3, playerColor);
				if (isBlackStoneCapturable(board, curPoint,
						(t_dir)inner_dir, inner_line, inner_backline) == true)
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

int		Heuristic::victorySimpleSearchPatterns(Board &board,
									t_vec2 point, t_Color playerColor, t_dir dir,
									char *line)
{
	int						ret = 0;

	if (strncmp(line, "11111", 5) == 0)
	{
		ret += 1000;
	}
	return (ret);
}