#include "../includes/Gomoku.hpp"

GameRules::GameRules()
{

}

GameRules::~GameRules()
{

}

bool	GameRules::isMoveAuthorized(Board &board, t_Color color, t_vec2 move)
{
	(void)move;

	if (board.map[move.y][move.x] == NONE || board.map[move.y][move.x] == SUGGESTION)
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

void	GameRules::checkVictory(t_GameDatas &gameDatas)
{
	(void)gameDatas;
}
