#ifndef GAMERULES_HPP
# define GAMERULES_HPP

#include "Gomoku.hpp"

class GameRules
{
	public:
		GameRules();
		~GameRules();

		static bool			IsMoveAuthorized(char Board[][19], t_Color color, t_vec2 move);
		void				CheckCaptures(char Board[][19], t_vec2 move);

		void				CheckVictory(t_GameDatas &GameDatas);

	private:
		static bool			HasDoubleThree(char Board[][19], t_Color color, t_vec2 move);
};

#endif