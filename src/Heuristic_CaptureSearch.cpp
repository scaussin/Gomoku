#include "../includes/Gomoku.hpp"

int		Heuristic::captureSearchPatterns(Board &board,
	t_vec2 point, t_Color playerColor, t_dir dir, char *line, char *backLine)
{
	int				ret = 0;
	t_Color			enemyColor;

	enemyColor = Tools::inverseColorPlayer(playerColor);

	// ATTACK CAPTURE - I can capture
	if (strncmp(line, "1220", 4) == 0)
	{
		ret += ATTACK_CAPTURE_FORM;
		if (enemyColor == WHITE)
		{
			ret *= (board.WhiteCaptures + 1);
		}
		else 
		{
			ret *= (board.BlackCaptures + 1);
		}
	}

	return (ret);
}
