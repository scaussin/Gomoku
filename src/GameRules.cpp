#include "../includes/Gomoku.hpp"

GameRules::GameRules()
{

}

GameRules::~GameRules()
{

}

bool	GameRules::IsMoveAuthorized(Board &Board, t_Color color, t_vec2 move)
{
	(void)move;

	if (Board.Map[move.y][move.x] == NONE)
	{
		if (HasDoubleThree(Board, color, move) == 1)
		{
			return (false);
		}
		return (true);
	}
	else
		return (false);
	return (true);
}

void	GameRules::CheckCaptures(Board &Board, t_vec2 move)
{
	(void)move;
	(void)Board;
}

bool	GameRules::HasDoubleThree(Board &Board, t_Color color, t_vec2 move)
{
	(void)Board;
	(void)color;
	(void)move;

	

	return (false);
}

void	GameRules::CheckVictory(t_GameDatas &GameDatas)
{
	(void)GameDatas;
}
