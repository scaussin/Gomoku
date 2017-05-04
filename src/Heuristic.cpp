#include "../includes/Gomoku.hpp"

// --------------------------------------------------------	//
//															//
//	Main Heuristic Function.								//
//	Returns a int heuristic value.							//
//															//
// --------------------------------------------------------	//

int		Heuristic::EvaluateBoard(Board &board, t_Color playerColor)
{
	// the return value.
	int					boardValue = 0;

	// board run through variables.
	static int			dir;
	static int			x;
	static int			y;
	static t_vec2		curPoint;

	t_Color				enemy_color;

	static char			line[7];
	static char			backLine[7];

	// Here, we will run through each point, and for each point, we will
	// look into every direction.
	enemy_color = Tools::inverseColorPlayer(playerColor);
	for (y = 0; y < 19; ++y)
	{
		for (x = 0; x < 19; ++x)
		{
			curPoint.x = x;
			curPoint.y = y;
			// we seek patterns on lines in every directions
			for (dir = 1; dir != 5; ++dir)
			{
				// from the curPoint, we get the 7 values on the line, and the 7 values on the behind.
				Tools::GetPatternPointsLine(&(line[0]), board, curPoint, (t_dir)dir, 7, playerColor);
				Tools::GetPatternPointsLine(&(line[0]), board, curPoint, Tools::GetOppositeDir((t_dir)dir), 7, playerColor);
				// Here we add our different heuristic search patterns to the board's value.

				boardValue += victorySearchPatterns(board,
								curPoint, playerColor, (t_dir)dir,
								line, backLine);

				boardValue += simpleSearchPatterns(board,
								curPoint, playerColor, (t_dir)dir,
								line, backLine);
				
				boardValue += threatSpaceSearchPatterns(board,
								curPoint, playerColor, (t_dir)dir,
								line, backLine);
				
				boardValue += captureSearchPatterns(board,
								curPoint, playerColor, (t_dir)dir,
								line, backLine);

				// OPPOSITE SIDE
				Tools::GetPatternPointsLine(&(line[0]), board, curPoint, (t_dir)dir, 7, enemy_color);
				Tools::GetPatternPointsLine(&(line[0]), board, curPoint, Tools::GetOppositeDir((t_dir)dir), 7, enemy_color);
				// Here we add our different heuristic search patterns to the board's value.

				boardValue -= victorySearchPatterns(board,
								curPoint, enemy_color, (t_dir)dir,
								line, backLine);

				boardValue -= simpleSearchPatterns(board,
								curPoint, enemy_color, (t_dir)dir,
								line, backLine);
				
				boardValue -= threatSpaceSearchPatterns(board,
								curPoint, enemy_color, (t_dir)dir,
								line, backLine);
				
				boardValue -= captureSearchPatterns(board,
								curPoint, enemy_color, (t_dir)dir,
								line, backLine);
			}
		}
	}
	return (boardValue);
}
