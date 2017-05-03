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

	if (GameDatas.BlackCaptures >= 10)
	{
		std::cout << KGRN "BLACK WINS BY CAPTURE" KRESET << std::endl;
		GameDatas.IsGameOver = true;
	}
	else if (GameDatas.WhiteCaptures >= 10)
	{
		std::cout << KGRN "WHITE WINS BY CAPTURE" KRESET << std::endl;
		GameDatas.IsGameOver = true;
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
					Tools::GetPatternPointsLine(line, board, curPoint, (t_dir)dir, 5, BLACK);
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
			WinnerColor = areVictorySequencesValid(board, VictorySequences);
			if (WinnerColor == NONE)
				std::cout << KMAG "-> Victory sequence invalid, can be captured." KRESET << std::endl;
			else if (WinnerColor == BLACK)
			{
				std::cout << KGRN "Victory for BLACK" KRESET << std::endl;
				GameDatas.IsGameOver = true;
			}
			else
			{
				std::cout << KGRN "Victory for WHITE" KRESET << std::endl;
				GameDatas.IsGameOver = true;
			}
		}
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
	t_VictorySequence		victoryLine;
	t_vec2					pointToAdd;
	int						mod_x;
	int						mod_y;

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

t_Color		GameRules::areVictorySequencesValid(Board &board,
				std::vector<t_VictorySequence> &victorySequences)
{
	std::vector<t_VictorySequence>::iterator	curSequence;

	static char					line[3];
	static char					backLine[3];
	static int					dir;
	static t_vec2				curPoint;

	int							blackValidLines = 0;
	int							whiteValidLines = 0;

	static bool					stoneCapturableFound;

	// for each victory sequence.
	for (curSequence = victorySequences.begin();
			curSequence != victorySequences.end();
			curSequence++)
	{
		// std::cout << KYEL "Victory line = " KRESET << "color "
		// << (*curSequence).Color <<  std::endl;
		// for each stone in current sequence.
		stoneCapturableFound = false;
		for (std::vector<t_vec2>::iterator vec_it = (*curSequence).Stones.begin();
				vec_it != (*curSequence).Stones.end();
				vec_it++)
		{
			curPoint.x = (*vec_it).x;
			curPoint.y = (*vec_it).y;
			//std::cout << curPoint.x << "x " << curPoint.y << "y" << std::endl;
			// for each direction on the current stone from the current sequence.
			for (dir = 1; dir != 9; dir++)
			{
				Tools::GetPatternPointsLine(line, board, curPoint, (t_dir)dir, 3, BLACK);
				Tools::GetPatternPointsLine(backLine, board, curPoint, Tools::GetOppositeDir((t_dir)dir), 3, BLACK);
				//std::cout << "line = " << line << std::endl;
				if ((*curSequence).Color == BLACK)
				{
					if (IsBlackStoneCapturable(board, curPoint, (t_dir)dir, line, backLine) == true)
					{
						stoneCapturableFound = true;
						std::cout << KMAG "- Capturable stone in BLACK sequence!" KRESET << std::endl;
						break ;
					}
				}
				else
				{
					if (IsBlackStoneCapturable(board, curPoint, (t_dir)dir, line, backLine) == true)
					{
						stoneCapturableFound = true;
						std::cout << KMAG "- Capturable stone in WHITE sequence!" KRESET << std::endl;
						break ;
					}
				}
			}
		}
		if (stoneCapturableFound == false) // -> valid line of 5.
		{
			if ((*curSequence).Color == BLACK)
				blackValidLines += 1;
			else
				whiteValidLines += 1;
		}
		// continue checking the other sequences,
		// because it could be a draw.
	}
	// check who won.
	if (blackValidLines >= 1 && whiteValidLines == 0)
		return (BLACK);
	else if (whiteValidLines >= 1 && blackValidLines == 0)
		return (WHITE);
	else if (whiteValidLines != 0 && blackValidLines != 0
				&& whiteValidLines == blackValidLines)
	{
		std::cout << KRED "Draw!" KRESET << std::endl;
	}
	return (NONE);
}
