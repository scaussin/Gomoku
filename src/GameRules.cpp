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
		if (hasDoubleThree(board, color, move) == 1
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

void	GameRules::CheckVictory(t_GameDatas &GameDatas)
{
	(void)GameDatas;
}
