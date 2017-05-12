#include "../includes/Gomoku.hpp"

double time_victorySearchPatterns = 0;
double time_simpleSearchPatterns = 0;
double time_threatSpaceSearchPatterns = 0;
double time_captureSearchPatterns = 0;
double time_GetPatternPointsLine = 0;
double time_EvaluateBoard = 0;

// --------------------------------------------------------	//
//															//
//	Main Heuristic Function.								//
//	Returns a int heuristic value.							//
//															//
// --------------------------------------------------------	//

int		Heuristic::EvaluateBoard(Board &board, t_Color playerColor)
{
	int start_EvaluateBoard = clock(); //time
	// the return value.
	int					boardValue = 0;

	// board run through variables.
	static int			dir;
	//static int			x;
	//static int			y;
	//static t_vec2		curPoint;
	//char				curStone;
	int start_GetPatternPointsLine; //time
	// int start_victorySearchPatterns; //time
	// int start_simpleSearchPatterns; //time
	// int start_threatSpaceSearchPatterns; //time
	// int start_captureSearchPatterns; //time

	t_Color				enemy_color;

	static char			line[7];
	static char			backLine[7];

	// Here, we will run through each point, and for each point, we will
	// look into every direction.
	enemy_color = Tools::inverseColorPlayer(playerColor);

	for (vector<t_vec2>::iterator it = board.points.begin() ; it != board.points.end() ; ++it)
	{
		for (dir = 1; dir != 9; ++dir)
		{
			// from the curPoint, we get the 7 values on the line, and the 7 values on the behind.
			start_GetPatternPointsLine = clock(); //time
			Tools::GetPatternPointsLine(&(line[0]), board, *it, (t_dir)dir, 7, playerColor);
			Tools::GetPatternPointsLine(&(backLine[0]), board, *it, Tools::GetOppositeDir((t_dir)dir), 7, playerColor);
			time_GetPatternPointsLine += (clock() - start_GetPatternPointsLine) / double(CLOCKS_PER_SEC) * 1000; //time
			

			// Here we add our different heuristic search patterns to the board's value.
			// start_victorySearchPatterns = clock(); //time
			boardValue += victorySearchPatterns(board,
							*it, playerColor, (t_dir)dir,
							line, backLine);
			// time_victorySearchPatterns += (clock() - start_victorySearchPatterns) / double(CLOCKS_PER_SEC) * 1000; //time
			
			// start_simpleSearchPatterns = clock(); //time
			boardValue += simpleSearchPatterns(board,
							*it, playerColor, (t_dir)dir,
							line, backLine);
			// time_simpleSearchPatterns += (clock() - start_simpleSearchPatterns) / double(CLOCKS_PER_SEC) * 1000; //time
						
			// start_threatSpaceSearchPatterns = clock(); //time
			boardValue += threatSpaceSearchPatterns(board,
							*it, playerColor, (t_dir)dir,
							line, backLine);
			// time_threatSpaceSearchPatterns += (clock() - start_threatSpaceSearchPatterns) / double(CLOCKS_PER_SEC) * 1000; //time
			
			// start_captureSearchPatterns = clock(); //time
			boardValue += captureSearchPatterns(board,
							*it, playerColor, (t_dir)dir,
							line, backLine);
			// time_captureSearchPatterns += (clock() - start_captureSearchPatterns) / double(CLOCKS_PER_SEC) * 1000; //time

			// OPPOSITE SIDE
			start_GetPatternPointsLine = clock(); //time
			Tools::GetPatternPointsLine(&(line[0]), board, *it, (t_dir)dir, 7, enemy_color);
			Tools::GetPatternPointsLine(&(backLine[0]), board, *it, Tools::GetOppositeDir((t_dir)dir), 7, enemy_color);
			time_GetPatternPointsLine += (clock() - start_GetPatternPointsLine) / double(CLOCKS_PER_SEC) * 1000; //time
			// Here we add our different heuristic search patterns to the board's value.

			// start_victorySearchPatterns = clock(); //time
			boardValue -= victorySearchPatterns(board,
							*it, enemy_color, (t_dir)dir,
							line, backLine);
			// time_victorySearchPatterns += (clock() - start_victorySearchPatterns) / double(CLOCKS_PER_SEC) * 1000; //time

			// start_simpleSearchPatterns = clock(); //time
			boardValue -= simpleSearchPatterns(board,
							*it, enemy_color, (t_dir)dir,
							line, backLine);
			// time_simpleSearchPatterns += (clock() - start_simpleSearchPatterns) / double(CLOCKS_PER_SEC) * 1000; //time
			
			// start_threatSpaceSearchPatterns = clock(); //time
			boardValue -= threatSpaceSearchPatterns(board,
							*it, enemy_color, (t_dir)dir,
							line, backLine);
			// time_threatSpaceSearchPatterns += (clock() - start_threatSpaceSearchPatterns) / double(CLOCKS_PER_SEC) * 1000; //time
			
			// start_captureSearchPatterns = clock(); //time
			boardValue -= captureSearchPatterns(board,
							*it, enemy_color, (t_dir)dir,
							line, backLine);
			// time_captureSearchPatterns += (clock() - start_captureSearchPatterns) / double(CLOCKS_PER_SEC) * 1000; //time
		}
	}
	time_EvaluateBoard += (clock() - start_EvaluateBoard) / double(CLOCKS_PER_SEC) * 1000; //time
	return (boardValue);
}

// TODO: multithread / buffer for each dir.
// int		Heuristic::EvaluateOneDir(Board &board, t_Color playerColor, t_vec2 *it, t_dir dir, char *line, char *backLine)
// {

// }
