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
	// int start_GetPatternPointsLine; //time
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
			// we seek patterns on lines in every directions
			// from the curPoint, we get the 7 values on the line, and the 7 values on the behind.
			// /**/int start_GetPatternPointsLine = clock();
			Tools::GetDualPatternPointsLine(&(line[0]), &(backLine[0]), board, *it, (t_dir)dir, 7, playerColor);
			// /**/time_GetPatternPointsLine += (clock() - start_GetPatternPointsLine) / double(CLOCKS_PER_SEC) * 1000;
			

			// Here we add our different heuristic search patterns to the board's value.
			// /**/int start_victorySearchPatterns = clock();
			boardValue += victorySearchPatterns(board,
							*it, playerColor, (t_dir)dir,
							line, backLine);
			// /**/time_victorySearchPatterns += (clock() - start_victorySearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
			
			// /**/int start_simpleSearchPatterns = clock();
			boardValue += simpleSearchPatterns(board,
							*it, playerColor, (t_dir)dir,
							line, backLine);
			// /**/time_simpleSearchPatterns += (clock() - start_simpleSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
						
			// /**/int start_threatSpaceSearchPatterns = clock();
			boardValue += threatSpaceSearchPatterns(board,
							*it, playerColor, (t_dir)dir,
							line, backLine);
			// /**/time_threatSpaceSearchPatterns += (clock() - start_threatSpaceSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
			
			// /**/int start_captureSearchPatterns = clock();
			boardValue += captureSearchPatterns(board,
							*it, playerColor, (t_dir)dir,
							line, backLine);
			// /**/time_captureSearchPatterns += (clock() - start_captureSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;

			// OPPOSITE SIDE
			// /**/start_GetPatternPointsLine = clock();
			Tools::ReversePatternColors(&(line[0]), &(backLine[0]), 7);
			// /**/time_GetPatternPointsLine += (clock() - start_GetPatternPointsLine) / double(CLOCKS_PER_SEC) * 1000;
			// Here we add our different heuristic search patterns to the board's value.

			// /**/start_victorySearchPatterns = clock();
			boardValue -= victorySearchPatterns(board,
							*it, enemy_color, (t_dir)dir,
							line, backLine);
			// /**/time_victorySearchPatterns += (clock() - start_victorySearchPatterns) / double(CLOCKS_PER_SEC) * 1000;

			// /**/start_simpleSearchPatterns = clock();
			boardValue -= simpleSearchPatterns(board,
							*it, enemy_color, (t_dir)dir,
							line, backLine);
			// /**/time_simpleSearchPatterns += (clock() - start_simpleSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
			
			// /**/start_threatSpaceSearchPatterns = clock();
			boardValue -= threatSpaceSearchPatterns(board,
							*it, enemy_color, (t_dir)dir,
							line, backLine);
			// /**/time_threatSpaceSearchPatterns += (clock() - start_threatSpaceSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
			
			// /**/start_captureSearchPatterns = clock();
			boardValue -= captureSearchPatterns(board,
							*it, enemy_color, (t_dir)dir,
							line, backLine);
			// /**/time_captureSearchPatterns += (clock() - start_captureSearchPatterns) / double(CLOCKS_PER_SEC) * 1000;
		}
	}
	time_EvaluateBoard += (clock() - start_EvaluateBoard) / double(CLOCKS_PER_SEC) * 1000; //time
	return (boardValue);
}

// --------------------------------------------------------	//
//															//
//	Light pre Heuristic Function.							//
//	Returns a int heuristic value for the last move			//
//	of the board. Light and fast!							//
//															//
// --------------------------------------------------------	//

int		Heuristic::PreEvaluateBoard(Board &board, t_Color playerColor)
{
	// the return value.
	int					boardValue = 0;
	static char			line[7];
	static char			backLine[7];
	static int			dir;

	for (dir = 1; dir != 9; ++dir)
	{
		Tools::GetDualPatternPointsLine(&(line[0]), &(backLine[0]), board, board.lastMove, (t_dir)dir, 7, playerColor);
		boardValue += victorySimpleSearchPatterns(board, board.lastMove, playerColor, (t_dir)dir, line, backLine);
		boardValue += threatSpaceSearchPatterns(board, board.lastMove, playerColor, (t_dir)dir, line, backLine);
		boardValue += captureSearchPatterns(board, board.lastMove, playerColor, (t_dir)dir, line, backLine);
	}
	return (boardValue);
}

