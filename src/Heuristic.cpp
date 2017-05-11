#include "../includes/Gomoku.hpp"

double time_victorySearchPatterns = 0;
double time_simpleSearchPatterns = 0;
double time_threatSpaceSearchPatterns = 0;
double time_captureSearchPatterns = 0;
double time_GetPatternPointsLine = 0;

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
	char				curStone;

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
			curStone = board.getPoint(curPoint);
			//if ((t_Color)board.getPoint(curPoint) != NONE && (t_Color)board.getPoint(curPoint) != SUGGESTION)
			if (curStone == BLACK || curStone == WHITE)
			{
				for (dir = 1; dir != 9; ++dir)
				{
					// from the curPoint, we get the 7 values on the line, and the 7 values on the behind.
					// /**/int start_GetPatternPointsLine = clock();
					Tools::GetDualPatternPointsLine(&(line[0]), &(backLine[0]), board, curPoint, (t_dir)dir, 7, playerColor);
					// Tools::GetPatternPointsLine(&(backLine[0]), board, curPoint, Tools::GetOppositeDir((t_dir)dir), 7, playerColor);
					// /**/time_GetPatternPointsLine += (clock() - start_GetPatternPointsLine) / double(CLOCKS_PER_SEC) * 1000;
					

					// Here we add our different heuristic search patterns to the board's value.
					// /**/int start_victorySearchPatterns = clock();
					boardValue += victorySearchPatterns(board,
									curPoint, playerColor, (t_dir)dir,
									line, backLine);
					// /**/time_victorySearchPatterns += (clock() - start_victorySearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
					
					// /**/int start_simpleSearchPatterns = clock();
					boardValue += simpleSearchPatterns(board,
									curPoint, playerColor, (t_dir)dir,
									line, backLine);
					// /**/time_simpleSearchPatterns += (clock() - start_simpleSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
								
					// /**/int start_threatSpaceSearchPatterns = clock();
					boardValue += threatSpaceSearchPatterns(board,
									curPoint, playerColor, (t_dir)dir,
									line, backLine);
					// /**/time_threatSpaceSearchPatterns += (clock() - start_threatSpaceSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
					
					// /**/int start_captureSearchPatterns = clock();
					boardValue += captureSearchPatterns(board,
									curPoint, playerColor, (t_dir)dir,
									line, backLine);
					// /**/time_captureSearchPatterns += (clock() - start_captureSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;

					// OPPOSITE SIDE
					// /**/start_GetPatternPointsLine = clock();
					// Tools::GetPatternPointsLine(&(line[0]), board, curPoint, (t_dir)dir, 7, enemy_color);
					// Tools::GetPatternPointsLine(&(backLine[0]), board, curPoint, Tools::GetOppositeDir((t_dir)dir), 7, enemy_color);

					Tools::ReversePatternColors(&(line[0]), &(backLine[0]), 7);
					// /**/time_GetPatternPointsLine += (clock() - start_GetPatternPointsLine) / double(CLOCKS_PER_SEC) * 1000;
					// Here we add our different heuristic search patterns to the board's value.

					// /**/start_victorySearchPatterns = clock();
					boardValue -= victorySearchPatterns(board,
									curPoint, enemy_color, (t_dir)dir,
									line, backLine);
					// /**/time_victorySearchPatterns += (clock() - start_victorySearchPatterns) / double(CLOCKS_PER_SEC) * 1000;

					// /**/start_simpleSearchPatterns = clock();
					boardValue -= simpleSearchPatterns(board,
									curPoint, enemy_color, (t_dir)dir,
									line, backLine);
					// /**/time_simpleSearchPatterns += (clock() - start_simpleSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
					
					// /**/start_threatSpaceSearchPatterns = clock();
					boardValue -= threatSpaceSearchPatterns(board,
									curPoint, enemy_color, (t_dir)dir,
									line, backLine);
					// /**/time_threatSpaceSearchPatterns += (clock() - start_threatSpaceSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
					
					// /**/start_captureSearchPatterns = clock();
					boardValue -= captureSearchPatterns(board,
									curPoint, enemy_color, (t_dir)dir,
									line, backLine);
					// /**/time_captureSearchPatterns += (clock() - start_captureSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
				}
			}
		}
	}
	return (boardValue);
}

// TODO: multithread / buffer for each dir.
// int		Heuristic::EvaluateOneDir(Board &board, t_Color playerColor, t_vec2 curPoint, t_dir dir, char *line, char *backLine)
// {

// }
