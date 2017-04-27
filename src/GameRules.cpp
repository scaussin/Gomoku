#include "../includes/Gomoku.hpp"

GameRules::GameRules()
{

}

GameRules::~GameRules()
{

}

bool	GameRules::IsMoveAuthorized(Board &board, t_Color color, t_vec2 move)
{
	(void)move;

	if (board.Map[move.y][move.x] == NONE || board.Map[move.y][move.x] == SUGGESTION)
	{
		if (checkForbiddenPatterns(board, color, move) == true
			&& checkCaptures(board, color, move) == false)
		{
			return (false);
		}
		return (true);
	}
	else
		return (false);
	return (true);
}

bool	GameRules::checkForbiddenPatterns(Board &board, t_Color color, t_vec2 move)
{
	int				dir;
	int				nb_free_3;
	std::string		line;
	std::string		backLine;

	dir = 1;
	nb_free_3 = 0;
	// for the move, we look in all directions.
	while (dir != 9)
	{
		// for each direction, we extract a string.
		line = Tools::GetPointsLine(board, move, (t_dir)dir, 5);
		backLine = Tools::GetPointsLine(board, move, Tools::GetOppositeDir((t_dir)dir), 5);
		// patterns are different for each color.
		if (color == BLACK)
		{
			// If uncommented, cannot move into capture.
			// if (checkBlackMovingIntoCapture(board, move, (t_dir)dir, line, backLine) == true)
			// {
			// 	std::cout << KMAG "Black tried to move into capture" KRESET << std::endl;
			// 	return (true);
			// }
			nb_free_3 += checkDoubleThreeBlackPatterns(board,
							move, (t_dir)dir, line, backLine);
		}
		else
		{
			// If uncommented, cannot move into capture.
			// if (checkWhiteMovingIntoCapture(board, move, (t_dir)dir, line, backLine) == true)
			// {
			// 	std::cout << KMAG "White tried to move into capture" KRESET << std::endl;
			// 	return (true);
			// }
			nb_free_3 += checkDoubleThreeWhitePatterns(board,
							move, (t_dir)dir, line, backLine);
		}
		dir++;
	}
	std::cout << "Found " << KYEL << nb_free_3 << KRESET << " free three(s)." << std::endl;
	if (nb_free_3 >= 2)
	{
		return (true);
	}
	return (false);
}

void	GameRules::CheckVictory(t_GameDatas &GameDatas)
{
	(void)GameDatas;
}
