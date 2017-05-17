#include "../includes/Gomoku.hpp"

int		Heuristic::captureSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, char *line, char *backLine)
{
	int				ret = 0;

	// ATTACK CAPTURE - I can capture
	if (strncmp(line, "1220", 4) == 0)
	{
		ret += ATTACK_CAPTURE_FORM;
		if (playerColor == BLACK)
		{
			if (board.BlackCaptures == 8)
				ret += VICTORY_CAPTURE_FORM;
		}
		else
		{
			if (board.WhiteCaptures == 8)
				ret += VICTORY_CAPTURE_FORM;
		}
	}
	return (ret);
}

int		Heuristic::captureSimpleSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, char *line)
{
	int				ret = 0;

	// ATTACK CAPTURE - I can capture
	if (strncmp(line, "1220", 4) == 0)
	{
		ret += ATTACK_CAPTURE_FORM;
	}
	return (ret);
}
