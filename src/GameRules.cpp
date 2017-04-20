#include "../includes/Gomoku.hpp"

GameRules::GameRules()
{

}

GameRules::~GameRules()
{

}

bool	GameRules::IsMoveAuthorized(t_GameDatas &GameDatas, t_vec2 move)
{
	(void)GameDatas;
	(void)move;

	if (GameDatas.Board[move.y][move.x] == NONE)
		return (true);
	else
		return false;

	return (true);
}

void	GameRules::CheckCaptures(t_GameDatas &GameDatas, t_vec2 move)
{
	(void)GameDatas;
	(void)move;
}

void	GameRules::CheckVictory(t_GameDatas &GameDatas)
{
	(void)GameDatas;
}
