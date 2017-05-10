#include "../includes/Gomoku.hpp"

// --------------------------------------------------------	//
//															//
//	Main Heuristic Function.								//
//	Returns a int heuristic value.							//
//															//
// --------------------------------------------------------	//

static ThreadPool	g_ThreadPool;

int		Heuristic::EvaluateBoard(Board &board, t_Color playerColor)
{
	// the return value.
	int					boardValue = 0;

	// board run through variables.
	// static int			dir = 1;
	static int			x;
	static int			y;
	static int			i;
	static t_vec2		curPoint;

	int 				boardValues[361];

	// t_Color				enemy_color;

	// int					dirBoardValues[8];

	// static char			line[7];
	// static char			backLine[7];

	// Here, we will run through each point, and for each point, we will
	// look into every direction.
	
	for (i = 0; i < 361; ++i)
	{
		boardValues[i] = 0;
	}
	i = 0;
	for (y = 0; y < 19; ++y)
	{
		for (x = 0; x < 19; ++x, ++i)
		{
			curPoint.x = x;
			curPoint.y = y;
			// we seek patterns on lines in every directions
			// dir = 1;
			if ((t_Color)board.getPoint(curPoint) != NONE && (t_Color)board.getPoint(curPoint) != SUGGESTION)
			{
				// g_ThreadPool.AddHeuristicReadlineTask(&board, &playerColor, &curPoint, &dir, &(dirBoardValues[0]));
				// g_ThreadPool.AddHeuristicReadlineTask(&board, &playerColor, &curPoint, &dir, &(dirBoardValues[1]));
				// g_ThreadPool.AddHeuristicReadlineTask(&board, &playerColor, &curPoint, &dir, &(dirBoardValues[2]));
				// g_ThreadPool.AddHeuristicReadlineTask(&board, &playerColor, &curPoint, &dir, &(dirBoardValues[3]));
				// g_ThreadPool.AddHeuristicReadlineTask(&board, &playerColor, &curPoint, &dir, &(dirBoardValues[4]));
				// g_ThreadPool.AddHeuristicReadlineTask(&board, &playerColor, &curPoint, &dir, &(dirBoardValues[5]));
				// g_ThreadPool.AddHeuristicReadlineTask(&board, &playerColor, &curPoint, &dir, &(dirBoardValues[6]));
				// g_ThreadPool.AddHeuristicReadlineTask(&board, &playerColor, &curPoint, &dir, &(dirBoardValues[7]));
				g_ThreadPool.AddHeuristicTask(&board, &playerColor, &curPoint, &(boardValues[i]));

				// g_ThreadPool.ClearTasks();
				// std::thread dir1(EvaluateOneDir, &board, &playerColor, &curPoint, (t_dir)dir, &(dirBoardValues[0]));
				// std::thread dir2(EvaluateOneDir, &board, &playerColor, &curPoint, (t_dir)dir + 1, &(dirBoardValues[1]));
				// std::thread dir3(EvaluateOneDir, &board, &playerColor, &curPoint, (t_dir)dir + 2, &(dirBoardValues[2]));
				// std::thread dir4(EvaluateOneDir, &board, &playerColor, &curPoint, (t_dir)dir + 3, &(dirBoardValues[3]));
				// std::thread dir5(EvaluateOneDir, &board, &playerColor, &curPoint, (t_dir)dir + 4, &(dirBoardValues[4]));
				// std::thread dir6(EvaluateOneDir, &board, &playerColor, &curPoint, (t_dir)dir + 5, &(dirBoardValues[5]));
				// std::thread dir7(EvaluateOneDir, &board, &playerColor, &curPoint, (t_dir)dir + 6, &(dirBoardValues[6]));
				// std::thread dir8(EvaluateOneDir, &board, &playerColor, &curPoint, (t_dir)dir + 7, &(dirBoardValues[7]));

				// dir1.join();
				// dir2.join();
				// dir3.join();
				// dir4.join();
				// dir5.join();
				// dir6.join();
				// dir7.join();
				// dir8.join();

				
				// for (dir = 1; dir != 9; ++dir)
				// {
				// 	// from the curPoint, we get the 7 values on the line, and the 7 values on the behind.
				// 	Tools::GetPatternPointsLine(&(line[0]), board, curPoint, (t_dir)dir, 7, playerColor);
				// 	Tools::GetPatternPointsLine(&(backLine[0]), board, curPoint, Tools::GetOppositeDir((t_dir)dir), 7, playerColor);
					

				// 	// Here we add our different heuristic search patterns to the board's value.

				// 	boardValue += victorySearchPatterns(board,
				// 					curPoint, playerColor, (t_dir)dir,
				// 					line, backLine);

				// 	boardValue += simpleSearchPatterns(board,
				// 					curPoint, playerColor, (t_dir)dir,
				// 					line, backLine);
					
				// 	boardValue += threatSpaceSearchPatterns(board,
				// 					curPoint, playerColor, (t_dir)dir,
				// 					line, backLine);
					
				// 	boardValue += captureSearchPatterns(board,
				// 					curPoint, playerColor, (t_dir)dir,
				// 					line, backLine);

				// 	// OPPOSITE SIDE
				// 	Tools::GetPatternPointsLine(&(line[0]), board, curPoint, (t_dir)dir, 7, enemy_color);
				// 	Tools::GetPatternPointsLine(&(backLine[0]), board, curPoint, Tools::GetOppositeDir((t_dir)dir), 7, enemy_color);
				// 	// Here we add our different heuristic search patterns to the board's value.

				// 	boardValue -= victorySearchPatterns(board,
				// 					curPoint, enemy_color, (t_dir)dir,
				// 					line, backLine);

				// 	boardValue -= simpleSearchPatterns(board,
				// 					curPoint, enemy_color, (t_dir)dir,
				// 					line, backLine);
					
				// 	boardValue -= threatSpaceSearchPatterns(board,
				// 					curPoint, enemy_color, (t_dir)dir,
				// 					line, backLine);
					
				// 	boardValue -= captureSearchPatterns(board,
				// 					curPoint, enemy_color, (t_dir)dir,
				// 					line, backLine);

				// }
			}
		}
	}
	while (g_ThreadPool.WaitForTasks() == false)
	{

	}
	for (i = 0; i < 361; ++i)
	{
		boardValue += boardValues[i];
	}
	return (boardValue);
}

// multithread / buffer for each dir.
// void		Heuristic::EvaluateOneDir(Board *board, t_Color *playerColor, t_vec2 *curPoint, t_dir dir, int *retval)
// {
// 	char			line[7];
// 	char			backLine[7];
// 	t_Color			enemy_color;

// 	enemy_color = Tools::inverseColorPlayer(*playerColor);
// 	Tools::GetPatternPointsLine(&(line[0]), *board, *curPoint, dir, 7, *playerColor);
// 	Tools::GetPatternPointsLine(&(backLine[0]), *board, *curPoint, Tools::GetOppositeDir(dir), 7, *playerColor);
	

// 	// Here we add our different heuristic search patterns to the board's value.

// 	retval += victorySearchPatterns(*board,
// 					*curPoint, *playerColor, dir,
// 					line, backLine);

// 	retval += simpleSearchPatterns(*board,
// 					*curPoint, *playerColor, dir,
// 					line, backLine);
	
// 	retval += threatSpaceSearchPatterns(*board,
// 					*curPoint, *playerColor, dir,
// 					line, backLine);
	
// 	retval += captureSearchPatterns(*board,
// 					*curPoint, *playerColor, dir,
// 					line, backLine);

// 	// OPPOSITE SIDE
// 	Tools::GetPatternPointsLine(&(line[0]), *board, *curPoint, dir, 7, enemy_color);
// 	Tools::GetPatternPointsLine(&(backLine[0]), *board, *curPoint, Tools::GetOppositeDir(dir), 7, enemy_color);
// 	// Here we add our different heuristic search patterns to the board's value.

// 	retval -= victorySearchPatterns(*board,
// 					*curPoint, enemy_color, dir,
// 					line, backLine);

// 	retval -= simpleSearchPatterns(*board,
// 					*curPoint, enemy_color, dir,
// 					line, backLine);
	
// 	retval -= threatSpaceSearchPatterns(*board,
// 					*curPoint, enemy_color, dir,
// 					line, backLine);

// 	retval -= captureSearchPatterns(*board,
// 					*curPoint, enemy_color, dir,
// 					line, backLine);

// }

void		Heuristic::EvaluateAllDir(Board *board, t_Color *playerColor, t_vec2 *curPoint, int *retval)
{
	char			line[7];
	char			backLine[7];
	t_Color			enemy_color;
	int				dir = 1;

	while (dir != 9)
	{
		enemy_color = Tools::inverseColorPlayer(*playerColor);
		Tools::GetPatternPointsLine(&(line[0]), *board, *curPoint, (t_dir)dir, 7, *playerColor);
		Tools::GetPatternPointsLine(&(backLine[0]), *board, *curPoint, Tools::GetOppositeDir((t_dir)dir), 7, *playerColor);
		

		// Here we add our different heuristic search patterns to the board's value.

		*retval += victorySearchPatterns(*board,
						*curPoint, *playerColor, (t_dir)dir,
						&(line[0]), &(backLine[0]));

		*retval += simpleSearchPatterns(*board,
						*curPoint, *playerColor, (t_dir)dir,
						&(line[0]), &(backLine[0]));
		
		*retval += threatSpaceSearchPatterns(*board,
						*curPoint, *playerColor, (t_dir)dir,
						&(line[0]), &(backLine[0]));
		
		*retval += captureSearchPatterns(*board,
						*curPoint, *playerColor, (t_dir)dir,
						&(line[0]), &(backLine[0]));

		// OPPOSITE SIDE
		Tools::GetPatternPointsLine(&(line[0]), *board, *curPoint, (t_dir)dir, 7, enemy_color);
		Tools::GetPatternPointsLine(&(backLine[0]), *board, *curPoint, Tools::GetOppositeDir((t_dir)dir), 7, enemy_color);
		// Here we add our different heuristic search patterns to the board's value.

		*retval -= victorySearchPatterns(*board,
						*curPoint, enemy_color, (t_dir)dir,
						&(line[0]), &(backLine[0]));

		*retval -= simpleSearchPatterns(*board,
						*curPoint, enemy_color, (t_dir)dir,
						&(line[0]), &(backLine[0]));
		
		*retval -= threatSpaceSearchPatterns(*board,
						*curPoint, enemy_color, (t_dir)dir,
						&(line[0]), &(backLine[0]));
		
		*retval -= captureSearchPatterns(*board,
						*curPoint, enemy_color, (t_dir)dir,
						&(line[0]), &(backLine[0]));
		dir++;
	}
}

void		Heuristic::EvaluateOneDir(Board *board, t_Color *playerColor, t_vec2 *curPoint, int *dir, int *retval)
{
	char			line[7];
	char			backLine[7];
	t_Color			enemy_color;

	enemy_color = Tools::inverseColorPlayer(*playerColor);
	Tools::GetPatternPointsLine(&(line[0]), *board, *curPoint, (t_dir)(*dir), 7, *playerColor);
	Tools::GetPatternPointsLine(&(backLine[0]), *board, *curPoint, Tools::GetOppositeDir((t_dir)(*dir)), 7, *playerColor);
	

	// Here we add our different heuristic search patterns to the board's value.

	*retval += victorySearchPatterns(*board,
					*curPoint, *playerColor, (t_dir)(*dir),
					&(line[0]), &(backLine[0]));

	*retval += simpleSearchPatterns(*board,
					*curPoint, *playerColor, (t_dir)(*dir),
					&(line[0]), &(backLine[0]));
	
	*retval += threatSpaceSearchPatterns(*board,
					*curPoint, *playerColor, (t_dir)(*dir),
					&(line[0]), &(backLine[0]));
	
	*retval += captureSearchPatterns(*board,
					*curPoint, *playerColor, (t_dir)(*dir),
					&(line[0]), &(backLine[0]));

	// OPPOSITE SIDE
	Tools::GetPatternPointsLine(&(line[0]), *board, *curPoint, (t_dir)(*dir), 7, enemy_color);
	Tools::GetPatternPointsLine(&(backLine[0]), *board, *curPoint, Tools::GetOppositeDir((t_dir)(*dir)), 7, enemy_color);
	// Here we add our different heuristic search patterns to the board's value.

	*retval -= victorySearchPatterns(*board,
					*curPoint, enemy_color, (t_dir)(*dir),
					&(line[0]), &(backLine[0]));

	*retval -= simpleSearchPatterns(*board,
					*curPoint, enemy_color, (t_dir)(*dir),
					&(line[0]), &(backLine[0]));
	
	*retval -= threatSpaceSearchPatterns(*board,
					*curPoint, enemy_color, (t_dir)(*dir),
					&(line[0]), &(backLine[0]));
	
	*retval -= captureSearchPatterns(*board,
					*curPoint, enemy_color, (t_dir)(*dir),
					&(line[0]), &(backLine[0]));


}
