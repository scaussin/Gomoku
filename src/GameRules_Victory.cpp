#include "../includes/Gomoku.hpp"

/*
**	The method that check the victory for the current game.
**	There are two ways to win : 10 captures, or an alignement of 5.
*/

void	GameRules::CheckVictory(t_GameDatas &GameDatas)
{
	int									dir;
	int									x;
	int									y;
	t_vec2								curPoint;
	char								line[5];

	std::vector<t_VictorySequence>		VictorySequences;

	t_Color								WinnerColor;

	Board &board = GameDatas.Board;
	// Check Victory by capture.
	if (board.BlackCaptures >= 10)
	{
		std::cout << KGRN "BLACK WINS BY CAPTURE" KRESET << std::endl;
		GameDatas.IsGameOver = true;
		GameDatas.WinnerColor = BLACK;
	}
	else if (board.WhiteCaptures >= 10)
	{
		std::cout << KGRN "WHITE WINS BY CAPTURE" KRESET << std::endl;
		GameDatas.IsGameOver = true;
		GameDatas.WinnerColor = WHITE;
	}
	else
	{
		// Check victory by alignment.
		for (y = 0; y < 19; y++)
		{
			for (x = 0; x < 19; x++)
			{
				curPoint.x = x;
				curPoint.y = y;
				for (dir = 1; dir != 5; dir++)
				{
					// for each direction on the current point, we extract a string.
					Tools::GetPointsLine(line, board, curPoint, (t_dir)dir, 5);
					// check for all victory patterns and fill the VictorySequence vector.
					checkVictoryPatterns(board, curPoint, (t_dir)dir, line, VictorySequences);
				}
			}
		}
		// We got all victory lines, now we check if they are valid.
		if (VictorySequences.size() != 0)
		{
			std::cout << KYEL "Victory pattern found:" KRESET << std::endl;
			// for each line of 5, check if it's win, or capturable.
			WinnerColor = areVictorySequencesValid(GameDatas, board, VictorySequences);
			if (WinnerColor == NONE)
				std::cout << KMAG "-> Victory sequence invalid, can be captured." KRESET << std::endl;
			else if (WinnerColor == BLACK)
			{
				std::cout << KGRN "Victory for BLACK" KRESET << std::endl;
				GameDatas.IsGameOver = true;
				GameDatas.WinnerColor = BLACK;
			}
			else
			{
				std::cout << KGRN "Victory for WHITE" KRESET << std::endl;
				GameDatas.IsGameOver = true;
				GameDatas.WinnerColor = WHITE;
			}
			return ;
		}
		// no victory sequence ongoing, no one is in check state.
		GameDatas.BlackInCheck = false;
		GameDatas.WhiteInCheck = false;
	}
}

/*
**	Victory pattern checking for the current direction dir.
**	We start by taking only the simple 5 alignments.
*/

void	GameRules::checkVictoryPatterns(Board &board,
								t_vec2 curPoint, t_dir dir,
								char *line,
								std::vector<t_VictorySequence> &victorySequences)
{
	t_VictorySequence				victoryLine;
	t_vec2							pointToAdd;
	static int						mod_x;
	static int						mod_y;

	Tools::SetMoveModifiers(mod_x, mod_y, dir);
	if (strncmp(line, "11111", 5) == 0)
	{
		victoryLine.Color = BLACK;
		// add the five stones in the struct victory sequence.
		for (int i = 0; i != 5; i++)
		{
			pointToAdd.x = curPoint.x + mod_x * i;
			pointToAdd.y = curPoint.y + mod_y * i;
			victoryLine.Stones.push_back(pointToAdd);
		}
		victorySequences.push_back(victoryLine);
	}
	if (strncmp(line, "22222", 5) == 0)
	{
		victoryLine.Color = WHITE;
		for (int i = 0; i != 5; i++)
		{
			pointToAdd.x = curPoint.x + mod_x * i;
			pointToAdd.y = curPoint.y + mod_y * i;
			victoryLine.Stones.push_back(pointToAdd);
		}
		victorySequences.push_back(victoryLine);
	}
}

/*
**	For every victory sequence (ie 5 stones aligned), we check
**	if any or several of them are valid.
**	For example, if one line is invalid but another for the same
**	color is valid, it's a win.
*/

t_Color		GameRules::areVictorySequencesValid(t_GameDatas &GameDatas, Board &board,
				std::vector<t_VictorySequence> &victorySequences)
{
	std::vector<t_VictorySequence>::iterator	curSequence;

	static char					line[3];
	static char					backLine[3];
	static int					dir;
	static t_vec2				curPoint;

	static bool					blackStoneCapturableFound;
	static bool					whiteStoneCapturableFound;

	static t_vec2				captureMove;

	// for each victory sequence.
	for (curSequence = victorySequences.begin(); curSequence != victorySequences.end(); curSequence++)
	{
		// for each stone in current sequence.
		blackStoneCapturableFound = false;
		whiteStoneCapturableFound = false;
		for (std::vector<t_vec2>::iterator vec_it = (*curSequence).Stones.begin();
				vec_it != (*curSequence).Stones.end(); vec_it++)
		{
			curPoint.x = (*vec_it).x;
			curPoint.y = (*vec_it).y;
			// for each direction on the current stone from the current sequence.
			for (dir = 1; dir != 9; dir++)
			{
				// Tools::GetPatternPointsLine(line, board, curPoint, (t_dir)dir, 3, BLACK);
				// Tools::GetPatternPointsLine(backLine, board, curPoint, Tools::GetOppositeDir((t_dir)dir), 3, BLACK);
				
				if ((*curSequence).Color == BLACK)
				{
					Tools::GetDualPatternPointsLine(&(line[0]), &(backLine[0]), board, curPoint, (t_dir)dir, 3, BLACK);
					if (GetCaptureMove(board, curPoint, (t_dir)dir, line, backLine, captureMove) == true)
					{
						blackStoneCapturableFound = true;
						std::cout << KMAG "- Capturable stone in BLACK sequence in " KRESET << captureMove.x << "x " << captureMove.y << "y" << std::endl;
						if (GameDatas.WhiteInCheck == true) // if White has missed the chance to capture this sequence.
							return (BLACK); // -> black wins.
						(*curSequence).CapturePoints.push_back(captureMove);
						break ;
					}
				}
				else
				{
					Tools::GetDualPatternPointsLine(&(line[0]), &(backLine[0]), board, curPoint, (t_dir)dir, 3, WHITE);
					if (GetCaptureMove(board, curPoint, (t_dir)dir, line, backLine, captureMove) == true)
					{
						whiteStoneCapturableFound = true;
						std::cout << KMAG "- Capturable stone in WHITE sequence in " KRESET << captureMove.x << "x " << captureMove.y << "y" << std::endl;
						if (GameDatas.BlackInCheck == true)
							return (WHITE);
						(*curSequence).CapturePoints.push_back(captureMove);
						break ;
					}
				}
			}
		}
		if (blackStoneCapturableFound == false && whiteStoneCapturableFound == false) // -> valid line of 5.
		{
			if ((*curSequence).Color == BLACK)
			{
				if (GameDatas.BlackInCheck == false)
					return (BLACK);
				else
					return (WHITE);
			}
			else 
			{
				if (GameDatas.WhiteInCheck == false)
					return (WHITE);
				else
					return (BLACK);
			}
		}
	}
	if (blackStoneCapturableFound == true)
		GameDatas.WhiteInCheck = true;
	else
		GameDatas.BlackInCheck = true;
	return (NONE);
}

bool		GameRules::GetCaptureMove(Board &board, t_vec2 curPoint, t_dir dir,
										char *line, char *backLine,
										t_vec2 &retMove)
{
	int			mod_x;
	int			mod_y;

	retMove.x = -1;
	retMove.y = -1;
	if (strncmp(line, "112", 3) == 0
		&& strncmp(backLine, "10", 2) == 0)
	{
		// get the point behind.
		Tools::SetMoveModifiers(mod_x, mod_y, dir);
		retMove.x = curPoint.x - mod_x;
		retMove.y = curPoint.y - mod_y;
		return (true);
	}
	else if (strncmp(line, "110", 3) == 0
		&& strncmp(backLine, "12", 2) == 0)
	{
		Tools::SetMoveModifiers(mod_x, mod_y, dir);
		retMove.x = curPoint.x + mod_x * 2;
		retMove.y = curPoint.y + mod_y * 2;
		return (true);
	}
	return (false);
}
