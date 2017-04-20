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
