#ifndef GAMERULES_HPP
# define GAMERULES_HPP

#include "Gomoku.hpp"

class GameRules
{
	public:
		GameRules();
		~GameRules();

		bool	IsMoveAuthorized(t_GameDatas &GameDatas, t_vec2 move);
		void	CheckCaptures(t_GameDatas &GameDatas, t_vec2 move);

		void	CheckVictory(t_GameDatas &GameDatas);
};

#endif