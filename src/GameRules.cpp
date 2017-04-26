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


void		GameRules::doCaptures(Board &board, t_Color color, t_vec2 move)
{
	t_Color enemy;

	if (color == BLACK)
		enemy = WHITE;
	else
		enemy = BLACK;
	
	//top left
	if (board.getPoint(move.y + 1,  move.x - 1) == enemy
		&& board.getPoint(move.y + 2,  move.x - 2) == enemy
		&& board.getPoint(move.y + 3,  move.x - 3) == color)
	{
		board.setPoint(move.y + 1,  move.x - 1, NONE);
		board.setPoint(move.y + 2,  move.x - 2, NONE);
		cout << "capture top left" << endl;
	}
	//top
	if (board.getPoint(move.y + 1,  move.x) == enemy
		&& board.getPoint(move.y + 2,  move.x) == enemy
		&& board.getPoint(move.y + 3,  move.x) == color)
	{
		board.setPoint(move.y + 1,  move.x, NONE);
		board.setPoint(move.y + 2,  move.x, NONE);
		cout << "capture top" << endl;
	}
	//top right
	if (board.getPoint(move.y + 1,  move.x + 1) == enemy
		&& board.getPoint(move.y + 2,  move.x + 2) == enemy
		&& board.getPoint(move.y + 3,  move.x + 3) == color)
	{
		board.setPoint(move.y + 1,  move.x + 1, NONE);
		board.setPoint(move.y + 2,  move.x + 2, NONE);
		cout << "capture top right" << endl;
	}
	// right
	if (board.getPoint(move.y,  move.x + 1) == enemy
		&& board.getPoint(move.y,  move.x + 2) == enemy
		&& board.getPoint(move.y,  move.x + 3) == color)
	{
		board.setPoint(move.y,  move.x + 1, NONE);
		board.setPoint(move.y,  move.x + 2, NONE);
		cout << "capture right" << endl;
	}
	//bottom right
	if (board.getPoint(move.y - 1,  move.x + 1) == enemy
		&& board.getPoint(move.y - 2,  move.x + 2) == enemy
		&& board.getPoint(move.y - 3,  move.x + 3) == color)
	{
		board.setPoint(move.y - 1,  move.x + 1, NONE);
		board.setPoint(move.y - 2,  move.x + 2, NONE);
		cout << "capture bottom right" << endl;
	}
	//bottom
	if (board.getPoint(move.y - 1,  move.x) == enemy
		&& board.getPoint(move.y - 2,  move.x) == enemy
		&& board.getPoint(move.y - 3,  move.x) == color)
	{
		board.setPoint(move.y - 1,  move.x, NONE);
		board.setPoint(move.y - 2,  move.x, NONE);
		cout << "capture bottom" << endl;
	}
	//bottom left
	if (board.getPoint(move.y - 1,  move.x - 1) == enemy
		&& board.getPoint(move.y - 2,  move.x - 2) == enemy
		&& board.getPoint(move.y - 3,  move.x - 3) == color)
	{
		board.setPoint(move.y - 1,  move.x - 1, NONE);
		board.setPoint(move.y - 2,  move.x - 2, NONE);
		cout << "capture bottom left" << endl;
	}
	//left
	if (board.getPoint(move.y,  move.x - 1) == enemy
		&& board.getPoint(move.y,  move.x - 2) == enemy
		&& board.getPoint(move.y,  move.x - 3) == color)
	{
		board.setPoint(move.y,  move.x - 1, NONE);
		board.setPoint(move.y,  move.x - 2, NONE);
		cout << "capture left" << endl;
	}
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
