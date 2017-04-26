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

	if (board.Map[move.y][move.x] == NONE)
	{
		if (hasDoubleThree(board, color, move) == 1)
		{
			return (false);
		}
		return (true);
	}
	else
		return (false);
	return (true);
}

void	GameRules::CheckCaptures(Board &board, t_vec2 move)
{
	(void)move;
	(void)board;
}

/*
**	See GameRules_FreeThrees.cpp for the rest of the methods.
*/

bool	GameRules::hasDoubleThree(Board &board, t_Color color, t_vec2 move)
{
	(void)board;
	(void)color;
	(void)move;

	int				dir;
	int				nb_free_3;
	std::string		doublon_mask;

	dir = 1;
	nb_free_3 = 0;
	while (dir != 9)
	{
		if (color == BLACK)
		{
			nb_free_3 += checkDoubleThreeBlackPatterns(board, move, (t_dir)dir);
		}
		else
		{
			nb_free_3 += checkDoubleThreeWhitePatterns(board, move, (t_dir)dir);
		}
		dir++;
	}
	std::cout << "Found " << nb_free_3 << " free three(s)." << std::endl;
	return (false);
}

void	GameRules::CheckVictory(t_GameDatas &GameDatas)
{
	(void)GameDatas;
}
