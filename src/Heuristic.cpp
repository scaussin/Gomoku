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
	int		boardValue = 0;

	// board run through variables.
	int			dir;
	int			x;
	int			y;
	t_vec2		curPoint;

	std::string	line;
	std::string	backLine;

	// Here, we will run through each point, and for each point, we will
	// look into every direction.
	for (y = 0; y < 19; y++)
	{
		for (x = 0; x < 19; x++)
		{
			curPoint.x = x;
			curPoint.y = y;
			// we seek patterns on lines in every directions
			for (dir = 1; dir != 5; dir++)
			{
				// from the curPoint, we get the 7 values on the line, and the 7 values on the behind.
				line = Tools::GetPointsLine(board, curPoint, (t_dir)dir, 7);
				backLine = Tools::GetPointsLine(board, curPoint, Tools::GetOppositeDir((t_dir)dir), 7);
				// Here we add our different heuristic search patterns to the board's value.

				// TODO: victory search pattern -> +100;
				boardValue += victorySearchPatterns(board,
								curPoint, playerColor, (t_dir)dir,
								line, backLine);

				boardValue += simpleSearchPatterns(board,
								curPoint, playerColor, (t_dir)dir,
								line, backLine);
				
				boardValue += threatSpaceSearchPatterns(board,
								curPoint, playerColor, (t_dir)dir,
								line, backLine);

				// TODO: capturable stones search patterns.
			}
		}
	}
	return (boardValue);
}
